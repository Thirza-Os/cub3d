/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:22:13 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/12 21:52:44 by lvan-gef      ########   odam.nl         */
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
	double		spacing;
	t_dvector	dc;
	t_dvector	cord;
	t_dda		*dda;

	spacing = 0.32;
	dda = program->dda;
	printf("cool dda: %f, %f\n", dda->player_pos.row, dda->player_pos.col);
	cord = dda->player_pos;
	printf("cool cord: %f, %f\n", cord.row, cord.col);
	dc.col = dda->player_dir.col * MOVESPEED * dir;
	if (dc.col < 0)
		spacing = -0.32;
	double kev_row = cord.row + dc.row + spacing;
	double kev_col = cord.col + dc.col + spacing;
	int ikr = (int)kev_row;
	int ikc = (int)kev_col;
	char walltype = dda->player->map[ikr][ikc];
	printf("walltype: %c\n", walltype);
    if (walltype != '1')
		program->dda->player_pos.col += dc.col;
	// if (_hit_wall(dda, cord.row, cord.col + dc.col + spacing) != true)
	// 	program->dda->player_pos.col += dc.col;
	spacing = 0.32;
	dc.row = program->dda->player_dir.row * MOVESPEED * dir;
	if (dc.row < 0)
		spacing = -0.32;
	kev_row = cord.row + dc.row + spacing;
	kev_col = cord.col + dc.col + spacing;
	ikr = (int)kev_row;
	ikc = (int)kev_col;
	walltype = dda->player->map[ikr][ikc];
	printf("walltype: %c\n", walltype);
    if (walltype != '1')
		dda->player_pos.row += dc.row;
	   //  render(program);
	// if (_hit_wall(dda, cord.row + dc.row + spacing, cord.col) != true)
	// 	dda->player_pos.row += dc.row;
	// // print_dda(program->dda);
	printf("ik sta hier: %f, %f, ik ga naar: %f, %f\n", dda->player_pos.row, dda->player_pos.col, cord.row + dc.row + spacing, cord.col + dc.col + spacing);

	// double kev_row = cord.row + dc.row + spacing;
	// double kev_col = cord.col + dc.col + spacing;
	//
	// int ikr = (int)kev_row;
	// int ikc = (int)kev_col;
	//
	// printf("kev: %f,%f,%d,%d\n",kev_row,kev_col,ikr,ikc);
	// char walltype = dda->player->map[ikr][ikc];
	// printf("walltype: %c\n", walltype);
    // if (walltype != '1')
	   //  render(program);
}

static	void	_move_left_rigth(t_program *program, int dir)
{
	double		spacing;
	t_dvector	dc;
	t_dvector	cord;
	t_dda		*dda;

	spacing = 0.32;
	dda = program->dda;
	cord = dda->player_pos;
	dc.col = -(program->dda->player_dir.row * MOVESPEED * dir);
	if (dc.col < 0)
		spacing = -0.32;
	// if (hit_wall(dda, cord.row, cord.col + dc.col + spacing) != true)
	double kev_row = cord.row + dc.row + spacing;
	double kev_col = cord.col + dc.col + spacing;
	int ikr = (int)kev_row;
	int ikc = (int)kev_col;
	char walltype = dda->player->map[ikr][ikc];
	printf("walltype: %c\n", walltype);
    if (walltype != '1')
		program->dda->player_pos.col += dc.col;
	spacing = 0.32;
	dc.row = program->dda->player_dir.col * MOVESPEED * dir;
	if (dc.row < 0)
		spacing = -0.32;
	// if (hit_wall(dda, cord.row + dc.col + spacing, cord.col) != true)
	kev_row = cord.row + dc.row + spacing;
	kev_col = cord.col + dc.col + spacing;
	ikr = (int)kev_row;
	ikc = (int)kev_col;
	walltype = dda->player->map[ikr][ikc];
	printf("walltype: %c\n", walltype);
    if (walltype != '1')
		program->dda->player_pos.row += dc.row;
	// render(program);
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
