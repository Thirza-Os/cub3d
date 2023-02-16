#include "cub3d.h"

void	parser(int argc, char *argv[])
{
	// t_program	program;

	check_cub(argv[1]);
	parse_input(tokenize_input(argv[1]));

	// tokenize: raw
	// parse_file(argv[1]);
	// validate: check valid input && return struct

}
