# include "ft_nmap.h"

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
