#include "cub3d.h"

void	extract_mlx_pixels(t_program *program)
{
	unsigned int	i;

	i = 0;
	while (i < 4)
	{
		program->mlx_textures[i] = mlx_load_png(program->textures[i]);
		i++;
	}
}

int	get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	get_pixel(double x, double y, mlx_texture_t *texture)
{

	uint32_t res;
	uint8_t *image_pos;

	const uint32_t	scaled_x = (x / ((double)texture->width));
	const uint32_t	scaled_y = (y / ((double)texture->height));
	//if (scaled_y >= texture->height || scaled_y <= 0)
	//{
	//	return (0);
	//}
	image_pos = &texture->pixels[(scaled_y * texture->width + scaled_x) * texture->bytes_per_pixel];

	((uint8_t *)(&res))[0] = image_pos[3];
	((uint8_t *)(&res))[1] = image_pos[2];
	((uint8_t *)(&res))[2] = image_pos[1];
	((uint8_t *)(&res))[3] = image_pos[0];

	return (res);
}
