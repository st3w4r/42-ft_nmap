#include "ft_nmap.h"

/* Ne pas oublier de remettre les Flags */
int               main(int argc, char **argv)
{
	if (getuid() != 0)
		ft_error_str_exit("ft_nmap: Operation not permitted\n");
  (void)argc;
  nm_g_struct_init();
  nm_argv_parser(argv, argc);
	nm_loop();
  return (0);
}
