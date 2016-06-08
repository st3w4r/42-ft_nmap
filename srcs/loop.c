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

char *nm_build_filter(unsigned short ports_dst, char *ip_str);


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


		printf("speedup: %d\n", g_struct.speedup);
		int i = 0;
		int j = 0;
		while (i < 1024)
		{
			if (g_struct.ports[i] == 1)
				j++;
			i++;
		}

		t_th_sniffer data_sniffer[j];
		pthread_t th_sniffer;
		j = 0;
		i = 0;
		while (i < 1024)
		{
			if (g_struct.ports[i] == 1)
			{
				printf("Port: %d\n", i);
				data_sniffer[j].filter_exp = nm_build_filter(i, g_struct.ip_store[0].content);
				// printf("filter_exp: %s\n", data_sniffer[j].filter_exp);
				data_sniffer[j].port_dst = i;
				data_sniffer[j].port_src = 4242;
				data_sniffer[j].seq = 42;
				data_sniffer[j].ack_seq = 42;
				data_sniffer[j].flags = flags;
				data_sniffer[j].socket = s;
				data_sniffer[j].sin = sin;

				if (pthread_create(&th_sniffer, NULL, (void*)&nm_th_sniffer, (void*)&data_sniffer[j]) == 0)
				{

				}
				pthread_join (th_sniffer, NULL);
				j++;
				// free(data_sniffer[j].filter_exp);
			}
			i++;
		}
	}
}

char *nm_build_filter(unsigned short ports_dst, char *ip_str)
{

	char *str;
	char *port;
	// char *start;
	// char *middle;

	// str = malloc(10);
	// str = ft_strdup("tcp");

	port = NULL;
	str = NULL;
	// start = ft_strdup("tcp port ");
	// middle = ft_strdup(" and src host ");
	port = ft_itoa((int)ports_dst);
	str = (char*)malloc(1000);
	ft_bzero(str, 1000);
	str = ft_strcat(str, "tcp port ");
	str = ft_strcat(str, port);
	str = ft_strcat(str, " and src host ");
	str = ft_strcat(str, ip_str);

	printf("str: %s\n", str);
	free(port);
	return (str);
}
