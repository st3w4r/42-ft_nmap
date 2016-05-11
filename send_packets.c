#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <pcap.h>

# define PACKET_BUF_SIZE 40
enum		e_flags_tcp
{
	F_TCP_URG = 1 << 0,
	F_TCP_ACK = 1 << 1,
	F_TCP_PSH = 1 << 2,
	F_TCP_RST = 1 << 3,
	F_TCP_SYN = 1 << 4,
	F_TCP_FIN = 1 << 5
};

unsigned short	nm_checksum(unsigned short *data, int len)
{
	unsigned long checksum;

	checksum = 0;
	while (len > 1)
	{
		checksum = checksum + *data++;
		len = len - sizeof(unsigned short);
	}
	if (len)
		checksum = checksum + *(unsigned char*)data;
	checksum = (checksum >> 16) + (checksum & 0xffff);
	checksum = checksum + (checksum >> 16);
	return (unsigned short)(~checksum);
}

struct ip *nm_configure_packet_ip(char *buf, char *ip_dst)
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
	ip->ip_p = IPPROTO_TCP;
	ip->ip_sum = 0;
	inet_pton(AF_INET, "0.0.0.0", &(ip->ip_src.s_addr));
	inet_pton(AF_INET, ip_dst, &(ip->ip_dst.s_addr));

	return (ip);
}

struct tcphdr *nm_configure_packet_tcp(char *buf, u_int size_ip,
			unsigned short port_src, unsigned short port_dst,
			u_int seq,
			u_int ack_seq,
			u_int flags,
			unsigned short window
		)
{
	struct tcphdr *tcp;

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
	tcp->check = htons(0);
	tcp->urg_ptr = 0;

	return (tcp);
}

int main(int argc, char **argv)
{
	int s;
	char *buf;
	struct sockaddr_in sin;

	struct ip *ip;
	struct tcphdr *tcp;

	u_int size_ip;
	u_int size_tcp;

	if (argc != 2)
	{
		printf("Argument needed\n");
		exit(1);
	}

	buf = malloc(PACKET_BUF_SIZE);

	sin.sin_family = AF_INET;

	s = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	int hincl = 1;
	setsockopt(s, IPPROTO_IP, IP_HDRINCL, &hincl, sizeof(hincl));

	memset(buf, 0, PACKET_BUF_SIZE);
	ip = nm_configure_packet_ip(buf, argv[1]);
	tcp = nm_configure_packet_tcp(buf, sizeof(struct ip), 4242, 8080, 42, 42, F_TCP_SYN | F_TCP_FIN, 42);

	sendto(s, buf, ip->ip_len, 0, (struct sockaddr*)&sin, sizeof(struct sockaddr));

	return (0);
}
