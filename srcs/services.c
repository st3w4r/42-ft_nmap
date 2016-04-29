#include "ft_nmap.h"

char	*get_service_name(int port, char *protocol)
{
	int	i;
	t_service	services_list[]  =
	{
		{ "ftp", 21, "tcp" },
		{ "ftp", 21, "udp" },
		{ "http", 80, "tcp" },
		{ "http", 80, "udp" },
		{ "https", 443, "tcp" },
		{ "https", 443, "udp" },
		{ 0, 0, 0 }
	};
	
	i = 0;
	while (services_list[i].name != NULL)
	{
		if (services_list[i].port == port &&
				ft_strcmp(protocol, services_list[i].protocol) == 0)
			return (services_list[i].name);
		i++;
	}
	return ("Unassigned");
}
