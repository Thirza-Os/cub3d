/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:37 by tosinga       #+#    #+#                 */
/*   Updated: 2024/09/11 01:56:18 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	parser(char *arg, t_program *program)
{
	char		**elements;

	if (check_cub(arg) != true)
		return (free_parser(NULL, false));
	elements = tokenize_input(arg);
	if (errno != 0 || elements == NULL)
		return (free_parser(elements, false));
	if (validate_nr_of_identifiers(elements) != true)
		return (free_parser(elements, false));
	if (validate_structure_paths(elements, program) != true)
		return (free_parser(elements, false));
	if (validate_rgb_input(elements, program) != true)
		return (free_parser(elements, false));
	if (validate_map(elements[SIZE], program) != true)
		return (free_parser(elements, false));
	return (free_parser(elements, true));
}
