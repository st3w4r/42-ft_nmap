#include "ft_nmap.h"

void capture_packet(u_char *user, const struct pcap_pkthdr *h, const u_char *packet)
{

	const struct ether_header *ethernet;
	const struct iphdr *ip;
	const struct tcp *tcp;
	const char *payload;
	u_int size_ip;
	u_int size_tcp;


	ethernet = (struct ether_header*)(packet);
/*	printf("Ethernet: %u\n", ethernet->ether_type);

	ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
	size_ip = IP_HL(ip)*4;
	if (size_ip < 20) {
		printf("   * Invalid IP header length: %u bytes\n", size_ip);
		return ;
	}
	printf("IP SRC sniffed: %s\n", inet_ntoa(ip->ip_src));
	printf("IP DST sniffed: %s\n", inet_ntoa(ip->ip_dst));

	tcp = (struct sniff_tcp*)(packet + SIZE_ETHERNET + size_ip);
	size_tcp = TH_OFF(tcp)*4;
	if (size_tcp < 20) {
		printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
		return ;
	}
	payload = (u_char *)(packet + SIZE_ETHERNET + size_ip + size_tcp);
	printf("TCP SRC port: %u\n", ntohs(tcp->th_sport));
	printf("TCP DST port: %u\n", ntohs(tcp->th_dport));
	printf("FLAGS: %u\n", tcp->th_flags);

	(tcp->fin & 0x1) ? printf("FIN on\n") : printf("FIN off\n");
	(tcp->syn & 0x1) ? printf("SYN on\n") : printf("SYN off\n");
	(tcp->rst & 0x1) ? printf("RST on\n") : printf("RST off\n");
	(tcp->psh & 0x1) ? printf("PUSH on\n") : printf("PUSH off\n");
	(tcp->ack & 0x1) ? printf("ACK on\n") : printf("ACK off\n");
	(tcp->urg & 0x1) ? printf("URG on\n") : printf("URG off\n");
*/

	// Flags
/*	tcp->urg = (flags & F_TCP_URG) ? 1 : 0;
	tcp->ack = (flags & F_TCP_ACK) ? 1 : 0;
	tcp->psh = (flags & F_TCP_PSH) ? 1 : 0;
	tcp->rst = (flags & F_TCP_RST) ? 1 : 0;
	tcp->syn = (flags & F_TCP_SYN) ? 1 : 0;
	tcp->fin = (flags & F_TCP_FIN) ? 1 : 0;

	(tcp->th_flags & TH_FIN) ? printf("FIN on\n") : printf("FIN off\n");
	(tcp->th_flags & TH_SYN) ? printf("SYN on\n") : printf("SYN off\n");
	(tcp->th_flags & TH_RST) ? printf("RST on\n") : printf("RST off\n");
	(tcp->th_flags & TH_PUSH) ? printf("PUSH on\n") : printf("PUSH off\n");
	(tcp->th_flags & TH_ACK) ? printf("ACK on\n") : printf("ACK off\n");
	(tcp->th_flags & TH_URG) ? printf("URG on\n") : printf("URG off\n");
	(tcp->th_flags & TH_ECE) ? printf("ECE on\n") : printf("ECE off\n");
	(tcp->th_flags & TH_CWR) ? printf("CWR on\n") : printf("CWR off\n");
*/
}

void	nm_sniffer(char *ip, unsigned int port, char *proto)
{
	char dev[] = "eth0";
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *handle;
	struct bpf_program fp;
	//	char filter_exp[] = "tcp port 53 and src host 8.8.8.8";
	char *filter_exp;
	bpf_u_int32 mask;
	bpf_u_int32 net;
	struct pcap_pkthdr header;
	const u_char *packet;

	filter_exp = ft_strdup(proto);
	filter_exp = ft_strjoin(" port ", filter_exp);
	filter_exp = ft_strjoin(" and src host ", ip);

	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1)
	{
		fprintf(stderr, "Can't get netmask: %s:%s\n", dev, errbuf);
		net = 0;
		mask = 0;
	}

	handle = pcap_open_live(dev, BUFSIZ, 1, 10000, errbuf);
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

	while (42)
		pcap_dispatch(handle, 100, capture_packet, NULL);

	pcap_close(handle);
}
