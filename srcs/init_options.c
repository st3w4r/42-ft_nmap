#include "ft_nmap.h"

int nm_init_ip_opt(char *arg)
{
	if (nm_check_ip_v4(arg) == FALSE)
		return (-1);
	nm_add_ip_to_ip_store(arg);
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

  if (!ft_is_number(arg))
    return (-1);
  speedup = ft_atoi(arg);
  if (speedup < 0 || speedup > 250)
    return (-1);
  else
    g_struct.speedup = speedup;
	g_struct.thread_free = g_struct.speedup;

	// g_struct.th_store[g_struct.speedup];
  return (0);
}

int nm_init_spoof_opt(char *arg)
{
  ft_putstr("nm_init_spoof_opt\n");
  printf("argtype: %s\n", arg);

  return (0);
}
int nm_init_ttl_opt(char *arg)
{
  ft_putstr("nm_init_ttl_opt\n");
  printf("argtype: %s\n", arg);
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
  ft_putstr("nm_init_g_opt\n");
  printf("argtype: %s\n", arg);

  return (0);
}
