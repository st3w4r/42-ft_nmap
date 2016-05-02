#include "ft_nmap.h"

void test_ip_v4()
{
	int i = 0;
	char *ip[] = { 
		// 4 section
		"",
		"0",
		"0.0",
		"0.0.0",
		"0.0.0.0",
		"0.0.0.0.0",
		// Split by dot
		"0,0,0,0",
		// Is number
		"a.b.c.d",
		"ab.bb.cb.db",
		"abc.abc.abc.abc",
		// Between 0 to 255
		"0.0.0.-1",
		"0.0.0.0",
		"1.0.0.0",
		"1.1.1.1",
		"256.1.1.1",
		"1.256.1.1",
		"1.1.256.1",
		"1.1.1.256",
		// Right
		"10.10.10.10",
		"10.10.10.123",
		"1.1.1.1",
		"0.0.0.0",
		"255.255.255.255",
		"255.255.255.256",
		"0.255.255.256",
		"10.10.10.124",
		"1.10.100.110",
		"100.100.100.10",
		"10.10.10.10",
		//Long
		"10.10.10.0010"
	};
	printf("Size: %lu\n", sizeof(ip) / sizeof(char *));
	while (i < sizeof(ip) / sizeof(char*))
	{
		printf("IP: %s - Valide: %d\n", ip[i], nm_check_ip_v4(ip[i]));
		i++;
	}
}

/* Ne pas oublier de remettre les Flags */
int               main(int argc, char **argv)
{

  (void)argc;
  // g_struct         = (t_struct *)malloc(sizeof(t_struct));
  g_struct.flags = 0x0;

  g_struct.ptr_init_fun[1] = nm_init_ports_opt;
  g_struct.ptr_init_fun[2] = nm_init_ip_opt;
  g_struct.ptr_init_fun[3] = nm_init_file_opt;
  g_struct.ptr_init_fun[4] = nm_init_speedup_opt;
  g_struct.ptr_init_fun[5] = nm_init_scan_opt;
  g_struct.ptr_init_fun[6] = nm_init_spoof_opt;
  g_struct.ptr_init_fun[7] = nm_init_ttl_opt;
  g_struct.ptr_init_fun[8] = nm_init_o_opt;
  g_struct.ptr_init_fun[9] = nm_init_s_opt;
  g_struct.ptr_init_fun[10] = nm_init_g_opt;

  // tabargs[0]    = "help";
  // tabargs[1]    = "ports";
  // tabargs[2]    = "ip";
  // tabargs[3]    = "file";
  // tabargs[4]    = "speedup";
  // tabargs[5]    = "scan";
  // tabargs[6]    = "spoof-mac";
  // tabargs[7]    = "ttl";
  // tabargs[8]    = "O";
  // tabargs[9]    = "S";
  // tabargs[10]   = "g";
//  nm_argv_parser(argv);

  test_ip_v4();
  nm_get_ip_file("ip_list");

  return (0);
}
