#include "ft_nmap.h"

/* Ne pas oublier de remettre les Flags */
int               main(int argc, char **argv)
{

  (void)argc;
  g_struct         = (t_struct *)malloc(sizeof(t_struct));
  g_struct->flags = 0;

  parser(argv, &(g_struct->flags));

	printf("TYPE: %s\n", get_service_name(21, "tcp"));

  return (0);
}
