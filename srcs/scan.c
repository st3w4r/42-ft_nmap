#include "ft_nmap.h"

void printBits(unsigned int num)
{
   for(int bit=0;bit<((int)sizeof(unsigned int) * 8); bit++)
   {
      printf("%i", num & 0x01);
      if (bit > 0)
        bit % (bit * 3) != 0 ? printf(" ") : 0;
      num = num >> 1;
   }
}

char **nm_init_scan_get_types()
{
  char **arrtypes;

  arrtypes       = (char **)malloc(sizeof(char *) * 6);
  arrtypes[0]    = ft_strdup("SYN");
  arrtypes[1]    = ft_strdup("NULL");
  arrtypes[2]    = ft_strdup("FIN");
  arrtypes[3]    = ft_strdup("XMAS");
  arrtypes[4]    = ft_strdup("ACK");
  arrtypes[5]    = ft_strdup("UDP");
  arrtypes[6]   = NULL;

  return (arrtypes);
}

int nm_cmp_types(char *type, char **arrtypes)
{
  int i;

  i = 0;
  while (arrtypes[i])
  {
    if (ft_strcmp(arrtypes[i], type) == 0)
    {
      g_struct.types |= 1 << i;
      return (i);
    }
    i++;
  }
  return (-1);
}

int nm_init_scan_opt(char *arg)
{
  char **types;
  char **arrtypes;
  int i;

  i = 0;
  types = NULL;
  arrtypes = nm_init_scan_get_types();
  types = ft_strsplit(arg, '/');
  while (types[i])
  {
    if (nm_cmp_types(types[i], arrtypes) == -1)
      return (-1);
    i++;
  }
  // printBits(g_struct.types);
  return (0);
}
