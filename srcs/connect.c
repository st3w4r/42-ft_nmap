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

struct ip		*nm_configure_packet_ip(char *buf, char *ip_dst)
{
	struct ip *ip;

	ip = (struct ip*)(buf);
	ip->ip_v = 4;
	ip->ip_hl = sizeof(*ip) >> 2;
	ip->ip_tos = 0;
	ip->ip_len = sizeof(struct ip) + sizeof(struct tcphdr);// htons(sizeof(buf));
	ip->ip_id = 0;
	ip->ip_off = 0;
	ip->ip_ttl = 42;
	ip->ip_p = (g_struct.types & UDP_F) ? IPPROTO_UDP : IPPROTO_TCP;
	ip->ip_sum = 0;
	inet_pton(AF_INET, "0.0.0.0", &(ip->ip_src.s_addr));
	inet_pton(AF_INET, ip_dst, &(ip->ip_dst.s_addr));
	return (ip);
}

struct tcphdr		*nm_configure_packet_tcp(char *buf, u_int size_ip,
			unsigned short port_src, unsigned short port_dst,
			u_int seq,
			u_int ack_seq,
			u_int flags,
			unsigned short window
		)
{
	struct ip *ip;
	struct tcphdr *tcp;

	ip = (struct ip*)(buf);
	tcp = (struct tcphdr*)(buf + size_ip);

	tcp->source = htons(port_src);
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

	tcp->window = htons(window);
	tcp->check = 0;
	tcp->urg_ptr = 0;
	tcp->check = (nm_tcp_checksum(buf, size_ip));
	tcp->check = htons(0xe26c);
/*	printf("%4x\n",(tcp->check));
	printf("%4x\n",htons(tcp->check));
	printf("%4x\n",ntohs(tcp->check));
*/	
	return (tcp);
}

struct udphdr		*nm_configure_packet_udp(char *buf, u_int size_ip,
						unsigned short port_src, unsigned short port_dst)
{
	struct ip		*ip;
	struct udphdr	*udp;

	ip = (struct ip*)(buf);
	udp = (struct udphdr*)(buf + size_ip);

	udp->source = port_src;
	udp->dest = port_dst;
	udp->len = htons(sizeof(struct udphdr));
	udp->check = 0;
	udp->check = nm_udp_checksum(buf, size_ip);
	return (udp);
}
