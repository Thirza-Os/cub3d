#include "../../include/cub_parser.h"
#include "cub_structs.h"

void printer(char **elements) {
	size_t index = 0;

	while (index < SIZE + 1)
	{
		printf("index: %zu, str: %s\n", index, elements[index]);
		index++;
	}
}

bool	parser(char *arg, t_program *program)
{
	char		**elements;

	if (check_cub(arg) != true)
		return false;
	elements = tokenize_input(arg);
	if (errno != 0)
	{
		printf("Free elements\n");
		return (false);
	}
	if (validate_nr_of_identifiers(elements) != true)
	{
		printf("Free elements\n");
		return (false);
	}
	if (validate_structure_paths(elements, program) != true)
	{
		printf("Free elements\n");
		return (false);
	}
	if (validate_rgb_input(elements, program) != true)
	{
		printf("Free elements\n");
		return (false);
	}
	printer(elements);
	if (validate_map(elements[SIZE], program) != true)
	{
		printf("Free elements\n");
		return (false);
	}
	return (true);
}
