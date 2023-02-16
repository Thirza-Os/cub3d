#include "cub3d.h"

// extra ,, in rgb
// handle empty lines !!

void	check_paths(char **elements)
{
	int	i;

	i = 0;

	while (i < 4)
	{
		if (!check_png(elements[i]) || (ft_strncmp("./", elements[i], 2) != 0))
			print_error("Incorrect filepath input!");
		i++;
	}
}

void	convert_digits(char **input, int *colors)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		colors[i] = ft_atorgb(input[i]);
		if (colors[i] < 0)
			print_error("Incorrect RGB input");
		i++;
	}
}

void	validate_rgb(char *input, int *colors)
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

void	check_colors(char **elements)
{
	int	*f_colors;
	int	*c_colors;

	f_colors = (int *)malloc(sizeof (int));  //1 (16 bytes) ROOT LEAK: 0x7f9946e0dac0 [16]
	c_colors = (int *)malloc(sizeof (int)); // 1 (16 bytes) ROOT LEAK: 0x7f9946e0dac0 [16]
	validate_rgb(elements[F], f_colors);
	validate_rgb(elements[C], c_colors);
}

void	check_map(char *map)
{
	printf("%s\n", map);
}

void	check_format(char **elements)
{
	check_paths(elements);
	check_colors(elements);
	check_map(elements[SIZE]);
}

void	validate_identifiers(char **elements)
{
	int	i;

	i = 0;
	while (i < SIZE + 1)
	{
		if (elements[i] == NULL)
			print_error("Missing object input");
		i++;
	}
	check_format(elements);
}

void	parse_file(char	**elements)
{
	validate_identifiers(elements);
		// parse_textures(elements);
}

