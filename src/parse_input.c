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

int	is_identifier(line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (ft_strncmp(line, "NO", 2))
		return (1);
	else if (ft_strncmp(line, "SO", 2))
		return (2)
	else if (ft_strncmp(line, "WE", 2))
		return (3)
	else if (ft_strncmp(line, "ES", 2))
		return (4)
	return (0);
}

char	*parse_content(char *argv)
{
	char	**identifiers;
	char	*line;
	// char	*map_array;
	int		i;
	int		fd;
	int		id;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		print_error("File opening failed.");
	// map_array = NULL;
	i = 0;
	line = get_next_line(fd);
	if (line == '\0')
		print_error("The map is empty");
	while (line != NULL)
	{
		//handle empty lines
		id = is_identifier(line);
		while (id < 0)
			{
				//add line to identifiers
			}
		check_map(line);
			//start making map
			// map_array = ft_strjoin_free_cub3d(map_array, line);
			// line = NULL;
			// i++;
		// line = get_next_line(fd);
	}
	free(line);
	close(fd);
	printf("%s\n", map_array);
	return (map_array);
}

void	parse_input(int argc, char *argv[])
{
	check_cub(argv[1]);
	parse_content(argv[1]);
}
