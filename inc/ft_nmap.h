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

typedef struct   s_arg_value
{
  char *arg;
  int value;
  struct s_arg_value *next;
}               t_arg_value;
// struct s_arg_value *head;

typedef struct   s_struct
{
  int flags;
}                t_struct;

t_struct *g_struct;

/* Parser.c */
int       parser(char **argv, int *flags);
void      usage();
char**    get_tabargs();
int       check_args(char *argv, int *flags);




#endif
