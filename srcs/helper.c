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

unsigned short	nm_udp_checksum(char *buf, u_int size_ip)
{
	struct iphdr		*ip;
	struct udphdr		*udp;
	t_pseudo_header		pseudo_hdr;
	unsigned short		checksum;
	char				*buf_cal;

	ip = (struct iphdr*)(buf);
	udp = (struct udphdr*)(buf + size_ip);

	pseudo_hdr.saddr = ip->saddr;
	pseudo_hdr.daddr = ip->daddr;
	pseudo_hdr.reserved = 0;
	pseudo_hdr.protocol = ip->protocol;
	pseudo_hdr.len = htons(sizeof(struct udphdr));

	buf_cal = malloc(sizeof(t_pseudo_header) + sizeof(struct udphdr));
	ft_memset(buf_cal, 0, sizeof(t_pseudo_header) + sizeof(struct udphdr));

	ft_memcpy(buf_cal, &pseudo_hdr, sizeof(t_pseudo_header));
	ft_memcpy(buf_cal + sizeof(t_pseudo_header), udp, sizeof(struct udphdr));

//	printf("%u\n",((struct tcphdr*)(buf_cal + sizeof(t_pseudo_header)))->dest);
//	printf("%u\n",ip->protocol);


	checksum = nm_checksum((unsigned short*)buf_cal,
			sizeof(t_pseudo_header) + sizeof(struct udphdr));
	free(buf_cal);
	return (checksum);
}

unsigned short	nm_tcp_checksum(char *buf, u_int size_ip)
{
	struct iphdr		*ip;
	struct tcphdr		*tcp;
	t_pseudo_header	pseudo_hdr;
	unsigned short		checksum;
	char				*buf_cal;

	ip = (struct iphdr*)(buf);
	tcp = (struct tcphdr*)(buf + size_ip);

	pseudo_hdr.saddr = ip->saddr;
	pseudo_hdr.daddr = ip->daddr;
	pseudo_hdr.reserved = 0;
	pseudo_hdr.protocol = ip->protocol;
	pseudo_hdr.len = htons(sizeof(struct tcphdr));

	buf_cal = malloc(sizeof(t_pseudo_header) + sizeof(struct tcphdr));
	ft_memset(buf_cal, 0, sizeof(t_pseudo_header) + sizeof(struct tcphdr));

	ft_memcpy(buf_cal, &pseudo_hdr, sizeof(t_pseudo_header));
	ft_memcpy(buf_cal + sizeof(t_pseudo_header), tcp, sizeof(struct tcphdr));

//	printf("%u\n",((struct tcphdr*)(buf_cal + sizeof(t_pseudo_header)))->dest);
//	printf("%u\n",ip->protocol);

//	printf("IP: %8x\n", ntohs((ip->daddr)));
//	printf("IP: %d\n", ip->saddr);

	checksum = nm_checksum((unsigned short*)buf_cal,
			sizeof(t_pseudo_header) + sizeof(struct tcphdr));
	free(buf_cal);
	printf("Checksum: %4x\n", checksum);
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
