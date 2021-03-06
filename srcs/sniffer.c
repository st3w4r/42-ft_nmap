#include "ft_nmap.h"

// Scan Detection Receive Response

enum e_scan_result	nm_detect_scan(
		enum e_scan_types scan_type,
		t_bool timeout,
		u_int16_t urg,
		u_int16_t ack,
		u_int16_t psh,
		u_int16_t rst,
		u_int16_t syn,
		u_int16_t fin
		)
{

	(void)urg;
	(void)ack;
	(void)fin;
	(void)psh;
	enum e_scan_result result;
	// SYN
	if ((scan_type & SYN_F) && (syn & 0x1 ) && (ack & 0x1))
	{
		result = F_RESULT_OPEN;
	}
	else if ((scan_type & SYN_F) && (rst & 0x1))
	{
		result = F_RESULT_CLOSE;
	}
	else if ((scan_type & SYN_F) && (timeout == TRUE))
	{
		result = F_RESULT_FILTERED;
	}
	// NULL
	else if ((scan_type & NULL_F) && (rst & 0x1))
	{
		result = F_RESULT_CLOSE;
	}
	else if ((scan_type & NULL_F) && (timeout == TRUE))
	{
		result = F_RESULT_OPEN_FILTERED;
	}
	// FIN
	else if ((scan_type & FIN_F) && (rst & 0x1))
	{
		result = F_RESULT_CLOSE;
	}
	else if ((scan_type & FIN_F) && (timeout == TRUE))
	{
		result = F_RESULT_OPEN_FILTERED;
	}
	// XMAS
	else if ((scan_type & XMAS_F) && (rst & 0x1))
	{
		result = F_RESULT_CLOSE;
	}
	else if ((scan_type & XMAS_F) && (timeout == TRUE))
	{
		result = F_RESULT_OPEN_FILTERED;
	}
	// UDP
	else if ((scan_type & UDP_F) && (timeout == TRUE))
	{
		result = F_RESULT_OPEN_FILTERED;
	}
	// ACK
	else if ((scan_type & ACK_F) && (rst & 0x1))
	{
		result = F_RESULT_UNFILTERED;
	}
	else if ((scan_type & ACK_F) && (timeout == TRUE))
	{
		result = F_RESULT_FILTERED;
	}

	return (result);
}

void nm_capture_packet(u_char *user, const struct pcap_pkthdr *h, const u_char *packet)
{
	const struct ethhdr *ethernet;
	const struct ip *ip;
	const struct tcphdr *tcp;
	const u_char *payload;
	u_int size_ip;
	u_int size_tcp;
	t_th_sniffer *data_sniffer;

	(void)h;
	data_sniffer = (t_th_sniffer *)user;
	ethernet = (struct ethhdr*)(packet);

	ip = (struct ip*)(packet + ETH_HLEN);

	size_ip = ip->ip_hl * 4;
	if (size_ip < 20) {
		printf("   * Invalid IP header length: %u bytes\n", size_ip);
		return ;
	}

	tcp = (struct tcphdr*)(packet + ETH_HLEN + size_ip);

	size_tcp = tcp->doff * 4;
	if (size_tcp < 20) {
		printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
		return ;
	}
	payload = (u_char *)(packet + ETH_HLEN + size_ip + size_tcp);

	data_sniffer->scan_result = nm_detect_scan(data_sniffer->scan_type, FALSE,
			tcp->urg, tcp->ack, tcp->psh, tcp->rst, tcp->syn, tcp->fin);

}


void	 nm_th_sniffer(void * data)
{

	t_th_sniffer data_sniffer = *(t_th_sniffer*)data;

	struct ip *ip;
	struct tcphdr *tcp;
	struct udphdr *udp;
	char *buf;

	buf = malloc(PACKET_BUF_SIZE);
	ft_memset(buf, 0, PACKET_BUF_SIZE);
	ip = nm_configure_packet_ip(buf, data_sniffer.ip_str, data_sniffer.scan_type);
	if (data_sniffer.scan_type & UDP_F)
		udp = nm_configure_packet_udp(buf, data_sniffer.port_dst);
	else
		tcp = nm_configure_packet_tcp(buf, data_sniffer.port_dst
			, data_sniffer.seq, data_sniffer.ack_seq, data_sniffer.flags);
	nm_sniffer(data_sniffer.filter_exp, buf, ip, data_sniffer);

}

void nm_sniffer(char *filter_exp, char *buf, struct ip *ip, t_th_sniffer data_sniffer)
{
	char dev[] = "eth0";
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *handle;
	struct bpf_program fp;
	bpf_u_int32 mask;
	bpf_u_int32 net;

	pthread_mutex_lock(&g_struct.pcap_init_mutex);
	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1)
	{
		fprintf(stderr, "Can't get netmask: %s:%s\n", dev, errbuf);
		net = 0;
		mask = 0;
	}
	handle = pcap_open_live(dev, BUFSIZ, 1, g_struct.packet_time, errbuf);
	if (handle == NULL)
	{
		fprintf(stderr, "Couldn't open device: %s:%s\n", dev, errbuf);
		exit(2);
	}
	if (pcap_compile(handle, &fp, filter_exp, 1, net) == -1)
	{
		fprintf(stderr, "Couldn't compile filter: %s:%s\n",
				filter_exp, pcap_geterr(handle));
		exit(2);
	}
	if (pcap_setfilter(handle, &fp) == -1)
	{
		fprintf(stderr, "Couldn't set filter: %s:%s\n",
				filter_exp, pcap_geterr(handle));
		exit(2);
	}
	pthread_mutex_unlock(&g_struct.pcap_init_mutex);

	sendto(data_sniffer.socket, buf, ip->ip_len, 0, (struct sockaddr*)&data_sniffer.sin, sizeof(struct sockaddr));
	int ret = pcap_dispatch(handle, 1, nm_capture_packet, (unsigned char *)&data_sniffer);
	if (ret == 0)
		data_sniffer.scan_result = nm_detect_scan(data_sniffer.scan_type, TRUE, 0, 0, 0, 0, 0, 0);

	pthread_mutex_lock(&g_struct.store_mutex);
	t_store *ptr = NULL;
	ptr = g_struct.store;

	while(ptr->next != NULL)
	ptr = ptr->next;
	ptr->ports_results = (t_port_result*)malloc(sizeof(t_port_result));

	ptr->ip = ft_strdup(data_sniffer.ip_str);
	ptr->ports_results->port = data_sniffer.port_dst;
	ptr->ports_results->results = data_sniffer.scan_result;
	ptr->ports_results->type = data_sniffer.scan_type;
	ptr->ports_results->conclusion = TRUE;
	ptr->ports_results->service_name = nm_get_service_name(data_sniffer.port_dst, (ip->ip_p == IPPROTO_TCP ? "tcp" : "udp"));

	ptr->next = (t_store*)malloc(sizeof(t_store));
	ptr = ptr->next;
	ptr->next = NULL;
	pthread_mutex_unlock(&g_struct.store_mutex);

	pcap_close(handle);
}
