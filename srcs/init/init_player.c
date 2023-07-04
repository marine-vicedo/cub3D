/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:35:47 by mvicedo           #+#    #+#             */
/*   Updated: 2023/07/04 14:55:19 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_player(t_data *data)
{
	t_player	*player;

	player = &data->player;
	player->turn_dir = 0;
	player->walk_dir = 0;
}

void	init_new_position(t_data *data)
{
	t_player	*player;

	player = &data->player;
	player->turn_dir = 0;
	player->walk_dir = 0;
}
