#include "../../include/cub_parser.h"

static char	*ft_strjoin_cub3d(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	b;

	s1_len = ft_strlen(s1);
	str = ft_calloc(s1_len + ft_strlen(s2) + 1, sizeof(*str));
	if (str == NULL)
		return (NULL);
	b = 0;
	ft_memcpy(str, s1, s1_len);
	while (s2[b] != '\0')
	{
		str[s1_len] = s2[b];
		s1_len++;
		b++;
	}
	str[s1_len] = '\0';
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
			if (elements[i] != NULL)
			{
				ft_putstr_fd("invalid object input\n", 2);
				errno = EINVAL;
				return (false);
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
			{
				printf("trim fail\n");
				return (false);
			}
			free(elements[i]);
			elements[i] = temp;
			return (false);
		}
		i++;
	}
	return (true);
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
	bool		flag;

	while (1)
	{
		flag = true;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		trimmed_line = ft_strtrim(line, WHITESPACE);
		if (trimmed_line == NULL)
		{
			perror("trime fail");
			break ;
		}
		if (trimmed_line[0] && flag == true)
			flag = is_identifier(trimmed_line, elements);
		if (errno != 0)
			break ;
		if (flag == true)
		{
			if (trimmed_line[0] == '1')
				elements[SIZE] = ft_strjoin_cub3d(elements[SIZE], line);
			else
			{
				errno = EINVAL;
				printf("%s", trimmed_line);
				ft_putstr_fd("Invalid input: Invalid map\n", 2);
				break ;
			}
		}
		free(trimmed_line);
		free(line);
		trimmed_line = NULL;
		line = NULL;
	}
	if (trimmed_line != NULL)
		free(trimmed_line);
	if (line != NULL)
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
