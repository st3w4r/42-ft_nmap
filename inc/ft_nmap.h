#ifndef NMAP_H
# define NMAP_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>


typedef struct   s_arg
{
  char           *port;
  char           *ip;
  int            file;
  int            speedup;
  int            type;
}                t_arg;

typedef struct   s_struct
{
  t_arg         *g_arg;
}                t_struct;

int       parser(char **argv, t_arg *g_arg);
void      usage();


#endif
