#include "../include/cub3d.h"
#include "../include/engine.h"
#include <math.h>
#include <stdint.h>

#define PI 3.1415926535

static mlx_image_t *image;
static mlx_image_t *image1;

// hardcoded map voor tracer word vervangen door parser
int worldMap[MAPWIDTH][MAPHEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}};

float px, py, pdx, pdy, pa;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a) {
  return (r << 24 | g << 16 | b << 8 | a);
}

void draw_vierkant(int start_x, int start_y, int color[3], mlx_image_t *img,
                   int size) {
  int y = 0;
  while (y < size) {
    int x = 0;
    while (x < size) {
      mlx_put_pixel(img, start_x + x, start_y + y,
                    ft_pixel(color[0], color[1], color[2], 255));
      x++;
    }
    y++;
  }
}

void ft_hook(void *param) {
  mlx_t *mlx = param;

  if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
    mlx_close_window(mlx);
  if (mlx_is_key_down(mlx, MLX_KEY_UP)) {
    printf("Pijltje op\n");
    px += pdx;
    py += pdy;
    image1->instances[0].y -= 5;
  }
  if (mlx_is_key_down(mlx, MLX_KEY_DOWN)) {
    printf("Pijltje benede\n");
    px -= pdx;
    py -= pdy;
    image1->instances[0].y += 5;
  }
  if (mlx_is_key_down(mlx, MLX_KEY_LEFT)) {
    printf("Pijltje links\n");
    pa -= 0.1;
    if (pa < 0) {
      pa += 2 * PI;
    }
    pdx = cos(pa) * 5; // voor nu 5
    pdx = sin(pa) * 5; // voor nu 5

    image1->instances[0].x -= 5;
  }
  if (mlx_is_key_down(mlx, MLX_KEY_RIGHT)) {
    printf("Pijltje rechts\n");
    pa += 0.1;
    if (pa > 2 * PI) {
      pa -= 2 * PI;
    }
    pdx = cos(pa) * 5; // voor nu 5
    pdx = sin(pa) * 5; // voor nu 5
    image1->instances[0].x += 5;
  }
}

void draw_2d_map(void) {
  int color[3];
  color[0] = 255;
  color[1] = 255;
  color[2] = 255;
  int y = 0;
  int next_y = 0;
  while (y < MAPHEIGHT) {
    int x = 0;
    int next_x = 0;
    while (x < MAPWIDTH) {
      if (worldMap[y][x] == 1) {
        draw_vierkant(next_x, next_y, color, image, 64);
      }
      next_x += 64;
      x++;
    }
    next_y += 64;
    y++;
  }
}

void draw_player(void) {
  int color[3];
  color[0] = 125;
  color[1] = 225;
  color[2] = 125;
  int y = 0;
  while (y < 8) {
    int x = 0;
    while (x < 8) {
      draw_vierkant(px, py, color, image1, 8);
      x++;
    }
    y++;
  }
}

void init_state(void) {
  mlx_t *mlx;

  // Gotta error check this stuff
  if (!(mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "MLX42", true))) {
    puts(mlx_strerror(mlx_errno));
    return;
  }
  if (!(image = mlx_new_image(mlx, SCREENWIDTH, SCREENHEIGHT))) {
    mlx_close_window(mlx);
    puts(mlx_strerror(mlx_errno));
    return;
  }
  if (!(image1 = mlx_new_image(mlx, SCREENWIDTH, SCREENHEIGHT))) {
    mlx_close_window(mlx);
    puts(mlx_strerror(mlx_errno));
    return;
  }
  if (mlx_image_to_window(mlx, image, 0, 0) == -1) {
    mlx_close_window(mlx);
    puts(mlx_strerror(mlx_errno));
    return;
  }
  if (mlx_image_to_window(mlx, image1, 0, 0) == -1) {
    mlx_close_window(mlx);
    puts(mlx_strerror(mlx_errno));
    return;
  }

  mlx_loop_hook(mlx, ft_hook, mlx);

  // init background
  int y = 0;
  while (y < SCREENHEIGHT) {
    int x = 0;
    while (x < SCREENWIDTH) {
      mlx_put_pixel(image, x, y, ft_pixel(125, 125, 125, 255));
      x++;
    }
    y++;
  }

  px = 300;
  py = 300;
  draw_2d_map();
  draw_player();
  mlx_loop(mlx);
  mlx_terminate(mlx);
}
