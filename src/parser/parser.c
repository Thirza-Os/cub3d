#include "../../include/cub_parser.h"
#include "../../include/cub3D.h"

bool	parser(char *arg, t_program *program)
{
	char		**elements;

	if (check_cub(arg) != true)
		return (clean_parser(NULL));
	elements = tokenize_input(arg);
	if (errno != 0)
		return (clean_parser(elements));
	(void)program;
	// if (validate_nr_of_identifiers(elements) != true)
	// 	return (clean_parser(elements));
	// if (validate_structure_paths(elements, program) != true)
	// 	return (clean_parser(elements));
	// if (validate_rgb_input(elements, program) != true)
	// 	return (clean_parser(elements));
	// if (validate_map(elements[SIZE], program) != true)
	// 	return (clean_parser(elements));
	return (true);
}
