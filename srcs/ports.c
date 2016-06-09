#include "ft_nmap.h"

int nm_ports_opt_get_range(char *ports)
{
  int start;
  int end;
  char **arr_range;

  arr_range = NULL;
  arr_range = ft_strsplit(ports, '-');
  if (!ft_is_number(arr_range[0]) || !ft_is_number(arr_range[1]))
    return (-1);
  start = ft_atoi(arr_range[0]);
  end = ft_atoi(arr_range[1]);
  if ((start < 0 || start > 1024) || (end < 0 || end > 1024))
    return (-1);
  while(start <= end)
  {
    g_struct.ports[start] = 1;
    start++;
  }
  ft_arrfree(&arr_range);
  return (0);
}

int nm_init_ports_opt(char *arg)
{
  char **arr_one;
  int i = 0;

  g_struct.ports = (int *)malloc(sizeof(int) * 1024);
  arr_one= NULL;
  arr_one = ft_strsplit(arg, ',');
  while (arr_one[i])
  {
    if (ft_strchr(arr_one[i], '-'))
    {
      if (nm_ports_opt_get_range(arr_one[i]) == -1)
        return (-1);
    }
    else if (ft_is_number(arr_one[i]))
      g_struct.ports[ft_atoi(arr_one[i])] = 1;
    else
      return (-1);
    i++;
  }
  ft_arrfree(&arr_one);
  return (0);
}
