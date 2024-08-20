#include "../../include/cub_parser.h"
#include "../../include/cub3D.h"

static	void	_check_edge_case(int fd, char *trim, char *line)
{
	_free_helper(&trim, &line);
	if (errno != 0)
	{
		while (1)
		{
			line = get_next_line(fd);
			if (line == NULL)
				break ;
			free(line);
		}
	}
}

// Place the identifiers in the right order for parsing.
// Pre check for double elements.
static	bool	is_identifier(const char *trimmed_line, char **elements)
{
	static const char	*g_labels[] = G_LABELS;
	int					i;

	i = 0;
	errno = 0;
	while (i < SIZE)
	{
		if (!ft_strncmp(trimmed_line, g_labels[i], ft_strlen(g_labels[i])))
		{
			free(elements[i]);
			elements[i] = _parse_ident(elements, i, trimmed_line);
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

	trimmed_line = NULL;
	while (1)
	{
		flag = true;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		trimmed_line = ft_strtrim(line, "\10\11\13\14\15\40");
		if (trimmed_line == NULL)
			break ;
		if (trimmed_line[0] && flag == true)
			flag = is_identifier(trimmed_line, elements);
		if (errno != 0)
			break ;
		if (_check_token(trimmed_line, elements, flag) != true)
			break ;
		_free_helper(&trimmed_line, &line);
	}
	_free_helper(&trimmed_line, &line);
	_check_edge_case(fd, trimmed_line, line);
}

// allocate space for the elements & fill the char pointer with tokenized input.
char	**tokenize_input(char *argv)
{
	int			fd;
	char		**elements;

	elements = ft_calloc(SIZE + 1, sizeof(char *));
	if (elements == NULL)
	{
		ft_putendl_fd("failed to calloc elements", 2);
		return (NULL);
	}
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Failed to open the map", 2);
		return (NULL);
	}
	get_elements(fd, elements);
	close(fd);
	return (elements);
}
