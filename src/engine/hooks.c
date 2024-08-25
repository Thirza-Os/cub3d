/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:22:13 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/25 17:49:31 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static	void	_move_up_and_down(const t_program *program, int dir)
{
	t_dda		*dda;
	t_dvector	new_pos;

	dda = program->dda;
	new_pos.col = dda->player_pos.col + dda->player_dir.col * MOVESPEED * dir;
	new_pos.row = dda->player_pos.row + dda->player_dir.row * MOVESPEED * dir;
	if (!hit_wall(program->player->map, \
			new_pos.row + WALL_BUFFER * dda->player_dir.row, \
			dda->player_pos.col) \
		&& !hit_wall(program->player->map, \
			new_pos.row - WALL_BUFFER * dda->player_dir.row, \
			dda->player_pos.col))
	{
		dda->player_pos.row = new_pos.row;
	}
	if (!hit_wall(program->player->map, \
			dda->player_pos.row, \
			new_pos.col + WALL_BUFFER * dda->player_dir.col)
		&& !hit_wall(program->player->map, \
			dda->player_pos.row, \
			new_pos.col - WALL_BUFFER * dda->player_dir.col))
	{
		dda->player_pos.col = new_pos.col;
	}
}

static	void	_move_left_rigth(const t_program *program, int dir)
{
	t_dda		*dda;
	t_dvector	new_pos;

	dda = program->dda;
	new_pos.col = dda->player_pos.col - dda->player_dir.row * MOVESPEED * dir;
	new_pos.row = dda->player_pos.row + dda->player_dir.col * MOVESPEED * dir;
	if (!hit_wall(program->player->map, \
			new_pos.row + WALL_BUFFER * dda->player_dir.col, \
			dda->player_pos.col) \
		&& !hit_wall(program->player->map, \
			new_pos.row - WALL_BUFFER * dda->player_dir.col, \
			dda->player_pos.col))
	{
		dda->player_pos.row = new_pos.row;
	}
	if (!hit_wall(program->player->map, \
			dda->player_pos.row, \
			new_pos.col + WALL_BUFFER * dda->player_dir.row) \
		&& !hit_wall(program->player->map, \
			dda->player_pos.row, \
			new_pos.col - WALL_BUFFER * dda->player_dir.row))
	{
		dda->player_pos.col = new_pos.col;
	}
}

static	void	_turn_around(const t_program *program, int dir)
{
	t_dvector	o_dir;
	double		plane;
	t_dda		*dda;

	dda = program->dda;
	o_dir.col = dda->player_dir.col;
	dda->player_dir.col = dda->player_dir.col * cos(ROTSPEED * dir) - \
							dda->player_dir.row * sin(ROTSPEED * dir);
	dda->player_dir.row = o_dir.col * sin(ROTSPEED * dir) + \
							dda->player_dir.row * cos(ROTSPEED * dir);
	plane = dda->plane.col;
	dda->plane.col = dda->plane.col * cos(ROTSPEED * dir) - \
							dda->plane.row * sin(ROTSPEED * dir);
	dda->plane.row = plane * sin(ROTSPEED * dir) + \
							dda->plane.row * cos(ROTSPEED * dir);
}

void	hooks(void *param)
{
	t_program	*program;
	t_mlx_state	*mlx_state;

	program = param;
	mlx_state = program->mlx_state;
	if (mlx_is_key_down(mlx_state->mlx, MLX_KEY_ESCAPE))
		free_cub(program, 0);
	if (mlx_is_key_down(mlx_state->mlx, MLX_KEY_W))
		_move_up_and_down(program, FORWARD);
	if (mlx_is_key_down(mlx_state->mlx, MLX_KEY_S))
		_move_up_and_down(program, BACKWARD);
	if (mlx_is_key_down(mlx_state->mlx, MLX_KEY_A))
		_move_left_rigth(program, LEFTWARD);
	if (mlx_is_key_down(mlx_state->mlx, MLX_KEY_D))
		_move_left_rigth(program, RIGHTWARD);
	if (mlx_is_key_down(mlx_state->mlx, MLX_KEY_LEFT))
		_turn_around(program, TURNLEFT);
	if (mlx_is_key_down(mlx_state->mlx, MLX_KEY_RIGHT))
		_turn_around(program, TURNRIGHT);
}
