/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_identifiers.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:22:22 by rbrune        #+#    #+#                 */
/*   Updated: 2023/07/06 14:22:23 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_structure_paths(char **elements, t_program *program)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!check_png(elements[i]) || (ft_strncmp("./", elements[i], 2) != 0))
			print_error("Incorrect filepath input!");
		program->textures[i] = ft_strdup(elements[i]);
		free (elements[i]);
		i++;
	}
}

void	convert_digits(char **input, int *colors)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		colors[i] = ft_atorgb(input[i]);
		if (colors[i] < 0)
			print_error("Incorrect RGB input");
		i++;
	}
}

void	convert_rgb(char *input, int *colors)
{
	char	**split_elements;
	char	*temp;
	int		i;

	i = 0;
	split_elements = ft_split(input, ',');
	while (split_elements[i])
		i++;
	if (i != 3)
		print_error("Incorrect RGB input");
	i = 0;
	while (split_elements[i])
	{
		temp = ft_strtrim(split_elements[i], WHITESPACE);
		free(split_elements[i]);
		split_elements[i] = temp;
		i++;
	}
	convert_digits(split_elements, colors);
	ft_free(split_elements);
	free(input);
}

void	validate_rgb_input(char **elements, t_program *program)
{
	convert_rgb(elements[F], program->floor_rgb);
	convert_rgb(elements[C], program->ceiling_rgb);
}

void	validate_nr_of_identifiers(char **elements)
{
	int	i;

	i = 0;
	while (i < SIZE + 1)
	{
		if (elements[i] == NULL)
			print_error("Missing object input");
		i++;
	}
}
