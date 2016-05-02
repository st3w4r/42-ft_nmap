# include "ft_nmap.h"

void	nm_get_ip_file(char *file)
{
	int fd;
	int result;
	char buf[16];

	result = 0;
//	g_struct.ip_store = ft_lstnew("ip", sizeof(char*));
	ft_bzero(buf, sizeof(buf));
	if ((fd = open(file, O_RDONLY)) <= 0)
	{
		printf("Error: Open file\n");
		exit(1);
	}
	while ((result = read(fd, buf, sizeof(buf))) > 0)
	{
		if (buf[15] != '\n')
		{
			printf("Error: Parse file\n");
			exit(1);
		}
		else
		{
			printf("Buf: %s\n", buf);
		}

		ft_bzero(buf, sizeof(buf));
	}
	close(fd);
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
