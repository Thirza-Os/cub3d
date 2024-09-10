/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map_surrounded.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:41 by tosinga       #+#    #+#                 */
/*   Updated: 2024/09/10 19:01:55 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static	bool	_has_valid_chars(char **map, t_check_wall cw, size_t height)
{
	while (cw.end > cw.start && map[cw.row][cw.end] == ' ')
		cw.end--;
	if (map[cw.row][cw.start] != '1' || map[cw.row][cw.end] != '1')
		return (false);
	if (cw.row == 0 || cw.row == height - 1)
	{
		cw.col = cw.start;
		while (cw.col <= cw.end)
		{
			if (map[cw.row][cw.col] != '1' && map[cw.row][cw.col] != ' ')
				return (false);
			cw.col++;
		}
	}
	return (true);
}

static	bool	_check_first_and_last_non_space(char **map, size_t height)
{
	t_check_wall	cw;

	cw.row = 0;
	cw.col = 0;
	while (cw.row < height)
	{
		cw.len = ft_strlen(map[cw.row]);
		cw.start = 0;
		cw.end = cw.len - 1;
		while (cw.start < cw.len && map[cw.row][cw.start] == ' ')
			cw.start++;
		if (cw.start == cw.len)
			continue ;
		if (_has_valid_chars(map, cw, height) != true)
			return (false);
		cw.row++;
	}
	return (true);
}

static	bool	_check_inner_loop(char **map, t_check_wall cw, size_t height)
{
	while (cw.col < cw.len)
	{
		if (map[cw.row][cw.col] != '1' && map[cw.row][cw.col] != ' ')
		{
			if (cw.row > 0 && (cw.col >= ft_strlen(map[cw.row - 1]) || \
				map[cw.row - 1][cw.col] == ' '))
				return (false);
			if (cw.row < height - 1 && (cw.col >= ft_strlen(map[cw.row + 1]) || \
				map[cw.row + 1][cw.col] == ' '))
				return (false);
			if (cw.col > 0 && map[cw.row][cw.col - 1] == ' ')
				return (false);
			if (cw.col < cw.len - 1 && map[cw.row][cw.col + 1] == ' ')
				return (false);
		}
		cw.col++;
	}
	return (true);
}

static	bool	_check_is_valid(char **map, size_t height)
{
	t_check_wall	cw;

	cw.row = 1;
	cw.start = 0;
	cw.end = 0;
	while (cw.row < height - 1)
	{
		cw.len = ft_strlen(map[cw.row]);
		cw.col = 0;
		if (_check_inner_loop(map, cw, height) != true)
			return (false);
		cw.row++;
	}
	return (true);
}

bool	check_surrounded_walls(char **map)
{
	size_t	height;

	height = 0;
	while (map[height] != NULL)
		height++;
	if (height == 0)
		return (false);
	if (_check_first_and_last_non_space(map, height) != true)
		return (false);
	if (_check_is_valid(map, height) != true)
		return (false);
	return (true);
}
