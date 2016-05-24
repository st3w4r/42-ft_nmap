#include "ft_nmap.h"

void nm_recevie_once(int socket)
{
	char buf[1000];
	struct iphdr *iph;
	struct tcphdr *tcph;

	ft_memset(buf, 0, sizeof(buf));
	recv(socket, &buf, sizeof(buf), 0);
	iph = (struct iphdr*)buf;
	tcph = (struct tcphdr*)(buf + sizeof(struct ip));

	printf("IP id: %d\n", ntohs(iph->id));
	printf("IP ttl: %d\n", (iph->ttl));
	printf("TCP Port src: %d\n", ntohs(tcph->source));
	printf("TCP Port dst: %d\n", ntohs(tcph->dest));

}

void nm_send_once(int s, char *buf, u_int len, struct sockaddr_in sin)
{
	sendto(s, buf, len, 0, (struct sockaddr*)&sin, sizeof(struct sockaddr));
}

void	nm_loop()
{
	int s;
	struct sockaddr_in sin;
	char *buf;
	struct ip *ip;
	struct tcphdr *tcp;
	struct udphdr *udp;
	unsigned int flags;

	s = nm_open_socket();

	sin.sin_family = AF_INET;

	buf = malloc(PACKET_BUF_SIZE);
	ft_memset(buf, 0, PACKET_BUF_SIZE);
	ip = nm_configure_packet_ip(buf, g_struct.ip_store[0].content);

	flags = 0;
	if (g_struct.types & SYN_F)
		flags = F_TCP_SYN;
	else if (g_struct.types & NULL_F)
		flags = F_TCP_NULL;
	else if (g_struct.types & FIN_F)
		flags = F_TCP_FIN;
	else if (g_struct.types & XMAS_F)
		flags = F_TCP_FIN | F_TCP_PSH | F_TCP_URG;
	else if (g_struct.types & ACK_F)
		flags = F_TCP_ACK;
	else if (g_struct.types & UDP_F)
	{
		udp = nm_configure_packet_udp(buf, 20, 4242, 53);
		nm_send_once(s, buf, ip->ip_len, sin);
		nm_sniffer(g_struct.ip_store[0].content, 53, "udp");
	}
	
	if (!(g_struct.types & UDP_F))
	{
		tcp = nm_configure_packet_tcp(buf, 20, 4242, 53, 42, 42, flags, 1024);
		nm_send_once(s, buf, ip->ip_len, sin);
		
		nm_sniffer(g_struct.ip_store[0].content, 53,
			"tcp");
//			"tcp port 53 and src host 8.8.8.8");
/*
		while (42)
		{
			nm_recevie_once(s);
		}*/
	}
}
