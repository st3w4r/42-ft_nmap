#include "ft_nmap.h"

void nm_recevie_once()
{

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

	s = nm_open_socket();

	sin.sin_family = AF_INET;

	buf = malloc(PACKET_BUF_SIZE);
	ft_memset(buf, 0, PACKET_BUF_SIZE);
	ip = nm_configure_packet_ip(buf, g_struct.ip_store[0].content);
	tcp = nm_configure_packet_tcp(buf, 20, 4242, 53, 42, 42, F_TCP_SYN, 42);

	// while (42)
		nm_send_once(s, buf, ip->ip_len, sin);
}
