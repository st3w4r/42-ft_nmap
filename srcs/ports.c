#include "ft_nmap.h"

int nm_ports_opt_get_range(char *ports)
{
  int start;
  int end;
  char **arrRange;

  arrRange = NULL;
  arrRange = ft_strsplit(ports, '-');
  if (!ft_is_number(arrRange[0]) || !ft_is_number(arrRange[1]))
    return (-1);
  start = ft_atoi(arrRange[0]);
  end = ft_atoi(arrRange[1]);
  if ((start <= 0 || start > 1024) || (end <= 0 || end > 1024))
    return (-1);
  while(start <= end)
  {
    g_struct.ports[start] = 1;
    start++;
  }
  ft_arrfree(&arrRange);
  return (0);
}

int nm_init_ports_opt(char *arg)
{
  char **arrOne;
  int i = 0;

  g_struct.ports = (int *)malloc(sizeof(int) * 1024);
  arrOne= NULL;
  arrOne = ft_strsplit(arg, ',');
  while (arrOne[i])
  {
    if (ft_strchr(arrOne[i], '-'))
    {
      if (nm_ports_opt_get_range(arrOne[i]) == -1)
        return (-1);
    }
    else if (ft_is_number(arrOne[i]))
      g_struct.ports[ft_atoi(arrOne[i])] = 1;
    else
      return (-1);
    i++;
  }
  ft_arrfree(&arrOne);
  return (0);
}
