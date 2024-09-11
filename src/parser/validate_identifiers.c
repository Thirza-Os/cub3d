/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_identifiers.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:37 by tosinga       #+#    #+#                 */
/*   Updated: 2024/09/11 02:49:27 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	validate_structure_paths(char **elements, t_program *program)
{
	int	index;

	index = 0;
	while (index < MAX_IMGS)
	{
		program->paths[index] = ft_strtrim(elements[index], WHITESPACE);
		if (program->paths[index] == NULL)
		{
			ft_putendl_fd("Path is NULL", 2);
			return (false);
		}
		if (check_png(elements[index]) != true)
			return (false);
		index++;
	}
	return (true);
}

bool	convert_digits(char **input, uint32_t *color)
{
	int	i;
	int	colors[3];

	i = 0;
	while (i < 3)
	{
		colors[i] = ft_atorgb(input[i]);
		if (colors[i] < 0)
		{
			ft_putstr_fd("Incorrect RGB input\n", 2);
			return (false);
		}
		i++;
	}
	*color = colors[0] << 24 | colors[1] << 16 | colors[2] << 8 | 255;
	return (true);
}

bool	convert_rgb(const char *input, uint32_t *color)
{
	char		**elements;

	elements = ft_split(input, ',');
	if (elements == NULL)
	{
		ft_putendl_fd("Failed to split rgb", 2);
		return (false);
	}
	if (_check_rgb_input(elements) != true)
	{
		free_char_arr(elements);
		return (false);
	}
	if (convert_digits(elements, color) != true)
	{
		free_char_arr(elements);
		return (false);
	}
	free_char_arr(elements);
	return (true);
}

bool	validate_rgb_input(char **elements, t_program *program)
{
	if (convert_rgb(elements[F], &program->player->floor_color) != true)
		return (false);
	if (convert_rgb(elements[C], &program->player->ceiling_color) != true)
		return (false);
	return (true);
}

bool	validate_nr_of_identifiers(char **elements)
{
	size_t	index;

	index = 0;
	while (index < SIZE)
	{
		if (elements[index] == NULL)
		{
			ft_putstr_fd("Missing object input\n", 2);
			return (false);
		}
		index++;
	}
	return (true);
}
