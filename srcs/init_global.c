#include "ft_nmap.h"

// void printBits(unsigned int num)
// {
//    for(int bit=0;bit<(sizeof(unsigned int) * 8); bit++)
//    {
//       printf("%i ", num & 0x01);
//       num = num >> 1;
//    }
// 	 printf("\n");
// }

void nm_g_struct_init_fun(void)
{
  g_struct.ptr_init_fun[0] = nm_usage;
  g_struct.ptr_init_fun[1] = nm_init_ports_opt;
  g_struct.ptr_init_fun[2] = nm_init_ip_opt;
  g_struct.ptr_init_fun[3] = nm_init_file_opt;
  g_struct.ptr_init_fun[4] = nm_init_speedup_opt;
  g_struct.ptr_init_fun[5] = nm_init_scan_opt;
  g_struct.ptr_init_fun[6] = nm_init_spoof_opt;
  g_struct.ptr_init_fun[7] = nm_init_ttl_opt;
	g_struct.ptr_init_fun[8] = nm_init_pt_opt;
  g_struct.ptr_init_fun[9] = nm_init_o_opt;
  g_struct.ptr_init_fun[10] = nm_init_s_opt;
	g_struct.ptr_init_fun[11] = nm_init_g_opt;

}

void nm_g_struct_init()
{
  g_struct.flags = 0x0;
	g_struct.ttl = 60;
  g_struct.packet_time = 1000;
	g_struct.th_sniffer = NULL;
	g_struct.thread_free = 0;
  g_struct.types = 0x003F;
	g_struct.source_port = 4242;
	g_struct.store = (t_store*)malloc(sizeof(t_store));
	g_struct.store->next = NULL;
	// g_struct.rtt->start;
	// g_struct.rtt->end;
	nm_init_speedup_opt("1");
	nm_init_ports_opt("0-1024");
	nm_g_struct_init_fun();

}
