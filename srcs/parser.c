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

int             nm_argv_parser(char **argv)
{
  char **tabargs;
  int i;
  int argtype;

  argtype       = 0;
  i             = 1;
  tabargs       = nm_get_args();
  while (argv[i])
  {
    argtype = strncmp(argv[i], "--", 2) == 0 ? 1 : 0;
    g_struct.argtmp = argtype == 1 ? argv[i + 1] : NULL;
    if (nm_check_args(argv[i], tabargs) == 0)
    {
      argtype == 1 ? i++ : 0;
      printf("argv[%d] %s\n", i, argv[i]);
    }
    i++;
  }
  printBits(g_struct.flags);
  return (0);
}


int             nm_check_args(char *src, char **tabargs)
{
  if (nm_cmp_args(src, tabargs) == -1)
  {
    printf("nmap: illegal option: %s\n", src);
    nm_usage();
    return (-1);
  }
  return (0);
}

int             nm_cmp_args(char *argv, char **tabargs)
{
  char *str;
  int i;

  i             = 0;
  str           = strncmp(argv, "--", 2) == 0 ? argv + 2 : argv + 1;
  while (tabargs[i])
  {
    if (ft_strcmp(tabargs[i], str) == 0)
    {
      g_struct.flags |= 1 << i;
      g_struct.ptr_init_fun[i]();
      return (0);
    }
    i++;
  }
  return (-1);
}

char**          nm_get_args()
{
  char **tabargs;

  tabargs       = (char **)malloc(sizeof(12));
  tabargs[0]    = "help";
  tabargs[1]    = "ports";
  tabargs[2]    = "ip";
  tabargs[3]    = "file";
  tabargs[4]    = "speedup";
  tabargs[5]    = "scan";
  tabargs[6]    = "spoof-mac";
  tabargs[7]    = "ttl";
  tabargs[8]    = "O";
  tabargs[9]    = "S";
  tabargs[10]   = "g";
  tabargs[11]   = NULL;

  return tabargs;
}

void            nm_usage()
{
  printf("\nft_nmap [OPTIONS]\n");
  printf("--help Print this help screen\n");
  printf("--ports ports to scan (eg: 1-10 or 1,2,3 or 1,5-15)\n");
  printf("--ip ip addresses to scan in dot format\n");
  printf("--file File name containing IP addresses to scan,\n");
  printf("--speedup [250 max] number of parallel threads to use\n");
  printf("--scan SYN/NULL/FIN/XMAS/ACK/UDP\n");
}
