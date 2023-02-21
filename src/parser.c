#include "cub3d.h"

void	parser(int argc, char *argv[])
{
	char	**elements;

	check_cub(argv[1]);
	parse_input(tokenize_input(argv[1]));
}
