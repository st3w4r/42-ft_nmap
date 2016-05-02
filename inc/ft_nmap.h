#ifndef NMAP_H
# define NMAP_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <pcap.h>

/*
typedef unsigned char	t_bool;
typedef unsigned int	t_uint;

# define TRUE 1
# define FALSE 0
*/
typedef struct	s_service
{
	char			*name;
	unsigned int	port;
	char			*protocol;
}				t_service;

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
  char *argtmp;
  int (*ptr_init_fun[11]) ();
}                t_struct;

t_struct g_struct;

/* Parser.c */
int       nm_cmp_args(char *argv, char **tabargs);
int       nm_check_args(char *str, char **tabargs);
int       nm_argv_parser(char **argv);
char**    nm_get_args();
void      nm_usage();

int nm_init_ports_opt();
int nm_init_ip_opt();
int nm_init_file_opt();
int nm_init_speedup_opt();
int nm_init_scan_opt();
int nm_init_spoof_opt();
int nm_init_ttl_opt();
int nm_init_o_opt();
int nm_init_s_opt();
int nm_init_g_opt();

/**
 ** Name: services.c
 ** Desc: Detect the service
 */
char	*nm_get_service_name(int port, char *protocol);

/**
 ** Name: helper.c
 ** Desc: Helper function
 */
t_bool	nm_check_ip_v4(char *ip);

#endif
