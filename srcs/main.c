#include "ft_nmap.h"

t_struct *g_struct;
/* Ne pas oublier de remettre les Flags */
int   main(int argc, char **argv)
{
  g_struct = (t_struct *)malloc(sizeof(t_struct));
  g_struct->g_arg = (t_arg *)malloc(sizeof(t_arg));

  parser(argv, g_struct->g_arg);

  return (0);
}
