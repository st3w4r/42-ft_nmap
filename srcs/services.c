#include "ft_nmap.h"

char	*nm_get_service_name(int port, char *protocol)
{
	struct servent *service;
	service = getservbyport(htons(port), protocol);
	if (service == NULL)
		return ("Unassigned");
	return (service->s_name);
}
