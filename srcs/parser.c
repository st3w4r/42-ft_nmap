#include "ft_nmap.h"

// ft_nmap [--help] [--ports [NOMBRE/PLAGE]] --ip ADRESSE IP [--speedup [NOMBRE]] [--scan [TYPE]]
// ou
// $> ft_nmap [--help] [--ports [NOMBRE/PLAGE]] --file FICHIER [--speedup [NOMBRE]] [--scan [TYPE]]
void printBits(int num)
{
  for(int bit = 0; bit < ((int)sizeof(int) * 8); bit++)
  {
    printf("%i ", num & 0x01);
    num = num >> 1;
  }
}

int             nm_argv_parser(char **argv, int argc)
{
  char **tabargs;
  int i;
  int opt;
  int argtype;

  argtype       = -1;
  opt           = 0;
  i             = 1;
  tabargs       = nm_get_args();
  while (i < argc)
  {
    argtype = nm_arg_type(argv[i]);
    if ((opt = nm_cmp_args(argv[i], tabargs, argtype)) > -1)
      nm_init_fun(argv[i + 1], opt, argtype);
    else
      return (nm_arg_error(argv[i]));
    i += argtype;
  }
  free(tabargs);
  return (0);
}

int             nm_arg_type(char *arg)
{
  if (strncmp(arg, "--", 2) == 0)
    return (2);
  else if (strncmp(arg, "-", 1) == 0)
    return (1);
  else
    return (0);
}

int           nm_init_fun(char *arg, int opt, int argtype)
{
  g_struct.flags |= 1 << opt;
  if (argtype == 2)
    return (g_struct.ptr_init_fun[opt](arg));
  else
    return (g_struct.ptr_init_fun[opt](NULL));
}

int             nm_arg_error(char *arg)
{
  printf("nmap: illegal option: %s\n", arg);
  nm_usage();
  return (-1);
}

int             nm_cmp_args(char *arg, char **tabargs, int argtype)
{
  // char *str;
  int i;

  (void)argtype;
  i             = 0;
  // str           = arg + argtype;
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

  tabargs       = (char **)malloc(sizeof(12));
  tabargs[0]    = "--help";
  tabargs[1]    = "--ports";
  tabargs[2]    = "--ip";
  tabargs[3]    = "--file";
  tabargs[4]    = "--speedup";
  tabargs[5]    = "--scan";
  tabargs[6]    = "--spoof-mac";
  tabargs[7]    = "--ttl";
  tabargs[8]    = "-O";
  tabargs[9]    = "-S";
  tabargs[10]   = "-g";
  tabargs[11]   = NULL;

  return tabargs;
}

int            nm_usage()
{
  printf("\nft_nmap [OPTIONS]\n");
  printf("--help Print this help screen\n");
  printf("--ports ports to scan (eg: 1-10 or 1,2,3 or 1,5-15)\n");
  printf("--ip ip addresses to scan in dot format\n");
  printf("--file File name containing IP addresses to scan,\n");
  printf("--speedup [250 max] number of parallel threads to use\n");
  printf("--scan SYN/NULL/FIN/XMAS/ACK/UDP\n");
  return (-1);
}
