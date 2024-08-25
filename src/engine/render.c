/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:22:13 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/25 17:57:06 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static	void	_init_dda(t_dda *dda, const t_player *player)
{
	int				index;
	const char		dirs[4] = "NESW";
	const double	values[4][4] = {{0, -1, 0.66, 0}, {1, 0, 0, 0.66}, \
									{0, 1, -0.66, 0}, {-1, 0, 0, -0.66}};

	index = 0;
	while (index < 4)
	{
		if (dirs[index] == player->starting_dir)
		{
			dda->player_dir.col = values[index][0];
			dda->player_dir.row = values[index][1];
			dda->plane.col = values[index][2];
			dda->plane.row = values[index][3];
			break ;
		}
		index++;
	}
}

static void	_display(uint32_t **img_buffer, mlx_image_t *img)
{
	int	row;
	int	col;

	row = 0;
	while (row < SCR_HEIGHT)
	{
		col = 0;
		while (col < SCR_WIDTH)
		{
			mlx_put_pixel(img, col, row, img_buffer[row][col]);
			col++;
		}
		row++;
	}
}

void	render(void *data)
{
	t_mlx_state	*mlx_state;
	t_dda		*dda;
	size_t		col;
	t_program	*program;

	program = data;
	mlx_state = program->mlx_state;
	dda = program->dda;
	ft_memset(mlx_state->img->pixels, 0, SCR_WIDTH * SCR_HEIGHT);
	col = 0;
	while (col < SCR_WIDTH)
	{
		dda_info(dda, program->player, col);
		fill_buffer(mlx_state, dda, program->player, col);
		col++;
	}
	_display(mlx_state->img_buffer, mlx_state->img);
}

static void	adjust_spawn_position(char **map, t_dvector *pos)
{
	const double	directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	double			check_row;
	double			check_col;
	int				i;

	i = 0;
	while (i < 4)
	{
		check_row = pos->row + directions[i][0] * SPAWN_BUFFER;
		check_col = pos->col + directions[i][1] * SPAWN_BUFFER;
		if (hit_wall(map, check_row, check_col))
		{
			pos->row -= directions[i][0] * SPAWN_BUFFER;
			pos->col -= directions[i][1] * SPAWN_BUFFER;
		}
		i++;
	}
}

t_dda	*init_dda(t_player *player)
{
	t_dda	*dda;

	dda = ft_calloc(1, sizeof(*dda));
	if (dda == NULL)
	{
		_free_player(player);
		perror("dda");
		return (NULL);
	}
	dda->player_pos.col = player->player_pos.col;
	dda->player_pos.row = player->player_pos.row;
	adjust_spawn_position(player->map, &dda->player_pos);
	_init_dda(dda, player);
	return (dda);
}
