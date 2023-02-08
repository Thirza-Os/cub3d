#include "cub3d.h"

void	print_error(char *message)
{
	printf("Error\n");
	printf("%s\n", message);
	exit (1);
}

void	*ft_malloc_check(void *s)
{
	if (s == 0)
	{
		printf("Error\n", 1);
		exit(1);
	}
	return (s);
}
