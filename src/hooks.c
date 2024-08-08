#include "../include/dda.h"

static	void	move_up_and_down(t_program *program, int dir)
{
	double	cur_pos_col;
	double	dx;
	double	dy;
	double	spacing;

	cur_pos_col = program->dda->player_pos.col;
	dx = program->dda->player_dir.col * MOVESPEED * dir;
	if (dx > 0)
		spacing = 0.32;
	else
		spacing = -0.32;
	if (!hitting_wall(program->dda, program->dda->player_pos.col + dx + spacing, program->dda->player_pos.row))
		program->dda->player_pos.col += dx;
	dy = program->dda->player_dir.row * MOVESPEED * dir;
	if (dy > 0)
		spacing = 0.32;
	else
		spacing = -0.32;
	if (!hitting_wall(program->dda, program->dda->player_pos.row + dy + spacing, cur_pos_col))
		program->dda->player_pos.row += dy;
	dda(program);
}

static	void	move_left_rigth(t_program *program, int dir)
{
	double	current_pos_x;
	double	dx;
	double	dy;
	double	spacing;

	current_pos_x = program->dda->player_pos.col;
	dx = -(program->dda->player_dir.row * MOVESPEED * dir);
	if (dx > 0)
		spacing = 0.32;
	else
		spacing = -0.32;
	if (!hitting_wall(program->dda, program->dda->player_pos.col + dx + spacing, program->dda->player_pos.row))
		program->dda->player_pos.col += dx;
	dy = program->dda->player_dir.col * MOVESPEED * dir;
	if (dy > 0)
		spacing = 0.32;
	else
		spacing = -0.32;
	if (!hitting_wall(program->dda, current_pos_x, program->dda->player_pos.row + dy + spacing))
		program->dda->player_pos.row += dy;
	dda(program);
}


static	void	turn_around(t_program *program, int dir)
{
	t_vector	old_dir;
	double		old_plane_x;

	old_dir.col = program->dda->player_dir.col;
	program->dda->player_dir.col = program->dda->player_dir.col * cos(ROTSPEED * dir) - \
							program->dda->player_dir.row * sin(ROTSPEED * dir);
	program->dda->player_dir.row = old_dir.col * sin(ROTSPEED * dir) + \
							program->dda->player_dir.row * cos(ROTSPEED * dir);
	old_plane_x = program->dda->plane.col;
	program->dda->plane.col = program->dda->plane.col * cos(ROTSPEED * dir) - \
							program->dda->plane.row * sin(ROTSPEED * dir);
	program->dda->plane.row = old_plane_x * sin(ROTSPEED * dir) + \
							program->dda->plane.row * cos(ROTSPEED * dir);
	dda(program);
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
