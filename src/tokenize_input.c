#include "cub3d.h"

static char	*ft_strjoin_cub3d(char const *s1, char const *s2)
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
	return (str);
}

// Place the identifiers in the right order for parsing.
// Pre check for double elements.
static int	is_identifier(char *trimmed_line, char **elements)
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
				elements[i] = \
				ft_substr(trimmed_line, 2, (ft_strlen(trimmed_line) - 2));
			else
				elements[i] = \
				ft_substr(trimmed_line, 1, (ft_strlen(trimmed_line) - 1));
			temp = ft_strtrim(elements[i], WHITESPACE);
			free(elements[i]);
			elements[i] = temp;
			return (1);
		}
		i++;
	}
	return (0);
}

// Get input line by line.
// Check if the line contains identifier or map input.
// Handle as such:
// Use the trimmed line for elements, untrimmed line for the map.
// Pre check for the left trimmed lines in the map (has to be 1).
static void	get_elements(int fd, char **elements)
{
	char		*line;
	char		*trimmed_line;
	int			flag;

	flag = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		trimmed_line = ft_strtrim(line, WHITESPACE);
		if (trimmed_line[0] && flag == 1)
			flag = is_identifier(trimmed_line, elements);
		if (flag == 0)
		{
			if (trimmed_line[0] == '1')
				elements[SIZE] = ft_strjoin_cub3d(elements[SIZE], line);
			else
				print_error("Invalid input: Invalid map");
		}
		free(trimmed_line);
		free(line);
	}
}

// allocate space for the elements & fill the char pointer with tokenized input.
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
