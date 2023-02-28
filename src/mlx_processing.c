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

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

// get scaled x and y -> between 0 and 1.
// mask last 8 bytes.
// NOT WORKING
uint32_t	get_pixel(double x, double y, mlx_texture_t *texture)
{
	// printf("texture %p\n", texture);

	// printf("x %f, y %f\n", x, y);
	uint32_t ret;

	const uint32_t	scaled_x = (x * (double)texture->width);
	const uint32_t	scaled_y = (y * (double)texture->height);

	// printf("x = %u, y = %u\n", scaled_x, scaled_y);
	ret = texture->pixels[scaled_y * texture->width + scaled_x];
	// printf("%x\n", ((uint32_t *)texture->pixels)[scaled_y * texture->width + scaled_x]);
	return (((uint32_t *)texture->pixels)[scaled_y * texture->width + scaled_x]&0x111111FF);
}
