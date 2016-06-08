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
	unsigned int flags;

	s = nm_open_socket();

	sin.sin_family = AF_INET;


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
/*	else if (g_struct.types & UDP_F)
	{
		udp = nm_configure_packet_udp(buf, 20, 4242, 53);
		nm_send_once(s, buf, ip->ip_len, sin);
		nm_sniffer(g_struct.ip_store[0].content, 53, "udp");
	}
*/
	if (!(g_struct.types & UDP_F))
	{

		pthread_t th_sniffer;
		t_th_sniffer data_sniffer;

		data_sniffer.port_dst = 53;
		data_sniffer.port_src = 4242;
		data_sniffer.seq = 42;
		data_sniffer.ack_seq = 42;
		data_sniffer.flags = flags;
		data_sniffer.filter_exp = "tcp port 53 and src host 8.8.8.8";
		data_sniffer.socket = s;
		data_sniffer.sin = sin;

		if (pthread_create(&th_sniffer, NULL, (void*)&nm_th_sniffer, (void*)&data_sniffer) == 0)
		{
		}
		pthread_join (th_sniffer, NULL);
	}
}
