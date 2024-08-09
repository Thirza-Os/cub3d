/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 01:47:28 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/09 03:33:26 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/dda.h"

static	void	move_up_and_down(t_program *program, int dir)
{
	double			spacing;
	t_cords_double	dc;
	t_cords_double	cord;
	t_dda			*dda;

	spacing = 0.32;
	dda = program->dda;
	cord = dda->player_pos;
	dc.col = dda->player_dir.col * MOVESPEED * dir;
	if (dc.col < 0)
		spacing = -0.32;
	if (hitting_wall(dda, cord.row, cord.col + dc.col + spacing) != true)
		program->dda->player_pos.col += dc.col;
	spacing = 0.32;
	dc.row = program->dda->player_dir.row * MOVESPEED * dir;
	if (dc.row < 0)
		spacing = -0.32;
	if (hitting_wall(dda, cord.row + dc.row + spacing, cord.col) != true)
		dda->player_pos.row += dc.row;
	dda_calc(program);
}

static	void	move_left_rigth(t_program *program, int dir)
{
	double			spacing;
	t_cords_double	dc;
	t_cords_double	cord;
	t_dda			*dda;

	spacing = 0.32;
	dda = program->dda;
	cord = dda->player_pos;
	dc.col = -(program->dda->player_dir.row * MOVESPEED * dir);
	if (dc.col < 0)
		spacing = -0.32;
	if (hitting_wall(dda, cord.row, cord.col + dc.col + spacing) != true)
		program->dda->player_pos.col += dc.col;
	spacing = 0.32;
	dc.row = program->dda->player_dir.col * MOVESPEED * dir;
	if (dc.row < 0)
		spacing = -0.32;
	if (hitting_wall(dda, cord.row + dc.col + spacing, cord.col) != true)
		program->dda->player_pos.row += dc.row;
	dda_calc(program);
}

static	void	turn_around(t_program *program, int dir)
{
	t_vector	o_dir;
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
	dda_calc(program);
}

void	hooks(void *param)
{
	t_program	*program;
	t_mlx_state	*mlx_state;

	program = param;
	mlx_state = program->mlx_state;
	if (mlx_is_key_down(mlx_state->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx_state->mlx);
	if (mlx_is_key_down(mlx_state->mlx, MLX_KEY_W))
		move_up_and_down(program, FORWARD);
	if (mlx_is_key_down(mlx_state->mlx, MLX_KEY_S))
		move_up_and_down(program, BACKWARD);
	if (mlx_is_key_down(mlx_state->mlx, MLX_KEY_A))
		move_left_rigth(program, LEFTWARD);
	if (mlx_is_key_down(mlx_state->mlx, MLX_KEY_D))
		move_left_rigth(program, RIGHTWARD);
	if (mlx_is_key_down(mlx_state->mlx, MLX_KEY_LEFT))
		turn_around(program, TURNLEFT);
	if (mlx_is_key_down(mlx_state->mlx, MLX_KEY_RIGHT))
		turn_around(program, TURNRIGHT);
}
