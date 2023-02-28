#include "cub3d.h"

void	extract_mlx_pixels(t_program program)
{
	unsigned int	i;

	i = 0;
	while (i < 4)
	{
		program.mlx_textures[i] = mlx_load_png(program.textures[i]);
		i++;
	}
}

// get scaled x and y -> between 0 and 1.
uint32_t	get_pixel(double x, double y, mlx_texture_t *texture)
{
	const uint32_t	scaled_x = x * (double)texture->width;
	const uint32_t	scaled_y = y * (double)texture->height;

	return (texture->pixels[scaled_y * texture->width + scaled_x]);
}
