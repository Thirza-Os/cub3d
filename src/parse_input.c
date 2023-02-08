#include "cub3d.h"

int	check_cub(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len == 0 || ft_strncmp(&arg[len - 4], ".cub", 4) != 0)
		print_error("Not a .cub file!");
	return (0);
}

char	*ft_strjoin_free_cub3d(char const *s1, char const *s2)
{
	char	*str;
	size_t	a;
	size_t	b;

	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
	{
		free ((char *)s1);
		free ((char *)s2);
		return (NULL);
	}
	a = ft_strlen(s1);
	b = 0;
	ft_memcpy(str, s1, a);
	while (s2[b])
	{
		str[a] = s2[b];
		a++;
		b++;
	}
	str[a] = '\0';
	free((char *)s1);
	free((char *)s2);
	return (str);
}

int	is_identifier(char *line, t_textures *texture)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (!ft_strncmp(line, g_labels[i], ft_strlen(g_labels[i])))
		{
			if (texture->elements[i] != '\0')
			{
				ft_free_narr(texture->elements, SIZE);
				print_error("invalid object input");
			}
			texture->elements[i] = ft_strdup(line);
			return (1);
		}
		i++;
	}
	return (0);
}

void	validate_identifiers(t_textures *texture)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (!texture->elements[i])
		{
			ft_free_narr(texture->elements, SIZE);
			print_error("invalid object input");
		}
		i++;
	}
}

// leak all structs
// handle all spaces and enters.
void	parse_content(char *argv)
{
	char		*line;
	char		*trimmed_line;
	t_textures	texture;
	char		*map;
	int			fd;
	int			id;
	int			i;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		print_error("File opening failed.");
	line = get_next_line(fd);
	if (line == '\0')
		print_error("The map is empty");
	map = NULL;
	i = 0;
	ft_bzero(&texture, sizeof(t_textures));
	while (line != NULL)
	{
		trimmed_line = ft_strtrim(line, WHITESPACE);
		id = is_identifier(trimmed_line, &texture);
		while (id != 0)
		{
			free(line);
			free(trimmed_line);
			line = get_next_line(fd);
			trimmed_line = ft_strtrim(line, WHITESPACE);
			id = is_identifier(trimmed_line, &texture);
		}
		validate_identifiers(&texture);
		i = 0;
		if (ft_strchr("01NSEW", trimmed_line[i]))
		{
			free(trimmed_line);
			map = ft_strjoin_free_cub3d(map, line);
			line = NULL;
			i++;
			line = get_next_line(fd);
		}
	}
	free(line);
	close(fd);
	printf("%s\n", map);
	// return (map_array);
}

void	parse_input(int argc, char *argv[])
{
	check_cub(argv[1]);
	parse_content(argv[1]);
}
