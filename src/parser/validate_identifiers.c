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
		free(elements[index]);
		index++;
	}
	return (true);
}

// void	convert_digits(char **input, int *colors)
// {
// 	int	i;
// 	int	j;
//
// 	i = 0;
// 	j = 0;
// 	while (i < 3)
// 	{
// 		colors[i] = ft_atorgb(input[i]);
// 		if (colors[i] < 0)
// 			print_error("Incorrect RGB input");
// 		i++;
// 	}
// }
//
// void	convert_rgb(char *input, int *colors)
// {
// 	char	**split_elements;
// 	char	*temp;
// 	int		i;
//
// 	i = 0;
// 	split_elements = ft_split(input, ',');
// 	while (split_elements[i])
// 		i++;
// 	if (i != 3)
// 		print_error("Incorrect RGB input");
// 	i = 0;
// 	while (split_elements[i])
// 	{
// 		temp = ft_strtrim(split_elements[i], WHITESPACE);
// 		free(split_elements[i]);
// 		split_elements[i] = temp;
// 		i++;
// 	}
// 	convert_digits(split_elements, colors);
// 	ft_free(split_elements);
// 	free(input);
// }
//
// void	validate_rgb_input(char **elements, t_program *program)
// {
// 	convert_rgb(elements[F], program->floor_rgb);
// 	convert_rgb(elements[C], program->ceiling_rgb);
// }

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

