#include "ft_nmap.h"

int nm_open_socket()
{
	int hincl;
	int s;

	hincl = 1;
	if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) < 0)
		ft_error_str_exit("Error socket opening\n");
	if (setsockopt(s, IPPROTO_IP, IP_HDRINCL, &hincl, sizeof(hincl)) < 0)
		ft_error_str_exit("Error setsocket\n");
	return (s);
}

struct ip		*nm_configure_packet_ip(char *buf, char *ip_dst, enum e_scan_types type)
{
	struct ip *ip;
	char *addr;

	ip = (struct ip*)(buf);
	ip->ip_v = 4;
	ip->ip_hl = sizeof(*ip) >> 2;
	ip->ip_tos = 0;
	ip->ip_len = sizeof(struct iphdr) + ((type & UDP_F) ? sizeof(struct udphdr) : sizeof(struct tcphdr));// htons(sizeof(buf));
	ip->ip_id = 0;
	ip->ip_off = 0;
	ip->ip_ttl = g_struct.ttl;
	ip->ip_p = (type & UDP_F) ? IPPROTO_UDP : IPPROTO_TCP;
	ip->ip_sum = 0;
	addr = nm_get_ip_interface();
	inet_pton(AF_INET, addr, &(ip->ip_src.s_addr));
	inet_pton(AF_INET, ip_dst, &(ip->ip_dst.s_addr));
	free(addr);
	return (ip);
}

struct tcphdr		*nm_configure_packet_tcp(char *buf, unsigned short port_dst,
			u_int seq,
			u_int ack_seq,
			u_int flags)
{
	struct iphdr *ip;
	struct tcphdr *tcp;

	ip = (struct iphdr*)(buf);
	tcp = (struct tcphdr*)(buf + (ip->ihl * 4));

	// tcp->source = htons(port_src);
	tcp->source = htons((unsigned short)g_struct.source_port);
	tcp->dest = htons(port_dst);
	tcp->doff = sizeof(struct tcphdr) >> 2;
	tcp->seq = htonl(seq);
	tcp->ack_seq = htonl(ack_seq);

	// Flags
	tcp->urg = (flags & F_TCP_URG) ? 1 : 0;
	tcp->ack = (flags & F_TCP_ACK) ? 1 : 0;
	tcp->psh = (flags & F_TCP_PSH) ? 1 : 0;
	tcp->rst = (flags & F_TCP_RST) ? 1 : 0;
	tcp->syn = (flags & F_TCP_SYN) ? 1 : 0;
	tcp->fin = (flags & F_TCP_FIN) ? 1 : 0;

	tcp->window = htons(1024);
	tcp->check = 0;
	tcp->urg_ptr = 0;
	tcp->check = (nm_pseudo_header_checksum(buf, ip->ihl * 4));
//	tcp->check = htons(0xdea4);
/*	printf("%4x\n",(tcp->check));
	printf("%4x\n",htons(tcp->check));
	printf("%4x\n",ntohs(tcp->check));
*/
	return (tcp);
}

struct udphdr		*nm_configure_packet_udp(char *buf, unsigned short port_dst)
{
	struct iphdr		*ip;
	struct udphdr	*udp;

	ip = (struct iphdr*)(buf);
	udp = (struct udphdr*)(buf + (ip->ihl * 4));

	udp->source = htons((unsigned short)g_struct.source_port);
	udp->dest = htons(port_dst);
	udp->len = htons(sizeof(struct udphdr));
	udp->check = 0;
	udp->check = nm_pseudo_header_checksum(buf, ip->ihl * 4);
//	udp->check = htons(0x7c9e);
	return (udp);
}
