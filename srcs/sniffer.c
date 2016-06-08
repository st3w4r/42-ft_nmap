#include "ft_nmap.h"

// Scan Detection Receive Response
void nm_detect_scan(
		enum e_scan_types scan_type,
		u_int16_t urg,
		u_int16_t ack,
		u_int16_t psh,
		u_int16_t rst,
		u_int16_t syn,
		u_int16_t fin
		)
{
	// SYN
	if ((scan_type & SYN_F) && (syn & 0x1 ) && (ack & 0x1))
		printf("--OPEN-- SCAN SYN\n");
	// NULL
	else if ((scan_type & NULL_F) && (rst & 0x1))
		printf("--CLOSE-- SCAN NULL");
	// FIN
	else if ((scan_type & FIN_F) && (rst & 0x1))
		printf("--CLOSE-- SCAN FIN");
	// XMAS
	else if ((scan_type & XMAS_F) && (rst & 0x1))
		printf("--CLOSE-- SCAN XMAS");
	// ACK
	else if ((scan_type & ACK_F) && (rst & 0x1))
		printf("--UNFILTRED-- SCAN ACK\n");

}

void nm_capture_packet(u_char *user, const struct pcap_pkthdr *h, const u_char *packet)
{
	const struct ethhdr *ethernet;
	const struct ip *ip;
	const struct tcphdr *tcp;
	const u_char *payload;
	u_int size_ip;
	u_int size_tcp;

	ethernet = (struct ethhdr*)(packet);
	printf("Ethernet: %u\n", ethernet->h_proto);

	ip = (struct ip*)(packet + ETH_HLEN);

	size_ip = ip->ip_hl * 4;
	if (size_ip < 20) {
		printf("   * Invalid IP header length: %u bytes\n", size_ip);
		return ;
	}

	printf("IP SRC sniffed: %s\n", inet_ntoa(ip->ip_src));
	printf("IP DST sniffed: %s\n", inet_ntoa(ip->ip_dst));

	tcp = (struct tcphdr*)(packet + ETH_HLEN + size_ip);

	size_tcp = tcp->doff * 4;
	if (size_tcp < 20) {
		printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
		return ;
	}
	payload = (u_char *)(packet + ETH_HLEN + size_ip + size_tcp);
	printf("TCP SRC port: %u\n", ntohs(tcp->source));
	printf("TCP DST port: %u\n", ntohs(tcp->dest));
	printf("TCP SEQ: %u\n", ntohl(tcp->seq));
	printf("TCP ACK: %u\n", ntohl(tcp->ack_seq));
	printf("FLAGS:\n");

	(tcp->fin & 0x1) ? printf("FIN on\n") : printf("FIN off\n");
	(tcp->syn & 0x1) ? printf("SYN on\n") : printf("SYN off\n");
	(tcp->rst & 0x1) ? printf("RST on\n") : printf("RST off\n");
	(tcp->psh & 0x1) ? printf("PUSH on\n") : printf("PUSH off\n");
	(tcp->ack & 0x1) ? printf("ACK on\n") : printf("ACK off\n");
	(tcp->urg & 0x1) ? printf("URG on\n") : printf("URG off\n");

//	nm_detect_scan(ACK_F,
//			tcp->urg, tcp->ack, tcp->psh, tcp->rst, tcp->syn, tcp->fin);
/*
	(tcp->fin & 0x1) ? printf("FIN on\n") : printf("FIN off\n");
	(tcp->syn & 0x1) ? printf("SYN on\n") : printf("SYN off\n");
	(tcp->rst & 0x1) ? printf("RST on\n") : printf("RST off\n");
	(tcp->psh & 0x1) ? printf("PUSH on\n") : printf("PUSH off\n");
	(tcp->ack & 0x1) ? printf("ACK on\n") : printf("ACK off\n");
	(tcp->urg & 0x1) ? printf("URG on\n") : printf("URG off\n");
*/
}


void	 *nm_th_sniffer(void * data)
{

	t_th_sniffer data_sniffer = *(t_th_sniffer*)data;

	struct ip *ip;
	struct tcphdr *tcp;
	struct udphdr *udp;
	char *buf;

	buf = malloc(PACKET_BUF_SIZE);
	ft_memset(buf, 0, PACKET_BUF_SIZE);
	ip = nm_configure_packet_ip(buf, g_struct.ip_store[0].content);
	tcp = nm_configure_packet_tcp(buf, data_sniffer.port_src, data_sniffer.port_dst
			, data_sniffer.seq, data_sniffer.ack_seq, data_sniffer.flags);

	printf("Dans thread data_sniffer: %s\n\n", data_sniffer.filter_exp);
	nm_sniffer(data_sniffer.filter_exp, buf, ip, tcp, data_sniffer);
	printf("Apres sniffer\n\n");

	return (0);
}

void nm_sniffer(char *filter_exp, char *buf, struct ip *ip, struct tcphdr *tcp, t_th_sniffer data_sniffer)
{
	char dev[] = "eth0";
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *handle;
	struct bpf_program fp;
	// char filter_exp[] = nm_build_filter(data_sniffer.port_dst, g_struct.ip_store[0].content);;
//	char filter_exp[] = "tcp";
	bpf_u_int32 mask;
	bpf_u_int32 net;
	struct pcap_pkthdr header;
	const u_char *packet;

	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1)
	{
		fprintf(stderr, "Can't get netmask: %s:%s\n", dev, errbuf);
		net = 0;
		mask = 0;
	}

	handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
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

	printf("Send once \n\n");
	sendto(data_sniffer.socket, buf, ip->ip_len, 0, (struct sockaddr*)&data_sniffer.sin, sizeof(struct sockaddr));
	int ret = pcap_dispatch(handle, 1, nm_capture_packet, NULL);
	printf("Ret: %d\n", ret);
	pcap_close(handle);
}
