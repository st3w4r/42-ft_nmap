#ifndef NMAP_H
# define NMAP_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <pcap.h>

/*
typedef unsigned char	t_bool;
typedef unsigned int	t_uint;

# define TRUE 1
# define FALSE 0
*/
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

typedef struct	s_service
{
  char			*name;
  unsigned int	port;
  char			*protocol;
}				t_service;

typedef struct   s_struct
{
  int flags;
  int *ports;
  int speedup;
  int (*ptr_init_fun[11]) ();
  t_list	*ip_store;
}                t_struct;

t_struct g_struct;

/* Parser.c */
int       nm_cmp_args(char *arg, char **tabargs);
int       nm_arg_error(char *arg);
int       nm_argv_parser(char **argv, int argc);
char**    nm_get_args();
int       nm_arg_type(char *arg);
int       nm_init_fun(char *arg, int opt, int argtype, char **tabargs);
int       nm_usage();

int nm_init_ports_opt(char *arg);
int nm_init_ip_opt(char *arg);
int nm_init_file_opt(char *arg);
int nm_init_speedup_opt(char *arg);
int nm_init_scan_opt(char *arg);
int nm_init_spoof_opt(char *arg);
int nm_init_ttl_opt(char *arg);
int nm_init_o_opt(char *arg);
int nm_init_s_opt(char *arg);
int nm_init_g_opt(char *arg);

/**
 ** Name: services.c
 ** Desc: Detect the service
 */
char	*nm_get_service_name(int port, char *protocol);

/**
 ** Name: helper.c
 ** Desc: Helper function
 */
void	nm_get_ip_file(char *file);
t_bool	nm_check_ip_v4(char *ip);

#endif
