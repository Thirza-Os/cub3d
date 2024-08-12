/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:22:13 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/12 21:47:06 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include "../include/dda.h"
#include "cub_structs.h"

static	void	_init_dda(t_dda *dda)
{
	int				index;
	const char		dirs[4] = "NESW";
	const double	values[4][4] = {{0, -1, 0.66, 0}, {1, 0, 0, 0.66}, \
									{0, 1, -0.66, 0}, {-1, 0, 0, -0.66}};

	index = 0;
	while (index < 4)
	{
		if (dirs[index] == dda->player->starting_dir)
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
    t_program   *program;

    program = data;
	mlx_state = program->mlx_state;
	dda = program->dda;
	ft_memset(mlx_state->img->pixels, 0, SCR_WIDTH * SCR_HEIGHT);
	col = 0;
	while (col < SCR_WIDTH)
	{
		dda_info(dda, col);
		fill_buffer(mlx_state, dda, col);
		col++;
	}
	_display(mlx_state->img_buffer, mlx_state->img);
}

t_dda	*init_dda(t_player *player)
{
	t_dda	*dda;

	dda = ft_calloc(1, sizeof(*dda));
	if (dda == NULL)
	{
		_clean_player(player);
		perror("dda");
		return (NULL);
	}
	dda->player = player;
	dda->player_pos.col = dda->player->player_pos.col;
	dda->player_pos.row = dda->player->player_pos.row;
	_init_dda(dda);
	return (dda);
}
