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

		struct ip *ip;
		struct tcphdr *tcp;
		struct udphdr *udp;
		char *buf;

		buf = malloc(PACKET_BUF_SIZE);
		ft_memset(buf, 0, PACKET_BUF_SIZE);
		ip = nm_configure_packet_ip(buf, g_struct.ip_store[0].content);
		// ip = nm_configure_packet_ip(buf, data_sniffer.ip_str);

		// data_sniffer.port_dst = 53;
		// data_sniffer.port_src = 4242;
		// data_sniffer.seq = 42;
		// data_sniffer.ack_seq = 42;
		// data_sniffer.flags = flags;
		data_sniffer.filter_exp = "tcp";
		// data_sniffer.socket = s;
		// data_sniffer.sin = sin;
		// data_sniffer.buf = buf;


		int i = 0;
		while (i < 1024)
		{
			if (g_struct.ports[i] == 1)
				printf("Ports: %d\n", i);
			i++;
		}
		tcp = nm_configure_packet_tcp(buf, 4242, 53, 42, 42, flags);

		if (pthread_create(&th_sniffer, NULL, (void*)&nm_th_sniffer, (void*)&data_sniffer) == 0)
		{
			usleep(10);
			printf("Send once \n\n");
			sendto(s, buf, ip->ip_len, 0, (struct sockaddr*)&sin, sizeof(struct sockaddr));
		}
		pthread_join (th_sniffer, NULL);
	}
}
