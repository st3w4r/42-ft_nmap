#include "ft_nmap.h"

/* Ne pas oublier de remettre les Flags */

void nm_header_informations()
{
	// Ici mettre les information avant le scan des ports
}

char *nm_display_scan_result(int result)
{
	if (result & F_RESULT_OPEN)
		return("open");
	else if (result & F_RESULT_CLOSE)
		return("close");
	else if (result & F_RESULT_FILTERED)
		return("filtered");
	else if (result & F_RESULT_UNFILTERED)
		return("unfiltered");
	else if (result & F_RESULT_OPEN_FILTERED)
		return("open|filtered");
}

char *nm_display_scan_type(int type, int result)
{
// printf("%-20s", "initialization...");
	if (type & SYN_F)
		printf("SYN(%s) ", nm_display_scan_result(result));
	if (type & ACK_F)
		printf("ACK(%s) ", nm_display_scan_result(result));
	if (type & FIN_F)
		printf("FIN(%s) ", nm_display_scan_result(result));
	if (type & XMAS_F)
		printf("XMAS(%s) ", nm_display_scan_result(result));
	if (type & UDP_F)
		printf("UDP(%s) ", nm_display_scan_result(result));
	if (type & NULL_F)
		printf("NULL(%s) ", nm_display_scan_result(result));
}

void 							nm_display()
{
	t_store *ptr = NULL;
	int port = 0;
	int check_p = 0;

	while (port < 1025)
	{
		ptr = g_struct.store;
		while (ptr->next != NULL)
		{
			if (port == ptr->ports_results->port)
			{
				if (check_p == 0)
					printf("ip: %s, port: %d, type: ", ptr->ip, ptr->ports_results->port);
				nm_display_scan_type(ptr->ports_results->type, ptr->ports_results->results);
				check_p = 1;
			}
			ptr = ptr->next;
		}
		if (check_p == 1)
			printf("\n");
		check_p = 0;
		port++;
	}


}
int               main(int argc, char **argv)
{
	if (getuid() != 0)
		ft_error_str_exit("ft_nmap: Operation not permitted\n");
	(void)argc;

	nm_g_struct_init();
	nm_argv_parser(argv, argc);

	pthread_mutex_init(&g_struct.pcap_init_mutex, NULL);
	pthread_mutex_init(&g_struct.store_mutex, NULL);

	nm_loop();
	nm_display();

	pthread_exit(NULL);
	pthread_mutex_destroy(&g_struct.pcap_init_mutex);
	pthread_mutex_destroy(&g_struct.store_mutex);
	return (0);
}
