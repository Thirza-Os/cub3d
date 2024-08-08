#include "../include/dda.h"

static uint32_t	get_pixel_value(t_mlx_state *mlx_state, t_cords_int tex_cords, int tex_n)
{
	uint8_t	*pixel_data;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	pixel_data = mlx_state->textures[tex_n]->pixels;
	r = pixel_data[(tex_cords.row * mlx_state->textures[tex_n]->width + tex_cords.col) * 4];
	g = pixel_data[(tex_cords.row * mlx_state->textures[tex_n]->width + tex_cords.col) * 4 + 1];
	b = pixel_data[(tex_cords.row * mlx_state->textures[tex_n]->width + tex_cords.col) * 4 + 2];
	a = pixel_data[(tex_cords.row * mlx_state->textures[tex_n]->width + tex_cords.col) * 4 + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

static t_cords_int	get_tex_cords(t_mlx_state *mlx_state, t_dda *dda, int tex_index)
{
	double		wall_x;
	t_cords_int	tex;

	if (dda->current_side == X_SIDE)
		wall_x = dda->player_pos.row + dda->perp_wall_dist * dda->ray_dir.row;
	else
		wall_x = dda->player_pos.col + dda->perp_wall_dist * dda->ray_dir.col;
	wall_x -= (floor(wall_x));
	tex.col = (int)(wall_x * mlx_state->textures[tex_index]->width);
	if (tex_index == S_INDEX || tex_index == W_INDEX)
		tex.col = mlx_state->textures[tex_index]->width - tex.col - 1;
	return (tex);
}

static void	fill_buffer_texture(t_mlx_state *mlx_state, t_dda *dda, int col, int tex_index)
{
	t_cords_int	tex_cord;
	double		step;
	double		tex_pos;
	int			row;

	tex_cord = get_tex_cords(mlx_state, dda, tex_index);
	step = 1.0 * (mlx_state->textures[tex_index]->height) / dda->line.heigth;
	tex_pos = 0;
	row = dda->line.start;
	while (row < 0)
	{
		tex_pos += step;
		row++;
	}
	while (row < SCR_HEIGHT && row <= dda->line.end)
	{
		tex_cord.row = ((int)tex_pos) & ((mlx_state->textures[tex_index]->height) - 1);
		tex_pos += step;
		mlx_state->img_buffer[row][col] = get_pixel_value(mlx_state, tex_cord, tex_index);
		row++;
	}
}

static int	get_tex_index(t_dda *dda)
{
	if (dda->current_side == X_SIDE && dda->ray_dir.col < 0)
		return (W_INDEX);
	else if (dda->current_side == X_SIDE && dda->ray_dir.col > 0)
		return (E_INDEX);
	else if (dda->current_side == Y_SIDE && dda->ray_dir.row < 0)
		return (N_INDEX);
	else
		return (S_INDEX);
}

void	textures(t_mlx_state *mlx_state, t_dda *dda, int col)
{
	int		tex_n;

	tex_n = get_tex_index(dda);
	fill_buffer_texture(mlx_state, dda, col, tex_n);
}
