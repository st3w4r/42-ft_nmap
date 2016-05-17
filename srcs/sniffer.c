#include "ft_nmap.h"

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
	printf("FLAGS:\n");
	
	(tcp->fin & 0x1) ? printf("FIN on\n") : printf("FIN off\n");
	(tcp->syn & 0x1) ? printf("SYN on\n") : printf("SYN off\n");
	(tcp->rst & 0x1) ? printf("RST on\n") : printf("RST off\n");
	(tcp->psh & 0x1) ? printf("PUSH on\n") : printf("PUSH off\n");
	(tcp->ack & 0x1) ? printf("ACK on\n") : printf("ACK off\n");
	(tcp->urg & 0x1) ? printf("URG on\n") : printf("URG off\n");
}

void	nm_sniffer(char *ip, unsigned int port, char *proto)
{
	char dev[] = "eth0";
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *handle;
	struct bpf_program fp;
//	char filter_exp[] = "tcp port 53 and src host 8.8.8.8";
	char filter_exp[] = "tcp";
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

//	while (42)
		pcap_dispatch(handle, 100, nm_capture_packet, NULL);

	pcap_close(handle);
}
