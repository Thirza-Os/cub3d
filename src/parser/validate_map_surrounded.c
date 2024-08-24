/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map_surrounded.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:41 by tosinga       #+#    #+#                 */
/*   Updated: 2024/08/24 04:09:25 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static	void	_find_boundaries(t_check_wall *ck, t_ivector max_map, \
								char **map)
{
	int	row;
	int	col;

	row = 0;
	while (row < max_map.row)
	{
		if (map[row] == NULL)
			break ;
		col = 0;
		while (col < max_map.col)
		{
			if (map[row][col] != ' ')
			{
				ck->left = ft_min(ck->left, col);
				ck->right = ft_max(ck->right, col);
				ck->top = row;
				break ;
			}
		}
		row++;
	}
}

static	bool	_check_boundaries(t_check_wall *ck, char **map)
{
	ck->col = ck->left;
	while (ck->col < ck->right)
	{
		if (map[ck->top][ck->col] != '1' || map[ck->bottom][ck->col] != '1')
			return (false);
		ck->col++;
	}
	ck->row = ck->top;
	while (ck->row <= ck->bottom)
	{
		if (map[ck->row][ck->left] != '1' || map[ck->row][ck->right] != '1')
			return (false);
		ck->row++;
	}
	return (true);
}

static	bool	_check_neighbors(t_check_wall *ck, char **map)
{
	ck->dr = -1;
	while (ck->dr < 1)
	{
		ck->dc = -1;
		while (ck->dc < 1)
		{
			ck->nr = ck->row + ck->dr;
			ck->nc = ck->col + ck->dc;
			if (ck->nr < ck->top || ck->nr > ck->bottom || \
				ck->nc < ck->left || ck->nc > ck->right || \
				map[ck->nr][ck->nc] == ' ')
			{
				return (false);
			}
			ck->dc++;
		}
		ck->dr++;
	}
	return (true);
}

static	bool	_check_adjacent(t_check_wall *ck, char **map)
{
	ck->row = ck->top;
	while (ck->row < ck->bottom)
	{
		ck->col = ck->left;
		while (ck->col < ck->right)
		{
			if (map[ck->row][ck->col] == '0' || \
				ft_strchr(PLAYER_POS, map[ck->row][ck->col]))
			{
				if (_check_neighbors(ck, map) != true)
				{
					return (false);
				}
			}
		}
		ck->row++;
	}
	return (true);
}

bool	check_surrounded_walls(t_program *program)
{
	t_check_wall	check;
	t_player		*player;

	player = program->player;
	check.left = player->max_map.col;
	check.right = 0;
	check.top = 0;
	check.bottom = 0;
	check.row = 0;
	check.col = 0;
	_find_boundaries(&check, player->max_map, player->map);
	if (_check_boundaries(&check, player->map) != true)
		return (false);
	return (_check_adjacent(&check, player->map));
}
