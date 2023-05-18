/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:15:09 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/17 15:15:12 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define WIN_WIDTH 230
#define WIN_HEIGHT 200
#define POINT_DIAMETER 50

typedef struct	s_tata
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_tata;

int		close_window(t_tata *tata)
{
	mlx_destroy_window(tata->mlx_ptr, tata->win_ptr);
	exit(0);
}

void	draw_circle(t_tata *tata, int center_x, int center_y, int diameter, int color)
{
	int radius = diameter / 2;
	int x, y;

	x = center_x - radius;
	while (x <= center_x + radius)
	{
		y = center_y - radius;
		while (y <= center_y + radius)
		{
			mlx_pixel_put(tata->mlx_ptr, tata->win_ptr, x, y, color);
			y++;
		}
		x++;
	}
}

int		main(void)
{
	t_tata	tata;
	int		win_mid_x;
	int		win_mid_y;

	tata.mlx_ptr = mlx_init();
	tata.win_ptr = mlx_new_window(tata.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Red Point");

	win_mid_x = WIN_WIDTH / 2;
	win_mid_y = WIN_HEIGHT / 2;

	draw_circle(&tata, win_mid_x, win_mid_y, POINT_DIAMETER, 0xFF0000); // Red color

	mlx_hook(tata.win_ptr, 17, 0L, close_window, &tata);
	mlx_loop(tata.mlx_ptr);
	return (0);
}