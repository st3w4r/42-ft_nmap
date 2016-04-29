#include "ft_nmap.h"

// ft_nmap [--help] [--ports [NOMBRE/PLAGE]] --ip ADRESSE IP [--speedup [NOMBRE]] [--scan [TYPE]]
// ou
// $> ft_nmap [--help] [--ports [NOMBRE/PLAGE]] --file FICHIER [--speedup [NOMBRE]] [--scan [TYPE]]

int       parser(char **argv, int *flags)
{
  int i;
  i       = 1;

  while (argv[i] != NULL)
  {
    if (check_args(argv[i], flags) != 0)
    {
      usage();
      return (-1);
    }
    i++;
  }
  return (0);
}


int      check_args(char *argv, int *flags)
{
  char *str;
  char **tabargs;
  int i;

  i       = 0;
  tabargs = get_tabargs();
  str     = strncmp(argv, "--", 2) == 0 ? argv + 2 : argv + 1;
  while (tabargs[i])
  {
    if (ft_strcmp(tabargs[i], str) == 0)
    {
      printf("tabargs: %d %s\n", i, str);
      *flags |= i;
    }
    i++;
  }
  free(tabargs);
  return (0);
}

char**               get_tabargs()
{
  char **tabargs;

  tabargs      = (char **)malloc(sizeof(12));
  tabargs[0]   = "help";
  tabargs[1]   = "ports";
  tabargs[2]   = "ip";
  tabargs[3]   = "file";
  tabargs[4]   = "speedup";
  tabargs[5]   = "scan";
  tabargs[6]   = "spoof-mac";
  tabargs[7]   = "ttl";
  tabargs[8]   = "O";
  tabargs[9]   = "S";
  tabargs[10]  = "g";
  tabargs[11]  = NULL;

  return tabargs;
}

void      usage()
{
  printf("Help Screen\n");
  printf("ft_nmap [OPTIONS]\n");
  printf("--help Print this help screen\n");
  printf("--ports ports to scan (eg: 1-10 or 1,2,3 or 1,5-15)\n");
  printf("--ip ip addresses to scan in dot format\n");
  printf("--file File name containing IP addresses to scan,\n");
  printf("--speedup [250 max] number of parallel threads to use\n");
  printf("--scan SYN/NULL/FIN/XMAS/ACK/UDP\n");
}
