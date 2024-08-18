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
			_free_helper(NULL, &line);
		}
	}
}

static	bool	_ident_error(char *msg, int error)
{
	ft_putendl_fd(msg, 2);
	if (error != 0)
		errno = error;
	return (false);
}

// Place the identifiers in the right order for parsing.
// Pre check for double elements.
static	bool	is_identifier(char *trimmed_line, char **elements)
{
	static const char	*g_labels[] = G_LABELS;
	int					i;
	char				*temp;

	i = 0;
	errno = 0;
	while (i < SIZE)
	{
		if (!ft_strncmp(trimmed_line, g_labels[i], ft_strlen(g_labels[i])))
		{
			if (elements[i] != NULL)
				return (_ident_error("Invalid object input", EINVAL));
			if (i < 4)
				elements[i] = ft_substr(trimmed_line, 2, \
							(ft_strlen(trimmed_line) - 2));
			else
				elements[i] = ft_substr(trimmed_line, 1, \
							(ft_strlen(trimmed_line) - 1));
			if (elements[i] == NULL)
				return (_ident_error("substring failed", 0));
			temp = ft_strtrim(elements[i], WHITESPACE);
			if (temp == NULL)
				return (_ident_error("trim failed", 0));
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
			ft_putendl_fd("Failed to trim a line", 2);
			break ;
		}
		if (trimmed_line[0] && flag == true)
			flag = is_identifier(trimmed_line, elements);
		if (errno != 0)
			break ;
		if (_check_token(trimmed_line, elements, flag) != true)
			break ;
		_free_helper(&trimmed_line, &line);
	}
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
