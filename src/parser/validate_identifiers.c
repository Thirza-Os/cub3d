#include "../../include/cub_parser.h"

bool	validate_structure_paths(char **elements, t_program *program)
{
	int	index;

	index = 0;
	while (index < 4)
	{
		if (check_png(elements[index]) != true || (ft_strncmp("./", elements[index], 2) != 0))
			return (false);
		program->paths[index] = ft_strdup(elements[index]);
		if (program->paths[index] == NULL)
		{
			perror("path");
			return (false);
		}
		// free(elements[index]);
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

bool	convert_rgb(char *input, uint32_t *color)
{
	char	**split_elements;
	char	*temp;
	int		i;

	i = 0;
	split_elements = ft_split(input, ',');
	if (split_elements == NULL)
	{
		ft_putstr_fd("Failed to split rgb\n", 2);
		return (false);
	}
	while (split_elements[i])
		i++;
	if (i != 3)
	{
		ft_putstr_fd("Incorrect RGB input\n", 2);
		return (false);
	}
	i = 0;
	while (split_elements[i])
	{
		temp = ft_strtrim(split_elements[i], WHITESPACE);
		if (temp == NULL)
		{
			ft_putstr_fd("Faield to trim\n", 2);
			printf("free elements\n");
			return (false);
		}
		free(split_elements[i]);
		split_elements[i] = temp;
		i++;
	}
	if (convert_digits(split_elements, color) != true)
	{
		printf("free elements\n");
		return (false);
	}
	// ft_free(split_elements);
	// free(input);
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
			errno = EINVAL;
			return (false);
		}
		index++;
	}
	return (true);
}
