#include "cub3d.h"

void	parser(char *argv[])
{
	char		**elements;
	t_program	program;

	check_cub(argv[1]);
	elements = tokenize_input(argv[1]);
	validate_nr_of_identifiers(elements);
	validate_structure_paths(elements, &program);
	validate_rgb_input(elements, &program);
	validate_map(elements[SIZE], &program);
}
