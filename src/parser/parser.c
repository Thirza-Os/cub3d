#include "../../include/cub_parser.h"

bool	parser(char *arg)
{
	char		**elements;

	if (check_cub(arg) != true)
		return false;
	printf("parser\n");
	elements = tokenize_input(arg);
	if (errno != 0)
	{
		printf("Free elements\n");
		return (false);
	}
	printf("%s\n", elements[0]);
	// validate_nr_of_identifiers(elements);
	// validate_structure_paths(elements, &program);
	// validate_rgb_input(elements, &program);
	// validate_map(elements[SIZE], &program);

	return (true);
}
