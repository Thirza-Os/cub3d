/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:37 by tosinga       #+#    #+#                 */
/*   Updated: 2024/09/11 03:18:07 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static	bool	_free_parser(char **elements, bool state)
{
	size_t	row;

	if (elements == NULL)
		return (state);
	row = 0;
	while (row <= SIZE)
	{
		if (elements[row] != NULL)
			free(elements[row]);
		row++;
	}
	free(elements);
	return (state);
}

bool	parser(char *arg, t_program *program)
{
	char		**elements;

	if (check_cub(arg) != true)
		return (_free_parser(NULL, false));
	elements = tokenize_input(arg);
	if (errno != 0 || elements == NULL)
		return (_free_parser(elements, false));
	if (validate_nr_of_identifiers(elements) != true)
		return (_free_parser(elements, false));
	if (validate_paths(elements, program) != true)
		return (_free_parser(elements, false));
	if (validate_rgb_input(elements, program) != true)
		return (_free_parser(elements, false));
	if (validate_map(elements[SIZE], program) != true)
		return (_free_parser(elements, false));
	return (_free_parser(elements, true));
}
