# include "ft_nmap.h"

char	*nm_get_ip_interface()
{
	struct ifaddrs *ifap;
	struct ifaddrs *ifa;
	char *addr;

	addr = NULL;
	if (getifaddrs(&ifap) < 0)
		ft_error_str_exit("Error getifaddrs\n");
	ifa = ifap;
	while (ifa->ifa_next != NULL)
	{
		if (ifa->ifa_addr->sa_family == AF_INET &&
			ft_strcmp("eth0", ifa->ifa_name) == 0)
		{
			addr = ft_strdup(inet_ntoa(((struct sockaddr_in*)ifa->ifa_addr)->sin_addr));
			break;
		}
		ifa = ifa->ifa_next;
	}
	freeifaddrs(ifap);
	return (addr);
}

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

unsigned short	nm_pseudo_header_checksum(char *buf, u_int size_ip)
{
	char						*header;
	t_pseudo_header	pseudo_hdr;
	unsigned short	checksum;
	char						*buf_cal;
	u_int						size_protocol;
	struct iphdr		*ip;

	ip = (struct iphdr*)(buf);
	header = (buf + size_ip);
	size_protocol = ip->tot_len - size_ip;

	pseudo_hdr.saddr = ip->saddr;
	pseudo_hdr.daddr = ip->daddr;
	pseudo_hdr.reserved = 0;
	pseudo_hdr.protocol = ip->protocol;
	pseudo_hdr.len = htons(size_protocol);

	buf_cal = malloc(sizeof(t_pseudo_header) + size_protocol);
	ft_memset(buf_cal, 0, sizeof(t_pseudo_header) + size_protocol);

	ft_memcpy(buf_cal, &pseudo_hdr, sizeof(t_pseudo_header));
	ft_memcpy(buf_cal + sizeof(t_pseudo_header), header, size_protocol);

	checksum = nm_checksum((unsigned short*)buf_cal,
			sizeof(t_pseudo_header) + size_protocol);
	free(buf_cal);
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
