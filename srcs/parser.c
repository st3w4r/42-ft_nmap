#include "ft_nmap.h"

// ft_nmap [--help] [--ports [NOMBRE/PLAGE]] --ip ADRESSE IP [--speedup [NOMBRE]] [--scan [TYPE]]
// ou
// $> ft_nmap [--help] [--ports [NOMBRE/PLAGE]] --file FICHIER [--speedup [NOMBRE]] [--scan [TYPE]]



int       parser(char **argv, t_arg *g_arg)
{
  int i;

  i       = 1;
  while (argv[i] != NULL)
  {
    if (ft_strncmp(argv[i], "--", 2) == 0)
      printf("argv %d %s\n", i, argv[i]);
    else
    {
      usage();
      return (-1);
    }
    i++;
  }
  return (0);
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
