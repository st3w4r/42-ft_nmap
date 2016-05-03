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
  nm_g_struct_init();
  nm_argv_parser(argv, argc);

  return (0);
}
