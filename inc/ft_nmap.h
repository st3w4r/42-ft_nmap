#ifndef NMAP_H
# define NMAP_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <pcap.h>

enum    e_flags
{
  HELP_F = 1 << 0,
  PORTS_F = 1 << 1,
  IP_F = 1 << 2,
  FILE_F = 1 << 3,
  SPEEDUP_F = 1 << 4,
  SCAN_F = 1 << 5,
  SPOOFMAC_F = 1 << 6,
  TTL_F = 1 << 7,
  O_F = 1 << 8,
  S_F = 1 << 9,
  G_F = 1 << 10
};

typedef struct   s_struct
{
  int flags;
}                t_struct;

t_struct g_struct;

/* Parser.c */
int       nm_argv_parser(char **argv, int *flags);
void      nm_usage();
char**    nm_get_args();
int       nm_cmp_args(char *argv, char **tabargs, int *flags);
void      nm_check_args(int *flags);




#endif
