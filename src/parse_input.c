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
			print_error("Not a correct file input!");
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

void	check_format(char **elements)
{
	check_paths(elements);
	check_colors(elements);
	// check_maps(elements);
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
	// validate_map(elements[SIZE + 1]);
}

int	is_identifier(char *trimmed_line, char **elements)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < SIZE)
	{
		if (!ft_strncmp(trimmed_line, g_labels[i], ft_strlen(g_labels[i])))
		{
			if (elements[i] != '\0')
				print_error("invalid object input");
			if (i < 4)
				elements[i] = ft_substr(trimmed_line, 2, (ft_strlen(trimmed_line) - 2));
			else
				elements[i] = ft_substr(trimmed_line, 1, (ft_strlen(trimmed_line) - 1));
			temp = ft_strtrim(elements[i], WHITESPACE);
			free(elements[i]);
			elements[i] = temp;
			return (1);
		}
		i++;
	}
	return (0);
}

void	get_elements(int fd, char **elements)
{
	char		*trimmed_line;
	char		*line;
	int			flag;

	flag = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		trimmed_line = ft_strtrim(line, WHITESPACE);
		// if (!ft_strncmp(trimmed_line, "\0", sizeof(line)))
		// {
			if (flag == 1)
			{
				flag = is_identifier(trimmed_line, elements);
			}
			if (flag == 0)
			{
				// if (ft_strncmp(line, "\0", sizeof(line)))
				// 	print_error("Empty line in map");
				elements[SIZE] = ft_strjoin_cub3d(elements[SIZE], line);
			}
		// }
		free(trimmed_line);
		free(line);
	}
}

// leak all structs
// handle all spaces and enters.
char	**tokenize_input(char *argv)
{
	int			fd;
	char		**elements;

	elements = ft_calloc(SIZE + 1, sizeof(char *));
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		print_error("File opening failed.");
	get_elements(fd, elements);
	close(fd);
	return (elements);
}

void	parse_file(char	**elements)
{
	validate_identifiers(elements);
		// parse_textures(elements);
}

void	parse_input(int argc, char *argv[])
{
	// t_program	program;

	check_cub(argv[1]);
	parse_file(tokenize_input(argv[1]));

	// tokenize: raw
	// parse_file(argv[1]);
	// validate: check valid input && return struct

}
