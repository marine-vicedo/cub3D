/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:29:33 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/03 12:35:01 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"


#define WIDTH 640
#define HEIGHT 480
#define FOV 60
#define WALL_HEIGHT 64

typedef struct s_player
{
    double x;
    double y;
    double angle;
} t_player;

typedef struct s_ray
{
    double x;
    double y;
    double distance;
    double angle;
    int hit;
    int wall_height;
} t_ray;

void draw_ray(t_ray *ray, t_player *player, void *mlx, void *win)
{
    int wall_color = 0xCCCCCC;
    double ray_height = (WALL_HEIGHT / ray->distance) * ((WIDTH / 2) / tan((FOV / 2) * M_PI / 180));
    double wall_top = (HEIGHT / 2) - ray_height / 2;
    double wall_bottom = (HEIGHT / 2) + ray_height / 2;
    double wall_x = ray->hit ? (int)ray->x % 64 : 0;

    mlx_pixel_put(mlx, win, player->x, player->y, ray->x, ray->y, wall_color);
    mlx_line_put(mlx, win, ray->distance, wall_top, 1, ray_height, wall_color);
}

void render(t_player *player, void *mlx, void *win)
{
    int i;
    double angle;
    t_ray ray;

    angle = player->angle - FOV / 2;
    i = 0;
    while (i < WIDTH)
    {
        ray.angle = angle;
        ray.x = player->x;
        ray.y = player->y;
        ray.hit = 0;

        while (!ray.hit)
        {
            ray.x += cos(ray.angle * M_PI / 180);
            ray.y += sin(ray.angle * M_PI / 180);
            if (ray.x < 0 || ray.y < 0 || ray.x >= WIDTH || ray.y >= HEIGHT)
                break;
            // Check for wall collision
            // ...

        }

        ray.distance = sqrt(pow(player->x - ray.x, 2) + pow(player->y - ray.y, 2));
        ray.wall_height = WALL_HEIGHT;
        draw_ray(&ray, player, mlx, win);

        angle += FOV / WIDTH;
        i++;
    }
}

int main()
{
    void *mlx;
    void *win;
    t_player player;

    player.x = WIDTH / 2;
    player.y = HEIGHT / 2;
    player.angle = 0;

    mlx = mlx_init();
    win = mlx_new_window(mlx, WIDTH, HEIGHT, "Raycasting Example");

    while (1)
    {
        // Handle player movement and rotation
        // ...

        mlx_clear_window(mlx, win);
        render(&player, mlx, win);
        //mlx_flush_event(mlx);
    }

    mlx_loop(mlx);
    return (0);
}