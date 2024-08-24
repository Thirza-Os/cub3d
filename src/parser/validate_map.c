/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:37 by tosinga       #+#    #+#                 */
/*   Updated: 2024/08/24 02:39:22 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static	int	check_characters(char *map, const char *g_positions[])
{
	int					index;
	char				start_dir;

	start_dir = '\0';
	if (_check_chars(map, &start_dir) != true)
	{
		ft_putendl_fd("Invalid map: No player input", 2);
		return (-1);
	}
	index = 0;
	while (g_positions[index])
	{
		if (*g_positions[index] == start_dir)
			break ;
		index++;
	}
	return (index);
}

static	bool	set_map_size(char *map, t_program *program)
{
	size_t		counter;
	size_t		col;
	t_player	*player;

	counter = 0;
	col = 0;
	player = program->player;
	while (map[counter] != '\0')
	{
		if (map[counter] == '\n')
		{
			player->max_map.row++;
			if ((int)col > player->max_map.col)
				player->max_map.col = col;
			col = 0;
		}
		else
			col++;
		counter++;
	}
	player->max_map.row++;
	if (player->max_map.row < 3)
		return (false);
	return (true);
}

static	bool	fill_map(char *map, t_program *program)
{
	char		**temp_map;

	temp_map = ft_split(map, '\n');
	if (temp_map == NULL)
	{
		ft_putstr_fd("Failed to split the map\n", 2);
		return (false);
	}
	if (_create_map(program) != true)
		return (false);
	_set_map(program->player, temp_map);
	free_char_arr(temp_map);
	return (true);
}

static	bool	fill_player(t_program *program)
{
	int	col;
	int	row;

	row = 0;
	while (row < program->player->max_map.row)
	{
		col = 0;
		while (col < program->player->max_map.col)
		{
			if (ft_strchr(PLAYER_POS, program->player->map[row][col]) != NULL)
			{
				program->player->player_pos.col = col;
				program->player->player_pos.row = row;
				return (true);
			}
			col++;
		}
		row++;
	}
	ft_putstr_fd("Failed to find player position\n", 2);
	return (false);
}

bool	validate_map(char *map, t_program *program)
{
	int					pos;
	static const char	*g_positions[] = {"N", "S", "W", "E"};

	pos = check_characters(map, g_positions);
	if (pos == -1)
		return (false);
	program->player->starting_dir = *g_positions[pos];
	if (set_map_size(map, program) != true)
	{
		ft_putendl_fd("Map is to small to play...", 2);
		return (false);
	}
	if (fill_map(map, program) != true)
		return (false);
	if (fill_player(program) != true)
		return (false);
	if (check_surrounded_walls(program) != true)
	{
		ft_putstr_fd("Map is not surrounded\n", 2);
		return (false);
	}
	return (true);
}
