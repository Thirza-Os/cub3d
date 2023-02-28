#include "cub3d.h"

void	parser(char *argv[])
{
	char		**elements;
	t_program	program;

	check_cub(argv[1]);
	elements = tokenize_input(argv[1]);
	validate_nr_of_identifiers(elements);
	validate_structure_paths(elements, &program);
	validate_rgb_input(elements, &program);
	validate_map(elements[SIZE], &program);
	extract_mlx_pixels(&program);


	uint32_t x;
	uint32_t y;
	mlx_t *mlx;
	mlx = mlx_init(1000, 1000, "TESTING", true);
	mlx_image_t* img = mlx_new_image(mlx, 1000, 1000);
	mlx_image_to_window(mlx, img, 0, 0);
	x = 0;
	printf("texture %p\n", program.mlx_textures[WE]);
	while(x < 1000)
	{
		y = 0;
		while (y < 1000)
		{
			mlx_put_pixel(img, x, y, get_pixel((double)x / 1000, (double)y / 1000, program.mlx_textures[WE]));
			y++;
		}
		x++;
	}
	mlx_loop(mlx);
}
