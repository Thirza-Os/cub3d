#include "cub3d.h"

void	validate_identifiers(char **elements)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (!elements[i])
		{
			ft_free_narr(elements, SIZE);
			print_error("invalid object input");
		}
		i++;
	}
}

int	is_identifier(char *trimmed_line, char **elements)
{
	int		i;

	i = 0;
	while (i < SIZE)
	{
		if (!ft_strncmp(trimmed_line, g_labels[i], ft_strlen(g_labels[i])))
		{
			if (elements[i] != '\0')
			{
				ft_free_narr(elements, SIZE);
				print_error("invalid object input");
			}
			if (i < 4)
				elements[i] = ft_substr(trimmed_line, 2, (ft_strlen(trimmed_line) - 2));
			else
				elements[i] = ft_substr(trimmed_line, 1, (ft_strlen(trimmed_line) - 1));
			elements[i] = ft_strtrim(elements[i], WHITESPACE);
			return (1);
		}
		i++;
	}
	return (0);
}
//.png
void	check_texture(char *element)
{
	int	fd;

	check_png(element);
}

void	check_color(char *element)
{
		printf("%s\n", element);
}

void	parse_textures(char **elements)
{
	int i;

	i = 0;
	while (i < SIZE)
	{
		while (i < 4)
		{
			check_texture(elements[i]);
			i++;
		}
		check_color(elements[i]);
		i++;
	}
}

void	extract_raw_content(char *line, int fd)
{
	//parse identfifiers
	//parse map
	char		*elements[SIZE];
	char		*trimmed_line;
	char		*map;
	int			id;
	int			i;

	map = NULL;
	ft_bzero(&elements, sizeof(elements));
	while (line != NULL)
	{
		trimmed_line = ft_strtrim(line, WHITESPACE);
		id = is_identifier(trimmed_line, elements);
		while (id != 0)
		{
			free(line);
			free(trimmed_line);
			line = get_next_line(fd);
			trimmed_line = ft_strtrim(line, WHITESPACE);
			id = is_identifier(trimmed_line, elements);
		}
		validate_identifiers(elements);
		i = 0;
		if (ft_strchr("01NSEW", trimmed_line[i]))
		{
			free(trimmed_line);
			map = ft_strjoin_free_cub3d(map, line);
			line = NULL;
			i++;
			line = get_next_line(fd);
		}
		// validate map
	}
	//parse to correct formats
	parse_textures(elements);
}

// leak all structs
// handle all spaces and enters.
void	parse_file(char *argv)
{
	char		*line;
	// t_textures	texture;
	int			fd;
	int			i;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		print_error("File opening failed.");
	line = get_next_line(fd);
	if (line == '\0')
		print_error("The map is empty");
	i = 0;
	//ft_bzero(&texture, sizeof(t_textures));
	extract_raw_content(line, fd);
	// free(line);
	close(fd);
	// return (map_array);
}

void	parse_input(int argc, char *argv[])
{
	check_cub(argv[1]);
	// tokenize: raw
	parse_file(argv[1]);
	// validate: check valid input && return struct

}
