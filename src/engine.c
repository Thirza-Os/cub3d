#include "../include/engine.h"
#include "../include/cub3d.h"
#include <math.h>
#include <stdint.h>

static mlx_image_t* image;

// hardcoded map voor tracer word vervangen door parser
int worldMap[MAPWIDTH][MAPHEIGHT]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		printf("Pijltje op\n");
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		printf("Pijltje benede\n");
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		printf("Pijltje links\n");
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		printf("Pijltje rechts\n");
}


void	init_state(void)
{
	t_engine engine;
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return ;
	}
	if (!(image = mlx_new_image(mlx, SCREENWIDTH, SCREENHEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return ;
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return ;
	}

	mlx_loop_hook(mlx, ft_hook, mlx);


	engine.player.x = 22;
	engine.player.y = 12;
	engine.dir.x = -1;
	engine.dir.y = 0;
	engine.plane.x = 0.0;
	engine.plane.y = 0.66;
	engine.ray.y = 0.0;
	engine.ray.x = 0.0;
	engine.cur_time = 0.0;
	engine.prev_time = 0.0;

	// game loop vervangen door mlx42
	// ray len vanaf cur pos
	double ray_dist_x = 0.0;
	double ray_dist_y = 0.0;
	double wall_dist = 0.0;  // voor als we een muur tegen komen
	int step_x = 0;  // -1 of +1
	int step_y = 0;  // -1 of +1
	double timer = 5;

	// init window met stuff...
	int w = 0;
	while (w < SCREENWIDTH)
	{
		int h = 0;
		while (h < SCREENHEIGHT)
		{
			uint32_t color = ft_pixel(255, 255, 100, 255);
			mlx_put_pixel(image, w, h, color);
			h++;
		}
		w++;
	}

	while (true)
	{
		// loop over alle breedte  eerste run heeft NaN waarom??
		int index = 0;
		while (index < MAPWIDTH)
		{
			double	camera_x = 2 * index / (double)index - 1;
			engine.ray.x = engine.dir.x + engine.plane.x * camera_x;
			engine.ray.y = engine.dir.y + engine.plane.y * camera_x;
			printf("%f, %f\n", engine.ray.x, engine.ray.y);

			// de box waar we nu in zijn
			int map_x = (int)engine.player.x;
			int map_y = (int)engine.player.y;

			// ray len vanaf x/y tot volgende x/y
			double delta_dist_x = INFINITY;
			if (engine.ray.x != 0.0)
				delta_dist_x = fabs(1 / engine.ray.x);
			double delta_dist_y = INFINITY;
			if (engine.ray.y != 0.0)
				delta_dist_y = fabs(1 / engine.ray.y);


			bool hit = false;
			int hit_side = 0;  // welke we de muur raken??

			if (engine.ray.x < 0)
			{
				step_x = -1;
				ray_dist_x = (engine.player.x - map_x) * delta_dist_x;
			}
			else
			{
				step_x = 1;
				ray_dist_x = (map_x + 1.0 - engine.player.x) * delta_dist_x;
			}

			if (engine.ray.y < 0)
			{
				step_y = -1;
				ray_dist_y = (engine.player.y - map_y) * delta_dist_y;
			}
			else
			{
				step_y = 1;
				ray_dist_y = (map_y + 1.0 - engine.player.y) * delta_dist_y;
			}

			// DDA
			while (hit == false)
			{
				if (ray_dist_x < ray_dist_y)
				{
					ray_dist_x += delta_dist_x;
					map_x += step_x;
					hit_side = 0;
				}
				else
				{
					ray_dist_y += delta_dist_y;
					map_y += step_y;
					hit_side = 1;
				}

				if (worldMap[map_x][map_y] > 0)
				{
					printf("We did hit a wall at: %d, %d\n", map_x, map_y);
					hit = true;
				}
			}

			if (hit_side == 0)
			{
				wall_dist = ray_dist_x - delta_dist_x;
			}
			else
			{
				wall_dist = ray_dist_y - delta_dist_y;
			}
			printf("Wall dist: %f\n", wall_dist);

			int line_heigth = (int)(SCREENHEIGHT / wall_dist);
			int draw_start = -line_heigth / 2 + SCREENHEIGHT / 2;
			if (draw_start < 0)
				draw_start = 0;
			int draw_end = line_heigth / 2 + SCREENHEIGHT / 2;
			if (draw_end >= SCREENHEIGHT)
				draw_end = SCREENHEIGHT - 1;
			printf("line_heigth: %d, draw_start: %d draw_end: %d\n", line_heigth, draw_start, draw_end);


			// store time zodat we een const move hebben
			timer += 0.05;
			engine.prev_time = engine.cur_time;
			double frame_time = (timer - engine.prev_time) / 1000.0;  // timer vervangen voor mlx versie
			engine.cur_time = timer;  // vervangen voor time MLX
			double move_speed = frame_time * 5.0;
			double rot_speed = frame_time * 3.0;

			printf("FPS: %f\n", 1.0 / frame_time);
			printf("move_speed: %f\n", move_speed);
			printf("rot_speed: %f\n", rot_speed);



			index++;
		}
		break;
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
