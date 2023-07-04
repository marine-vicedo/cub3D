/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:29:30 by pmaimait          #+#    #+#             */
/*   Updated: 2023/07/04 15:02:04 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == K_W)
		data->player.walk_dir = -1;
	else if (keysym == K_S)
		data->player.walk_dir = +1;
	else if (keysym == K_AR_R)
		data->player.turn_dir = +1;
	else if (keysym == K_AR_L)
		data->player.turn_dir = -1;
	else if (keysym == K_D)
		data->player.walk_dir = -3;
	else if (keysym == K_A)
		data->player.walk_dir = +3;
	if (keysym == K_ESC)
		exit_game(data);
	update(data);
	draw_window(data);
	return (0);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == K_W)
		data->player.walk_dir = 0;
	else if (keysym == K_S)
		data->player.walk_dir = 0;
	else if (keysym == K_AR_R)
		data->player.turn_dir = 0;
	else if (keysym == K_AR_L)
		data->player.turn_dir = 0;
	return (0);
}

void	update(t_data *data)
{
	t_player	*p;
	int			movestep;
	double		new_p_x;
	double		new_p_y;

	p = &data->player;
	p->rotate_angle += (p->turn_dir * rotationSpeed);
	movestep = (p->walk_dir % 2) * moveSpeed;
	new_p_x = p->pos_x + cos(p->rotate_angle) * movestep;
	new_p_y = p->pos_y + sin(p->rotate_angle) * movestep;
	if (abs(p->walk_dir) == 3)
	{
		new_p_x = p->pos_x + cos(p->rotate_angle + PI / 2) * movestep;
		new_p_y = p->pos_y + sin(p->rotate_angle + PI / 2) * movestep;
	}
	if (!has_wall_at(data, new_p_x, new_p_y))
	{
		p->pos_x = new_p_x;
		p->pos_y = new_p_y;
	}
}

int	has_wall_at(t_data *data, double x, double y)
{
	int	map_grid_x;
	int	map_grid_y;

	map_grid_x = 0;
	map_grid_y = 0;
	if (x < 0 || x > (data->map.width * TILE_SIZE) || y < 0
		|| y > (data->map.height * TILE_SIZE))
		return (1);
	map_grid_x = floor(x / TILE_SIZE);
	map_grid_y = floor(y / TILE_SIZE);
	if (data->map.map[map_grid_y][map_grid_x] == '1')
		return (1);
	return (0);
}
