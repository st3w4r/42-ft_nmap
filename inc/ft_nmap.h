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
# include <netinet/udp.h>
# include <netinet/if_ether.h>
# include <ifaddrs.h>
# include <pthread.h>

# define PACKET_BUF_SIZE 40

enum		e_scan_result
{
	F_RESULT_OPEN = 1 << 0,
	F_RESULT_CLOSE = 1 << 1,
	F_RESULT_FILTERED = 1 << 2,
	F_RESULT_UNFILTERED = 1 << 3,
	F_RESULT_OPEN_FILTERED = 1 << 4
};

enum		e_flags_tcp
{
	F_TCP_URG = 1 << 0,
	F_TCP_ACK = 1 << 1,
	F_TCP_PSH = 1 << 2,
	F_TCP_RST = 1 << 3,
	F_TCP_SYN = 1 << 4,
	F_TCP_FIN = 1 << 5,
	F_TCP_NULL = 0
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
	FIN_F = 1 << 2,
	XMAS_F = 1 << 3,
	ACK_F = 1 << 4,
	UDP_F = 1 << 5,
};

typedef struct	s_pseudo_header
{
	u_int32_t	saddr;
	u_int32_t	daddr;
	u_int8_t	reserved;
	u_int8_t	protocol;
	u_int16_t	len;
}				t_pseudo_header;

typedef struct	s_scan_result
{
	enum e_scan_types		type;
	enum e_scan_result	result;
}								t_scan_result;

typedef struct	s_port_result
{
	int						port;
	t_scan_result	*t_scan_result; // Array of t_scan_result
	t_bool				conclusion;
	char					*service_name;
}				t_port_result;

typedef struct	s_store
{
	char					*ip;
	t_port_result	*ports_results; // Array of t_port_result
}								t_store;

typedef struct	s_service
{
  char					*name;
  u_int					port;
  char					*protocol;
}								t_service;

typedef struct   s_struct
{
  int flags;
  int speedup;
  int types;
  int ttl;
	int *ports;
	int thread_free;
  t_list *ip_store; // Linked list of string ip
  t_store	*sotre; // Array of struct s_store
	pthread_t *th_sniffer; //Array of thread
	int *thread_occupied;
	pthread_mutex_t pcap_init_mutex;
	int (*ptr_init_fun[11]) ();
}                t_struct;

typedef struct		s_th_sniffer
{
	char *filter_exp;
	unsigned short port_dst;
	unsigned short port_src;
	u_int seq;
	u_int ack_seq;
	u_int flags;
	struct sockaddr_in sin;
	int socket;
	char *ip_str;
	char *buf;
	enum e_scan_types scan_type;
	enum e_scan_result scan_result;
}					t_th_sniffer;


t_struct g_struct;

/* Parser.c */
void printBits(unsigned int num);

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
char	*nm_get_ip_interface();
void	nm_add_ip_to_ip_store(char *ip);
void	nm_get_ip_file(char *file);
t_bool	nm_check_ip_v4(char *ip);
unsigned short	nm_pseudo_header_checksum(char *buf, u_int size_ip);
unsigned short	nm_checksum(unsigned short *data, int len);

/**
 ** Name: connect.c
 ** Desc: Open socket and configure packet ip and tcp
 */
int				nm_open_socket();
struct ip		*nm_configure_packet_ip(char *buf, char *ip_dst, enum e_scan_types type);
struct tcphdr	*nm_configure_packet_tcp(char *buf,
					unsigned short port_src, unsigned short port_dst,
					u_int seq,
					u_int ack_seq,
					u_int flags);
struct udphdr	*nm_configure_packet_udp(char *buf,
					unsigned short port_src, unsigned short port_dst);
/**
 ** Name: loop.c
 ** Desc: Loop on send and recevive request
 */
void nm_loop();
int nm_build_flag(enum e_scan_types type);

/**
 ** Name: sniffer.c
 ** Desc: Sniff the network and capture packets
 */
void	 *nm_th_sniffer(void * data);
void nm_sniffer(char *filter_exp, char *buf, struct ip *ip, t_th_sniffer data_sniffer);

#endif
