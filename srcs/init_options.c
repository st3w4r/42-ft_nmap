#include "ft_nmap.h"

char		*getIP(char *str)
{
	struct sockaddr_in *ipv4	= NULL;
	struct addrinfo* result;
	char ip[INET_ADDRSTRLEN ];

	if (getaddrinfo(str, NULL, NULL, &result) != 0)
	{
		printf("nmap: unknown host\n");
		nm_usage();
		exit(0);
	}

	while (result->ai_next) {
		if (result->ai_family == AF_INET)
		{
			ipv4 = (struct sockaddr_in *)result->ai_addr;
			inet_ntop(result->ai_family, &(ipv4->sin_addr), ip, sizeof(ip));
			return ft_strdup(ip);
		}
		result = result->ai_next;
	}
	printf("nmap: unknown host\n");
	nm_usage();
	exit(0);
	return NULL;
}


int nm_init_ip_opt(char *arg)
{
	// if (nm_check_ip_v4(arg) == FALSE)
	// 	return (-1);
	nm_add_ip_to_ip_store(getIP(arg));
	return (0);
}
int nm_init_file_opt(char *arg)
{
  nm_get_ip_file(arg);
  return (0);
}
int nm_init_speedup_opt(char *arg)
{
  int speedup;

	speedup = 1;
  if (!ft_is_number(arg))
    return (-1);
  speedup = ft_atoi(arg);
  if (speedup <= 0 || speedup > 250)
    return (-1);
  else
    g_struct.speedup = speedup;
	g_struct.th_sniffer = (pthread_t*)malloc(sizeof(pthread_t) * g_struct.speedup);
  return (0);
}

int nm_init_spoof_opt(char *arg)
{
  ft_putstr("nm_init_spoof_opt\n");
  printf("argtype: %s\n", arg);

  return (0);
}

int							nm_init_pt_opt(char *arg)
{
	int pt;

	if (!ft_is_number(arg))
		return (-1);
	pt = ft_atoi(arg);
	if (pt < 1 || pt > 10)
		return (-1);
	else
		g_struct.packet_time = pt * 1000;
	return (0);
}

int nm_init_ttl_opt(char *arg)
{
  int ttl;

  if (!ft_is_number(arg))
    return (-1);
  ttl = ft_atoi(arg);
  if (ttl < 1 || ttl > 255)
    return (-1);
  else
    g_struct.ttl = ttl;
  return (0);
}
int nm_init_o_opt(char *arg)
{
  ft_putstr("nm_init_o_opt\n");
  printf("argtype: %s\n", arg);

  return (0);
}
int nm_init_s_opt(char *arg)
{
  ft_putstr("nm_init_s_opt\n");
  printf("argtype: %s\n", arg);

  return (0);
}
int nm_init_g_opt(char *arg)
{
	int port;

  if (!ft_is_number(arg))
    return (-1);
  port = ft_atoi(arg);
  if (port < 1 || port > 65536)
    return (-1);
  else
    g_struct.source_port = port;
  return (0);
}
