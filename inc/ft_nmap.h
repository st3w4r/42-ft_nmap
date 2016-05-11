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
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/tcp.h>
# include <netinet/if_ether.h>

# define PACKET_BUF_SIZE 40

enum		e_flags_tcp
{
	F_TCP_URG = 1 << 0,
	F_TCP_ACK = 1 << 1,
	F_TCP_PSH = 1 << 2,
	F_TCP_RST = 1 << 3,
	F_TCP_SYN = 1 << 4,
	F_TCP_FIN = 1 << 5
};

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

enum    e_scan_types
{
	SYN_F = 1 << 0,
	NULL_F = 1 << 1,
	FUN_F = 1 << 2,
	XMAS_F = 1 << 3,
	ACK_F = 1 << 4,
	UDP_F = 1 << 5,
};

typedef struct	s_port_result
{
	int		port;
	int		flags; // e_scan_types
}				t_port_result;

typedef struct	s_store
{
	char			*ip;
	t_port_result	*ports_results;
}				t_store;

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
  int types;
  int ttl;
  int (*ptr_init_fun[11]) ();
  t_list	*ip_store; // Linked list of string ip
  t_store	*sotre; // Array of struct s_store
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

int       nm_init_ports_opt(char *arg);
int       nm_init_ip_opt(char *arg);
int       nm_init_file_opt(char *arg);
int       nm_init_speedup_opt(char *arg);
int       nm_init_scan_opt(char *arg);
int       nm_init_spoof_opt(char *arg);
int       nm_init_ttl_opt(char *arg);
int       nm_init_o_opt(char *arg);
int       nm_init_s_opt(char *arg);
int       nm_init_g_opt(char *arg);

void      nm_g_struct_init_fun(void);
void      nm_g_struct_init();

/**
 ** Name: services.c
 ** Desc: Detect the service
 */
char	*nm_get_service_name(int port, char *protocol);

/**
 ** Name: helper.c
 ** Desc: Helper function
 */
void	nm_add_ip_to_ip_store(char *ip);
void	nm_get_ip_file(char *file);
t_bool	nm_check_ip_v4(char *ip);

/**
 ** Name: connect.c
 ** Desc: Open socket and configure packet ip and tcp
 */
int				nm_open_socket();
struct ip	*nm_configure_packet_ip(char *buf, char *ip_dst);
struct tcphdr		*nm_configure_packet_tcp(char *buf, u_int size_ip,
								unsigned short port_src, unsigned short port_dst,
								u_int seq,
								u_int ack_seq,
								u_int flags,
								unsigned short window);

/**
 ** Name: loop.c
 ** Desc: Loop on send and recevive request
 */
void nm_loop();

#endif
