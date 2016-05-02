#include "ft_nmap.h"

int nm_ports_opt_get_range(char *ports)
{
  int j;
  char **arrRange;

  j = 0;
  arrRange = NULL;
  arrRange = ft_strsplit(ports, '-');
  while(arrRange[j])
  {
    printf("PortRange: %s\n", arrRange[j]);
    j++;
  }

  return (j);
}

int nm_init_ports_opt(char *arg)
{
  ft_putstr("nm_init_ports_opt\n");

  char **arrOne;
  int counter;

  counter = 0;
  arrOne= NULL;

  arrOne = ft_strsplit(arg, ',');
  int i = 0;
  int j;
  while (arrOne[i])
  {
    if (ft_strchr(arrOne[i], '-'))
      counter += nm_ports_opt_get_range(arrOne[i]);
    else
    {
      printf("Port: %s\n", arrOne[i]);
      counter++;
    }
    i++;
  }

  printf("Counter: %d\n", counter);
  free(arrOne);
  return (0);
}
int nm_init_ip_opt(char *arg)
{
  ft_putstr("nm_init_ip_opt\n");
  printf("argtype: %s\n", arg);

  return (0);
}
int nm_init_file_opt(char *arg)
{
  ft_putstr("nm_init_file_opt\n");
  printf("argtype: %s\n", arg);
  nm_get_ip_file(arg);
  return (0);
}
int nm_init_speedup_opt(char *arg)
{
  ft_putstr("nm_init_speedup_opt\n");
  printf("argtype: %s\n", arg);

  return (0);
}
int nm_init_scan_opt(char *arg)
{
  ft_putstr("nm_init_scan_opt\n");
  printf("argtype: %s\n", arg);

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
