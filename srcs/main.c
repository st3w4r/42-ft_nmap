#include "ft_nmap.h"

/* Ne pas oublier de remettre les Flags */


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
	return("unreachable");
}


void nm_display_scan_type(int type, int result)
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
	int check_v = 0;
	int open = 0;

	printf("%-15s %-20s %-10s %-55s %-10s\n","Ip", "Service Name", "Port", "Results", "Conclusion");
	printf("--------------------------------------------------------------------------------------------------------------------\n");
	while (port < 1025)
	{
		ptr = g_struct.store;
		while (ptr->next != NULL)
		{
			if (port == ptr->ports_results->port)
			{
				if (check_p == 0)
					printf("%-15s %-20s %-10d ", ptr->ip, ptr->ports_results->service_name, ptr->ports_results->port);
				nm_display_scan_type(ptr->ports_results->type, ptr->ports_results->results);
				if (ptr->ports_results->results & F_RESULT_OPEN)
					open = 1;
				if (check_v == 2)
					printf("\n%-48s", "");
				check_v++;
				check_p = 1;
			}
			ptr = ptr->next;
		}
		if (check_p == 1)
				printf("\n");
		if (open == 1 && check_p == 1)
			printf("%*s\n",110, "Open");
		else if (open == 0 && check_p == 1)
			printf("%*s\n",110, "Close");
		open = 0;
		check_v = 0;
		check_p = 0;
		port++;
	}
}

void nm_display_header()
{
	int i;

	i = 0;
	while (g_struct.ip_store[i].content)
		i++;

	printf("Scan Configurations\n");
	if (i == 1)
		printf("Target Ip-Address : %s\n", g_struct.ip_store[0].content);
	else
		printf("Target Ip-Address : multiple\n");
	i = 0;
	int j = 0;
	while (i < 1025)
	{
		if (g_struct.ports[i] == 1)
			j++;
		i++;
	}
	printf("No of Ports to scan : %d\n", j);
	printf("Scans to be performed : ");
	if (g_struct.types & SYN_F)
		printf("SYN ");
	if (g_struct.types & ACK_F)
		printf("ACK ");
	if (g_struct.types & FIN_F)
		printf("FIN ");
	if (g_struct.types & XMAS_F)
		printf("XMAS ");
	if (g_struct.types & UDP_F)
		printf("UDP ");
	if (g_struct.types & NULL_F)
		printf("NULL ");
	printf("\n");
	printf("No of threads : %d\n", g_struct.speedup);
}

int               main(int argc, char **argv)
{
	if (getuid() != 0)
		ft_error_str_exit("ft_nmap: Operation not permitted\n");
	(void)argc;

	pthread_mutex_init(&g_struct.pcap_init_mutex, NULL);
	pthread_mutex_init(&g_struct.store_mutex, NULL);
	nm_g_struct_init();
	nm_argv_parser(argv, argc);
	nm_display_header();

	nm_loop();
	nm_display();

	pthread_exit(NULL);
	pthread_mutex_destroy(&g_struct.pcap_init_mutex);
	pthread_mutex_destroy(&g_struct.store_mutex);
	return (0);
}
