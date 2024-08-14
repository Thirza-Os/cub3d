#include "../../include/cub_parser.h"

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
static	bool	is_identifier(char *trimmed_line, char **elements)
{
	static const char *g_labels[] = G_LABELS;
	int		i;
	char	*temp;

	i = 0;
	errno = 0;
	while (i < SIZE)
	{
		if (!ft_strncmp(trimmed_line, g_labels[i], ft_strlen(g_labels[i])))
		{
			// if (elements[i] != '\0')
			if (elements[i] != NULL)
			{
				ft_putstr_fd("invalid object input\n", 2);
				errno = EINVAL;
				return false;
			}
			if (i < 4)
				elements[i] = ft_substr(trimmed_line, 2, (ft_strlen(trimmed_line) - 2));
			else
				elements[i] = ft_substr(trimmed_line, 1, (ft_strlen(trimmed_line) - 1));
			if (elements[i] == NULL)
			{
				ft_putstr_fd("substring id failed", 2);
				return (false);
			}
			temp = ft_strtrim(elements[i], WHITESPACE);
			if (temp == NULL)
				return (false);
			free(elements[i]);
			elements[i] = temp;
			return (true);
		}
		i++;
	}
	return (false);
}

// Get input line by line.
// Check if the line contains identifier or map input.
// Handle as such:
// Use the trimmed line for elements, untrimmed line for the map.
// Pre check for the left trimmed lines in the map (has to be 1).
static	void	get_elements(int fd, char **elements)
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
		if (trimmed_line == NULL)
		{
			perror("trime fail");
			break ;
		}
		if (trimmed_line[0] && flag == 1)
			flag = is_identifier(trimmed_line, elements);
		if (errno != 0)
			break ;
		if (flag == true) {
			if (trimmed_line[0] == '1')
				elements[SIZE] = ft_strjoin_cub3d(elements[SIZE], line);
			else
			{
				printf("%s", trimmed_line);
				ft_putstr_fd("Invalid input: Invalid map\n", 2);
				break ;
			}
		}
		free(trimmed_line);
		free(line);
	}
	free(trimmed_line);
	free(line);
	if (errno != 0)
	{
		printf("read zodat we geen leaks hebben\n");
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
	{
		perror("Open map");
		// clean elements
		return (NULL);
	}
	get_elements(fd, elements);
	close(fd);
	return (elements);
}
