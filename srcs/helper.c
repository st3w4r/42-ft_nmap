# include "ft_nmap.h"

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

unsigned short	nm_tcp_checksum(char *buf, u_int size_ip)
{
	struct ip *ip;
	struct tcphdr *tcp;
	t_tcp_pseudo_header	pseudo_hdr;
	unsigned short	checksum;
	unsigned short	cksum_pseudo;
	unsigned short	cksum_tcp;
	char *buf_cal;

	ip = (struct ip*)(buf);
	tcp = (struct tcphdr*)(buf + size_ip);

	pseudo_hdr.saddr = ip->ip_src.s_addr;
	pseudo_hdr.daddr = ip->ip_dst.s_addr;
	pseudo_hdr.reserved = 0;
	pseudo_hdr.protocol = ip->ip_p;
	pseudo_hdr.tcp_len = sizeof(struct tcphdr);

//	printf("%lu\n", sizeof(t_tcp_pseudo_header) * 8);
	buf_cal = malloc(sizeof(t_tcp_pseudo_header) + sizeof(struct tcphdr));
	ft_memset(buf_cal, 0, sizeof(t_tcp_pseudo_header) + sizeof(struct tcphdr));

	ft_memcpy(buf_cal, &pseudo_hdr, sizeof(t_tcp_pseudo_header));
	ft_memcpy(buf_cal + sizeof(t_tcp_pseudo_header), tcp, sizeof(struct tcphdr));

	//printf("%u\n",((struct tcphdr*)(buf_cal + sizeof(t_tcp_pseudo_header)))->dest);
	printf("%u\n",((struct tcphdr*)(buf_cal + sizeof(t_tcp_pseudo_header)))->dest);
	printf("%u\n",ip->ip_p);

//	cksum_pseudo = nm_checksum((unsigned short*)&pseudo_hdr, sizeof(t_tcp_pseudo_header));
//	cksum_tcp = nm_checksum((unsigned short*)tcp, sizeof(*tcp));
	checksum = nm_checksum((unsigned short*)buf_cal,
			sizeof(t_tcp_pseudo_header) + sizeof(struct tcphdr));

	return (checksum);
}

void	nm_add_ip_to_ip_store(char *ip)
{
	t_list	*ip_entry;

	if ((ip_entry = malloc(sizeof(t_list))) < 0)
		ft_malloc_error();
	ip_entry->content = ft_strdup(ip);
	if (g_struct.ip_store)
		ft_lstadd(&g_struct.ip_store, ip_entry);
	else
		g_struct.ip_store = ft_lstnew(ip, ft_strlen(ip) + 1);

}

void	nm_get_ip_file(char *file)
{
	int fd;
	char *line;

	if ((fd = open(file, O_RDONLY)) <= 0)
		ft_error_str_exit("Error: can't open file\n");
	while (ft_get_next_line(fd, &line) > 0)
		if (nm_check_ip_v4(line))
			nm_add_ip_to_ip_store(line);
	close(fd);
}

t_bool	nm_check_ip_v4(char *ip)
{
	struct sockaddr_in sa;
	int result;

	result = inet_pton(AF_INET, ip, &(sa.sin_addr));
	return (result != 0);
}
