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
void nm_ip_loop(int s, struct sockaddr_in sin, unsigned int flags);
void nm_ports_loop(char *ip_str, int s, struct sockaddr_in sin, unsigned int flags);

t_th_sniffer *nm_build_data_sniffer(unsigned short port_dst, int s, char *ip_str, struct sockaddr_in sin, enum e_scan_types type);
int free_threads();


void	nm_loop()
{
	int s;
	struct sockaddr_in sin;
	char *buf;
	unsigned int flags = 0;
	s = nm_open_socket();

	sin.sin_family = AF_INET;


	nm_ip_loop(s, sin, flags);

	// int i;
	// i = 0;
	// while (i <= g_struct.speedup)
	// {
	// 	pthread_join(g_struct.th_sniffer[i], NULL);
	// 	i++;
	// }
	// // pthread_join(g_struct.th_sniffer[i], NULL);

	// if (!(g_struct.types & UDP_F))
	// {
	// }
}

void nm_ip_loop(int s, struct sockaddr_in sin, unsigned int flags)
{
	char *ip_str;
	int i;

	i = 0;
	ip_str = NULL;
	while (g_struct.ip_store[i].content)
	{
		nm_ports_loop(g_struct.ip_store[i].content, s, sin, flags);
		i++;
	}
	if (g_struct.thread_free > 0)
		free_threads();
	pthread_exit(NULL);
}

int nm_build_flag(enum e_scan_types type)
{
	int flags;

	flags = 0;
	if (type & SYN_F)
		flags = F_TCP_SYN;
	else if (type & NULL_F)
		flags = F_TCP_NULL;
	else if (type & FIN_F)
		flags = F_TCP_FIN;
	else if (type & XMAS_F)
		flags = F_TCP_FIN | F_TCP_PSH | F_TCP_URG;
	else if (type & ACK_F)
		flags = F_TCP_ACK;
	else
		flags = F_TCP_FIN | F_TCP_PSH | F_TCP_URG | F_TCP_ACK | F_TCP_NULL | F_TCP_SYN;
	return flags;
}

int free_threads()
{
	int j;
	int ret;
	int check;

	j = 0;
	ret = -1;
	check = 0;
	while (j <= g_struct.speedup)
	{
		if (g_struct.thread_occupied[j] == 1)
		{
			if ((ret = pthread_join(g_struct.th_sniffer[j], NULL)) == 0)
			{
				g_struct.thread_occupied[j] = 0;
				g_struct.thread_free--;
				// check++;
				printf("Liberation du thread: %d, thread_free: %d\n", j, g_struct.thread_free);
			}
		// 	if (check == 0)
		// 		j = -1;
		}
		j++;
	}
	return (1);
}

void nm_scans_loop(t_th_sniffer *data_sniffer, unsigned short port_dst, char *ip_str, int s, struct sockaddr_in sin)
{
	int i = 0;

	while (i < 7)
	{
		if (g_struct.types & (1 << i))
		{

			data_sniffer = nm_build_data_sniffer(port_dst, s, ip_str, sin, (1 << i));

			if (g_struct.thread_free == g_struct.speedup - 1)
				free_threads();
			if (pthread_create(&g_struct.th_sniffer[g_struct.thread_free], NULL, (void*)&nm_th_sniffer, (void*)data_sniffer) == 0)
			{
				g_struct.thread_occupied[g_struct.thread_free] = 1;
				printf("Creation du thread : %d/%d, port: %d, scan type %d\n", g_struct.thread_free, g_struct.speedup, port_dst, data_sniffer->flags);
				g_struct.thread_free++;
				i++;
			}
		}
		else
			printf("Plus de Threads\n");
		}
		else
			i++;
	}
	printf("Sortie de scan loop\n");
}

void nm_ports_loop(char *ip_str, int s, struct sockaddr_in sin, unsigned int flags)
{
	int port;

	port = 0;
	while (port < 1024)
	{
		if (g_struct.ports[port] == 1)
		{
			t_th_sniffer data_sniffer;
			// if (g_struct.thread_free == g_struct.speedup - 1)
				// free_threads();
			nm_scans_loop(&data_sniffer, port, ip_str, s, sin);
		}
		port++;
	}
	printf("Dernier free\n");

}

t_th_sniffer *nm_build_data_sniffer(unsigned short port_dst, int s, char *ip_str, struct sockaddr_in sin, enum e_scan_types type)
{
	t_th_sniffer *data_sniffer;
	data_sniffer = (t_th_sniffer*)malloc(sizeof(t_th_sniffer));

	data_sniffer->filter_exp = ft_strdup(nm_build_filter(port_dst, ip_str));
	data_sniffer->port_dst = port_dst;
	data_sniffer->port_src = 4242;
	data_sniffer->seq = 42;
	data_sniffer->ack_seq = 42;
	data_sniffer->socket = s;
	data_sniffer->sin = sin;
	data_sniffer->flags = nm_build_flag(type);

	return data_sniffer;
}

char *nm_build_filter(unsigned short ports_dst, char *ip_str)
{
	char *str;
	char *port;


	port = NULL;
	str = NULL;
	str = (char*)malloc(1000);
	ft_bzero(str, 1000);
	port = ft_itoa((int)ports_dst);
	str = ft_strcat(str, "tcp port ");
	str = ft_strcat(str, port);
	str = ft_strcat(str, " and src host ");
	str = ft_strcat(str, ip_str);

	free(port);
	return (str);
}
