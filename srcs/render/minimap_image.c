/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:28:30 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/09 15:38:15 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

void    render_minimap(t_data *data)
{
    t_minimap   *minimap;
    
    minimap = &data->minimap;
	minimap->view_dist = MMAP_VIEW_DIST;
	minimap->size = (2 * minimap->view_dist) + 1;
	minimap->tile_size = MMAP_PIXEL_SIZE / (2 * minimap->view_dist);
    
}

