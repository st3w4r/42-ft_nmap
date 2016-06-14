#include "ft_nmap.h"

int             nm_argv_parser(char **argv, int argc)
{
  char **tabargs;
  int i;
  int opt;
  int argtype;
  int check_ip = 0;
  argtype       = -1;
  opt           = 0;
  i             = 1;
  tabargs       = nm_get_args();

  while (i < argc)
  {
    if (ft_strcmp("--ip", argv[i]) == 0)
      check_ip = 1;
    if (ft_strcmp("--file", argv[i]) == 0)
      check_ip = 1;
    i++;
  }
  if (check_ip == 0)
  {
    nm_usage();
    exit(0);
  }

  i = 1;
  while (i < argc)
  {
    argtype = nm_arg_type(argv[i]);
    if ((opt = nm_cmp_args(argv[i], tabargs)) > -1)
    {
      if (nm_init_fun(argv[i + 1], opt, argtype, tabargs) == -1)
			{
				nm_arg_error(argv[i + 1]);
				return (-1);
			}
    }
    else
      return (nm_arg_error(argv[i]));
    i += argtype;
  }
  ft_arrfree(&tabargs);
  return (0);
}

/* nm_arg_type
** return the type of argument - = 1, -- = 2
*/
int             nm_arg_type(char *arg)
{
  if (strncmp(arg, "--", 2) == 0)
    return (2);
  else if (strncmp(arg, "-", 1) == 0)
    return (1);
  else
    return (0);
}

int           nm_init_fun(char *arg, int opt, int argtype, char **tabargs)
{
  g_struct.flags |= 1 << opt;
	if (!arg)
	{
		nm_arg_error(arg);
		exit(0);
	}
  if (argtype == 2)
  {
    if (arg && nm_arg_type(arg) != 0)
    {
      printf("Error: %s missing argument\n", tabargs[opt]);
      return (-1);
    }
    return (g_struct.ptr_init_fun[opt](arg));
  }
  else
    return (g_struct.ptr_init_fun[opt](NULL));
}

int             nm_arg_error(char *arg)
{
  printf("nmap: illegal option: %s\n", arg);
  nm_usage();
	exit(0);
  return (-1);
}
/* nm_cmp_args
** Retourne l'index de la fonction a initialiser
** Si non -1 en cas d'erreur (mauvaise arguments dans la ligne de commande)
*/

int             nm_cmp_args(char *arg, char **tabargs)
{
  int i;

  i = 0;
  while (tabargs[i])
  {
    if (ft_strcmp(tabargs[i], arg) == 0)
      return (i);
    i++;
  }
  return (-1);
}

char**          nm_get_args()
{
  char **tabargs;

  tabargs       = (char **)malloc(sizeof(char *) * 13);
  tabargs[0]    = ft_strdup("--help");
  tabargs[1]    = ft_strdup("--ports");
  tabargs[2]    = ft_strdup("--ip");
  tabargs[3]    = ft_strdup("--file");
  tabargs[4]    = ft_strdup("--speedup");
  tabargs[5]    = ft_strdup("--scan");
  tabargs[6]    = ft_strdup("--spoof-mac");
  tabargs[7]    = ft_strdup("--ttl");
	tabargs[8]		= ft_strdup("--pt");
  tabargs[9]    = ft_strdup("-O");
  tabargs[10]		= ft_strdup("-S");
	tabargs[11]   = ft_strdup("--g");
  tabargs[12]   = NULL;

  return (tabargs);
}

int            nm_usage()
{
  printf("\nft_nmap [OPTIONS]\n");
  printf("--help Print this help screen\n");
  printf("--ports ports to scan (eg: (start) 1-10 (end) or 1,2,3 or 1,5-15)\n");
  printf("--ip ip addresses to scan in dot format\n");
  printf("--file File name containing IP addresses to scan,\n");
	printf("--speedup [250 max] number of parallel threads to use\n");
	printf("--ttl (time to live) 1-255\n");
	printf("--pt (packet time) 1-10 sec\n");
  printf("--g (source port) 1-65536 \n");
  printf("--scan SYN/NULL/FIN/XMAS/ACK/UDP\n");
  return (-1);
}
