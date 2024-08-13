/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:22:13 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/13 01:36:17 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/dda.h"
#include "cub3D.h"

bool	_hit_wall(const t_dda *dda, double row, double col)
{
	int irow = (int)row;
	int icol = (int)col;
	printf("cool double: %f, %f\n", row, col);
	printf("cool int: %d, %d\n", irow, icol);
	if (dda->player->map[irow][icol] == '1')
		return (true);
	return (false);
}

static	void	_move_up_and_down(t_program *program, int dir)
{
    t_dda *dda = program->dda;
    t_dvector new_pos;

    // Calculate potential new positions based on direction
    new_pos.col = dda->player_pos.col + dda->player_dir.col * MOVESPEED * dir;
    new_pos.row = dda->player_pos.row + dda->player_dir.row * MOVESPEED * dir;

    // Check if the new position would collide with a wall (including small buffer)
    if (!hit_wall(dda, (int)new_pos.row, (int)(dda->player_pos.col))) {
        dda->player_pos.row = new_pos.row;
    }
    if (!hit_wall(dda, (int)(dda->player_pos.row), (int)new_pos.col)) {
        dda->player_pos.col = new_pos.col;
    }
}

static	void	_move_left_rigth(t_program *program, int dir)
{
    t_dda *dda = program->dda;
    t_dvector new_pos;

    // Calculate potential new positions based on strafing direction
    new_pos.col = dda->player_pos.col - dda->player_dir.row * MOVESPEED * dir;
    new_pos.row = dda->player_pos.row + dda->player_dir.col * MOVESPEED * dir;

    // Check if the new position would collide with a wall (including small buffer)
    if (!hit_wall(dda, (int)new_pos.row, (int)(dda->player_pos.col))) {
        dda->player_pos.row = new_pos.row;
    }
    if (!hit_wall(dda, (int)(dda->player_pos.row), (int)new_pos.col)) {
        dda->player_pos.col = new_pos.col;
    }
}

static	void	_turn_around(t_program *program, int dir)
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
	// render(program);
}

void	hooks(void *param)
{
	t_program	*program;
	t_mlx_state	*mlx_state;

	program = param;
	mlx_state = program->mlx_state;
	if (mlx_is_key_down(mlx_state->mlx, MLX_KEY_ESCAPE))
		clean_cub(program);
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
