/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:37 by tosinga       #+#    #+#                 */
/*   Updated: 2024/08/30 02:48:12 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "cub_parser.h"
#include "get_next_line.h"
#include <assert.h>

static	void	_hydrate_fd(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

// Place the identifiers in the right order for parsing.
// Pre check for double elements.
static	bool	parse_config(const char *line, char **elements)
{
	static const char	*labels[] = {"NO", "SO", "WE", "EA", "F", "C"};
	int					index;

	index = 0;
	errno = 0;
	while (index < SIZE)
	{
		while (*line != '\0' && *line == ' ')
		{
			line++;
		}
		if (!ft_strncmp(line, labels[index], ft_strlen(labels[index])))
		{
			free(elements[index]);
			elements[index] = _parse_ident(elements, index, line);
			return (true);
		}
		index++;
	}
	return (false);
}

// Get input line by line.
// Check if the line contains identifier or map input.
// Handle as such:
// Use the trimmed line for elements, untrimmed line for the map.
// Pre check for the left trimmed lines in the map (has to be 1).
static bool get_config(int fd, char **elements)
{
	char		*line;
	bool		is_config;

	is_config = true;
	while (is_config)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (false);
		is_config = parse_config(line, elements);
		if (errno != 0)
		{
			free(line);
			return (false);
		}
		free(line);
	}
	return (true);
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
		return (elements);
	}
	if (get_config(fd, elements) == true)
	{
		_get_raw_map(fd, elements);
	}
	_hydrate_fd(fd);
	return (elements);
}
