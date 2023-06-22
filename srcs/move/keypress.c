/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:29:30 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/21 13:46:45 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_keypress(int keysym, t_data *data)
{
	
	if (keysym == K_W) {
    	data->player.walkDirection = -1;
    } else if (keysym == K_S) {
    	data->player.walkDirection = +1;
    } else if (keysym == K_AR_R) {
    	data->player.turnDirection = +1;
    } else if (keysym == K_AR_L) {
    	data->player.turnDirection = -1;
    } else if (keysym == K_D) {
    	data->player.walkDirection = -3;
    } else if (keysym == K_A) {
    	data->player.walkDirection = +3;
	}
	if (keysym == K_ESC)
		exit_game(data);
	//printf("Keypress: %d\n", keysym);
	updata(data);
	draw_window(data);
	return (0);
}

int	handle_keyrelease(int keysym, t_data *data)
{
    if (keysym == K_W) {
    	data->player.walkDirection = 0;
    } else if (keysym == K_S) {
    	data->player.walkDirection = 0;
    } else if (keysym == K_AR_R) {
    	data->player.turnDirection = 0;
    } else if (keysym == K_AR_L) {
    	data->player.turnDirection = 0;
    }
	//printf("Keyrelease: %d\n", keysym);
	return (0);
}



void	updata(t_data *data)
{
	t_player	*player;
	int			movestep;
	double		newPlayerX;
	double		newPlayerY;

	player = &data->player;
	player->rotationAngle += (player->turnDirection * player->rotationSpeed);
	movestep = (player->walkDirection  % 2) * player->moveSpeed;
	newPlayerX = player->pos_x + cos(player->rotationAngle) * movestep;
	newPlayerY = player->pos_y + sin(player->rotationAngle) * movestep;
	if (abs(player->walkDirection) == 3)
	{
		newPlayerX = player->pos_x + cos(player->rotationAngle + PI / 2) * movestep;
		newPlayerY = player->pos_y + sin(player->rotationAngle + PI / 2) * movestep;	
	}
	if(!hasWallAt(data, newPlayerX, newPlayerY))
	{
		player->pos_x = newPlayerX;
		player->pos_y = newPlayerY;
	}
}

int	hasWallAt(t_data *data, double x, double y)
{
	int	mapGridIndexX;
	int	mapGridIndexY;

	mapGridIndexX = 0;
	mapGridIndexY = 0;
	if (x < 0 || x > (data->map.width * TILE_SIZE) || y < 0 || y > (data->map.height * TILE_SIZE))
    	return (1);
	mapGridIndexX = floor(x / TILE_SIZE);
	mapGridIndexY = floor(y / TILE_SIZE);
	if (data->map.map[mapGridIndexY][mapGridIndexX] == '1')
		return (1);
	return (0);
}