#include "ft_nmap.h"

/* Ne pas oublier de remettre les Flags */
int               main(int argc, char **argv)
{

  (void)argc;
  nm_g_struct_init();
  nm_argv_parser(argv, argc);
	nm_loop();
  return (0);
}
