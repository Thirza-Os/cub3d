/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:11:02 by rbrune        #+#    #+#                 */
/*   Updated: 2023/07/06 14:18:38 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_program	parser(char *argv[])
{
	char		**elements;
	t_program	program;

	check_cub(argv[1]);
	elements = tokenize_input(argv[1]);
	validate_nr_of_identifiers(elements);
	validate_structure_paths(elements, &program);
	validate_rgb_input(elements, &program);
	validate_map(elements[SIZE], &program);
	free (elements);
	return (program);
}
