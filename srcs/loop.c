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
t_th_sniffer nm_build_data_sniffer(unsigned short port_dst, int s, char *ip_str, struct sockaddr_in sin);


void	nm_loop()
{
	int s;
	struct sockaddr_in sin;
	char *buf;
	unsigned int flags;

	s = nm_open_socket();

	sin.sin_family = AF_INET;


	flags = 1;
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
	else
		flags = F_TCP_FIN | F_TCP_PSH | F_TCP_URG | F_TCP_ACK | F_TCP_NULL | F_TCP_SYN;
/*	else if (g_struct.types & UDP_F)
	{
		udp = nm_configure_packet_udp(buf, 20, 4242, 53);
		nm_send_once(s, buf, ip->ip_len, sin);
		nm_sniffer(g_struct.ip_store[0].content, 53, "udp");
	}
*/
nm_ip_loop(s, sin, flags);
	if (!(g_struct.types & UDP_F))
	{


	}
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

}


void nm_scans_loop(unsigned short port_dst, char *ip_str, int s, struct sockaddr_in sin)
{
	t_th_sniffer data_sniffer;
	pthread_t th_sniffer[g_struct.speedup];

	int scan = 0;

	while (scan < 40)
	{
		printf("scan: %d, speedup: %d, free thread: %d\n", scan,g_struct.speedup, g_struct.thread_free);
		if (g_struct.thread_free >= 0)
		{
			data_sniffer = nm_build_data_sniffer(port_dst, s, ip_str, sin);
			if (g_struct.types & SYN_F)
				data_sniffer.flags = F_TCP_SYN;
			else if (g_struct.types & NULL_F)
				data_sniffer.flags = F_TCP_NULL;
			else if (g_struct.types & FIN_F)
				data_sniffer.flags = F_TCP_FIN;
			else if (g_struct.types & XMAS_F)
				data_sniffer.flags = F_TCP_FIN | F_TCP_PSH | F_TCP_URG;
			else if (g_struct.types & ACK_F)
				data_sniffer.flags = F_TCP_ACK;
			// g_struct.types >>= 1;
			if (pthread_create(&th_sniffer[g_struct.thread_free], NULL, (void*)&nm_th_sniffer, (void*)&data_sniffer) == 0)
			{
				scan++;
				printf("Thread creer: %d\n", g_struct.thread_free);
				g_struct.thread_free--;
			}
			else
				printf("Error: pthread create\n");
		}
		else
		{
			int i = 0;
			while (i <= g_struct.speedup)
			{
				if (pthread_join(th_sniffer[i], NULL) == 0)
					g_struct.thread_free++;
				i++;
			}
		}
	}

}

void nm_ports_loop(char *ip_str, int s, struct sockaddr_in sin, unsigned int flags)
{
	int port;

	port = 0;
	while (port < 1024)
	{
		if (g_struct.ports[port] == 1)
			nm_scans_loop(port, ip_str, s, sin);
		port++;
	}
}

t_th_sniffer nm_build_data_sniffer(unsigned short port_dst, int s, char *ip_str, struct sockaddr_in sin)
{
	t_th_sniffer data_sniffer;

	data_sniffer.filter_exp = ft_strdup(nm_build_filter(port_dst, ip_str));
	data_sniffer.port_dst = port_dst;
	data_sniffer.port_src = 4242;
	data_sniffer.seq = 42;
	data_sniffer.ack_seq = 42;
	data_sniffer.socket = s;
	data_sniffer.sin = sin;

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
