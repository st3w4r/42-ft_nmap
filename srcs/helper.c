# include "ft_nmap.h"

void print_ip_store(t_list *elem)
{
	printf("IP: %s\n", elem->content);
}

void	nm_get_ip_file(char *file)
{
	int fd;
	char *line;
	t_list	*ip_entry;

	if ((fd = open(file, O_RDONLY)) <= 0)
		ft_error_str("Error: Open file\n");
	while (ft_get_next_line(fd, &line) > 0)
	{
		if ((ip_entry = malloc(sizeof(t_list))) < 0)
			ft_malloc_error();
		if (nm_check_ip_v4(line))
		{
			ip_entry->content = ft_strdup(line);
			if (g_struct.ip_store)
				ft_lstadd(&g_struct.ip_store, ip_entry);
			else
				g_struct.ip_store = ft_lstnew(line, ft_strlen(line) + 1);
		}
	}
	close(fd);
	ft_lstiter(g_struct.ip_store, print_ip_store);
}

/*
 * Check IPv4
 * 4 section
 * Split by dots
 * Is number
 * Convert to int
 * From 0 to 255
 */

t_bool	nm_check_ip_v4(char *ip)
{
	char	**ip_section;
	int		ip_part;
	int		i;
	t_bool	validate;

	i = 0;
	validate = TRUE;
	if ((ip_section = ft_strsplit(ip, '.')) == NULL)
		return (FALSE);
	if (ft_arrlen(ip_section) != 4)
		validate = FALSE;
	while (validate && ip_section[i] != NULL)
	{
		if (ft_is_number(ip_section[i]) == FALSE)
		{
			validate = FALSE;
			break;
		}
		ip_part = ft_atoi(ip_section[i]);
		if (ip_part < 0 || ip_part > 255)
		{
			validate = FALSE;
			break;
		}
		i++;
	}
	if (ip_section)
		ft_arrfree(&ip_section);
	return (validate);
}
