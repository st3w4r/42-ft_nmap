#include "ft_nmap.h"

/* Ne pas oublier de remettre les Flags */
int               main(int argc, char **argv)
{

  (void)argc;
  // g_struct         = (t_struct *)malloc(sizeof(t_struct));
  g_struct.flags = 0x0;

  nm_argv_parser(argv, &g_struct.flags);

  return (0);
}
