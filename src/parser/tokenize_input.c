/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:37 by tosinga       #+#    #+#                 */
/*   Updated: 2024/09/11 02:46:15 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

static	bool	_is_identifier(const char *trimmed_line, char **elements)
{
	static const char	*g_labels[] = {"NO", "SO", "WE", "EA", "F", "C"};
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

static void	_get_elements(int fd, char **elements)
{
	char		*line;
	bool		flag;

	while (1)
	{
		flag = true;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line && flag == true)
			flag = _is_identifier(line, elements);
		if (errno != 0)
			break ;
		if (_check_token(line, elements, flag) != true)
			break ;
		_free_helper(&line, &line);
	}
	_free_helper(&line, &line);
	_check_edge_case(fd, line, line);
}

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
	_get_elements(fd, elements);
	close(fd);
	return (elements);
}
