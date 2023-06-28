/*void	draw_pixel(t_data *data, t_pixel p, int option)
{
	int		size;
	int		window_width;
	int		window_height;
	t_img	*img;

	if (option == WINDOW)
	{
		window_width = SCWIDTH;
		window_height = SCHEIGHT;
		img = data->img.img;
	}
	else
	{
		window_width = (data->map.width * TILE_SIZE);
		window_height = (data->map.height * TILE_SIZE);
		img = data->minimap.m_map.img;
	}
	size = window_width * img->ratio;
	if ((p.x >= 0 && p.x < window_width * img->ratio) && \
			(p.y >= 0 && p.y < window_height * img->ratio))
		img->addr[p.x + size * p.y] = p.color;
}

/*unsigned int	get_color(t_data *data, double x, double y)
{
	unsigned int	color_index;
	unsigned int	color;
	double	ratio = data->texture[data->ray.side].img_height / data->ray.wallStripHeight;
	unsigned int		tex_start;
	
	if (data->ray.side == 2 || data->ray.side == 3)
		tex_start = (int)round(data->ray.ray_x) % TILE_SIZE + x * ratio;
	else
		tex_start = (int)round(data->ray.ray_y) % TILE_SIZE + x * ratio;
		
	if (tex_start < (unsigned int)data->texture[data->ray.side].img_width && (y * ratio) < (unsigned int)data->texture[data->ray.side].img_height)
		//color_index = (tex_start * data->texture[data->ray.side].line_size) +  (y * ratio) * (data->texture[data->ray.side].bits_per_pixel / 8);
		color_index = ((y * ratio)* data->texture[data->ray.side].line_size) +  tex_start * (data->texture[data->ray.side].bits_per_pixel / 8);
	else
		//color_index= (tex_start - 1) * data->texture[data->ray.side].line_size +  y * ratio * (data->texture[data->ray.side].bits_per_pixel / 8);
		color_index= (y * ratio) * data->texture[data->ray.side].line_size +  (tex_start - 1) * (data->texture[data->ray.side].bits_per_pixel / 8);
	color = get_texture(data, color_index);
	return (color);
}

void	render3DProjectWall(t_data *data)
{
	int	color;
	double	y;
	double	x;
	
	data->ray.correctionWallDistance = data->ray.ray_distance * cos(data->ray.ray_angle - data->player.rotationAngle);
    data->ray.distanceProjectionPlane = (SCWIDTH / 2) / tan(FOV_ANGLE / 2);
    data->ray.wallStripHeight  = (TILE_SIZE / data->ray.correctionWallDistance) * data->ray.distanceProjectionPlane;
	data->ray.draw_start_y = (SCHEIGHT / 2) - (data->ray.wallStripHeight / 2);
	
	data->ray.draw_start_x = data->ray.ray_id * Wall_STRIP_WIDTH;
	x = 0;
	while (data->ray.draw_start_x <= (data->ray.ray_id * Wall_STRIP_WIDTH + Wall_STRIP_WIDTH))
	{
		y = 0;
		data->ray.draw_start_y = (SCHEIGHT / 2) - (data->ray.wallStripHeight / 2) + y;
		while (data->ray.draw_start_y < 0)
			data->ray.draw_start_y = SCHEIGHT / 2 - (data->ray.wallStripHeight / 2) + y++;
		while (data->ray.draw_start_y < SCHEIGHT)
		{
			// draw_pixel(data, init_pixel(data->ray.draw_start_x, data->ray.draw_start_y, get_color(data, data->ray.draw_start_x, data->ray.draw_start_y)), WINDOW);
			color = get_color(data, x, y);
			ft_my_mlx_pixel_put(&data->img, (int)data->ray.draw_start_y, (int)data->ray.draw_start_x, color);
			y += 1;
			data->ray.draw_start_y = (SCHEIGHT / 2) - (data->ray.wallStripHeight / 2) + y;
			if (y >= data->ray.wallStripHeight)
				break ;
		}
		x++;
		data->ray.draw_start_x = data->ray.draw_start_x + x;
	}
} */ 