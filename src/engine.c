#include "../include/engine.h"
#include "../include/cub3d.h"
#include <math.h>

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


void	init_state(void)
{
	t_engine engine;

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
	while (true)
	{
		// loop over alle breedte
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

			(void)hit_side;
			(void)wall_dist;










			index++;
		}
		break;
	}
}
