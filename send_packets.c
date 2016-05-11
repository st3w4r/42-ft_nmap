#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <pcap.h>

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

struct tcphdr *nm_configure_packet_tcp(char *buf, u_int size_ip)
{
	struct tcphdr *tcp;

	tcp = (struct tcphdr*)(buf + size_ip);

	tcp->source = htons(4242);
	tcp->dest = htons(8080);
	tcp->doff = sizeof(struct tcphdr) >> 2;
	tcp->seq = htonl(42);
	tcp->ack_seq = htonl(42);

	// Flags
	tcp->urg = 1;
	tcp->ack = 1;
	tcp->psh = 1;
	tcp->rst = 1;
	tcp->syn = 1;
	tcp->fin = 1;

	tcp->window = htons(42);
	tcp->check = 0;
	tcp->urg_ptr = 0;

	return (tcp);
}

int main(int argc, char **argv)
{
	int s;
	char buf[200];
	struct sockaddr *dest_addr;
	struct sockaddr_in sin;

	struct ethhdr *ethernet;
	struct ip *ip;
	struct tcphdr *tcp;


	u_int size_ip;
	u_int size_tcp;

	if (argc != 2)
	{
		printf("Argument needed\n");
		exit(1);
	}
	// dest_addr = (struct sockaddr *)malloc(sizeof(struct sockaddr));
	//	sin = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));

	//	bzero(buf, sizeof(buf));
	//	ia = ((struct sockaddr_in*)dest_addr);
	//	inet_aton(argv[1], &((struct sockaddr_in*)dest_addr)->sin_addr);
	//	inet_aton(argv[1], &(sin.sin_addr));
	//	inet_aton(argv[1], pin);

	sin.sin_family = AF_INET;
	// sin.sin_port = htons(atoi(argv[2]));

	//	printf("IP: %s\n", inet_ntoa(((struct sockaddr_in*)dest_addr)->sin_addr));
	//	printf("IP: %s\n", inet_ntoa(sin.sin_addr));

	s = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	int hincl = 1;
	setsockopt(s, IPPROTO_IP, IP_HDRINCL, &hincl, sizeof(hincl));
	// ethernet = (struct ethhdr*)(buf);
	// printf("%lu\n", sizeof(*ethernet));
	// printf("%u\n", ETH_HLEN);
	// ip = (struct ip*)(buf);
	// printf("%lu\n", sizeof(struct ip));
	// printf("%lu\n", sizeof(struct tcphdr));
	// size_ip = 5 * 4;
/*
	if (size_ip < 20) {
		printf("Invalid IP header length %u\n", size_ip);
		exit(1);
	}
	*/
	// tcp = (struct tcphdr*)(buf + sizeof(struct ip));
/*
size_tcp = tcp->doff * 4;
	if (size_tcp < 20) {
		printf("Invalid TCP header length %u\n", size_tcp);
		exit(1);
	}
*/

	// ip = (struct ip*)(buf);
	// tcp = (struct tcphdr*)(buf + size_ip);

	memset(buf, 0, sizeof(buf));
	ip = nm_configure_packet_ip(buf, argv[1]);
	tcp = nm_configure_packet_tcp(buf, sizeof(struct ip));
	// ip->ip_v = 4;
	// ip->ip_hl = sizeof(*ip) >> 2;
	// ip->ip_tos = 0;
	// ip->ip_len = sizeof(struct ip) + sizeof(struct tcphdr);// htons(sizeof(buf));
	// ip->ip_id = 0;
	// ip->ip_off = 0;
	// ip->ip_ttl = 42;
	// ip->ip_p = IPPROTO_TCP;
	// ip->ip_sum = 0;
	// inet_pton(AF_INET, "0.0.0.0", &(ip->ip_src.s_addr));
	// inet_pton(AF_INET, argv[1], &(ip->ip_dst.s_addr));
	//
	// tcp->source = htons(4242);
	// tcp->dest = htons(8080);
	// tcp->doff = sizeof(struct tcphdr) >> 2;
	// tcp->seq = htonl(42);
	// tcp->ack_seq = htonl(42);
	//
	// // Flags
	// tcp->urg = 1;
	// tcp->ack = 1;
	// tcp->psh = 1;
	// tcp->rst = 1;
	// tcp->syn = 1;
	// tcp->fin = 1;
	//
	// tcp->window = htons(42);
	// tcp->check = 0;
	// tcp->urg_ptr = 0;
	//
	// printf("%04x\n", nm_checksum((unsigned short*)tcp, sizeof(*tcp)));
	// printf("%04x\n", htons(nm_checksum((unsigned short*)tcp, sizeof(*tcp))));
	// printf("%04x\n", nm_checksum((unsigned short*)buf, sizeof(buf)));
	// printf("%04x\n", nm_checksum((unsigned short*)tcp, sizeof(*tcp) + sizeof(*ip)));
	// ip->ip_sum = nm_checksum((unsigned short*)buf, sizeof(struct ip) + sizeof(struct tcphdr));
	// printf("%hu\n", nm_checksum((unsigned short*)buf, sizeof(struct ip) + sizeof(struct tcphdr)));

	sendto(s, buf, ip->ip_len, 0, (struct sockaddr*)&sin, sizeof(struct sockaddr));

	return (0);
}
