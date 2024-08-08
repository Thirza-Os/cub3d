#include "../include/cub3D.h"
#include <math.h>

// static bool	hitting_wall(t_dda *dda, int x, int y)
// {
//     (void)dda;
//     (void)x;
//     (void)y;
// 	// if (dda->p->map[y][x] != '0')
// 	// 	return (true);
// 	return (false);
// }
//
// static void	move_forwards_backwards(t_dda *dda, int dir)
// {
// 	double	current_pos_x;
// 	double	dx;
// 	double	dy;
// 	double	spacing;
//
// 	current_pos_x = dda->player_pos.col;
// 	dx = dda->player_dir.col * MOVESPEED * dir;
// 	if (dx > 0)
// 		spacing = 0.32;
// 	else
// 		spacing = -0.32;
// 	if (!hitting_wall(dda, dda->player_pos.col + dx + spacing, dda->player_pos.row))
// 		dda->player_pos.col += dx;
// 	dy = dda->player_dir.row * MOVESPEED * dir;
// 	if (dy > 0)
// 		spacing = 0.32;
// 	else
// 		spacing = -0.32;
// 	if (!hitting_wall(dda, current_pos_x, dda->player_pos.row + dy + spacing))
// 		dda->player_pos.row += dy;
// }
//
// static void	move_left_right(t_dda *dda, int dir)
// {
// 	double	current_pos_x;
// 	double	dx;
// 	double	dy;
// 	double	spacing;
//
// 	current_pos_x = dda->player_pos.col;
// 	dx = -(dda->player_dir.row * MOVESPEED * dir);
// 	if (dx > 0)
// 		spacing = 0.32;
// 	else
// 		spacing = -0.32;
// 	if (!hitting_wall(dda, dda->player_pos.col + dx + spacing, dda->player_pos.row))
// 		dda->player_pos.col += dx;
// 	dy = dda->player_dir.col * MOVESPEED * dir;
// 	if (dy > 0)
// 		spacing = 0.32;
// 	else
// 		spacing = -0.32;
// 	if (!hitting_wall(dda, current_pos_x, dda->player_pos.row + dy + spacing))
// 		dda->player_pos.row += dy;
// }
//
// static void	turn_left_right(t_dda *dda, int dir)
// {
// 	t_cords_double	old_dir;
// 	double			old_plane_x;
//
// 	old_dir.col = dda->player_dir.col;
// 	dda->player_dir.col = dda->player_dir.col * cos(ROTSPEED * dir) - dda->player_dir.row * sin(ROTSPEED * dir);
// 	dda->player_dir.row = old_dir.col * sin(ROTSPEED * dir) + dda->player_dir.row * cos(ROTSPEED * dir);
// 	old_plane_x = dda->plane.col;
// 	dda->plane.col = dda->plane.col * cos(ROTSPEED * dir) - dda->plane.row * sin(ROTSPEED * dir);
// 	dda->plane.row = old_plane_x * sin(ROTSPEED * dir) + dda->plane.row * cos(ROTSPEED * dir);
// }
//
// void	key_input(t_program *data)
// {
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
// 		// cleanup(data, EXIT_SUCCESS);
//         exit(99);
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
// 		move_forwards_backwards(data->dda, FORWARD);
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
// 		move_left_right(data->dda, LEFTWARD);
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
// 		move_forwards_backwards(data->dda, BACKWARD);
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
// 		move_left_right(data->dda, RIGHTWARD);
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
// 		turn_left_right(data->dda, LEFTWARD);
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
// 		turn_left_right(data->dda, RIGHTWARD);
// }
