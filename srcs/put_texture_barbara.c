unsigned int    get_texture(t_image *text)
{
    int                res;
    int                tex_i;
    unsigned char    r;
    unsigned char    g;
    unsigned char    b;
/* use offset_y and offset_x to find the good pixel in the texture. You have calculated these variables in "get_hor_texture_color" and "get_vert_texture_color" functions*/
    tex_i = text->offset_y * text->line_length + text->offset_x \
            * (text->bits_per_pixel / 8);
    r = (unsigned char)(text->addr)[tex_i + 2];
    g = (unsigned char)(text->addr)[tex_i + 1];
    b = (unsigned char)(text->addr)[tex_i];
    res = ((int)r << 16) + ((int)g << 8) + (int)b;
    return (res);
}

unsigned int    choose_color(t_ray *r, double y)
{
    unsigned int    color;

    if (r->is_hor_hit)
        get_hor_texture_color(r, y);
    else if (r->is_vert_hit)
        get_vert_texture_color(r, y);
    color = get_texture(r->text);
    return (color);
}

void    get_hor_texture_color(t_ray *r, double y)
{
    t_image    *tex;

    tex = r->text;
    tex->offset_y = (y * tex->icon_h) / floor(r->wall_height);
    if (tex->offset_y > tex->icon_h)
        tex->offset_y = tex->icon_h - 1;
    tex->offset_x = r->end.x % TILES_S;
    if (r->is_ray_down)
        tex->offset_x = TILES_S - tex->offset_x;
    tex->offset_x = (tex->offset_x * tex->icon_w) / TILES_S;
    if (tex->offset_x > tex->icon_w)
        tex->offset_x = tex->icon_w - 1;
}

void    get_vert_texture_color(t_ray *r, double top_pxl)
{
    t_image    *tex;

    tex = r->text;
    tex->offset_y = (top_pxl * tex->icon_h) / floor(r->wall_height);
    if (tex->offset_y >= tex->icon_w)
        tex->offset_y = tex->icon_w - 1;
    tex->offset_x = r->end.y % TILES_S;
    if (r->is_ray_left)
        tex->offset_x = TILES_S - tex->offset_x;
    tex->offset_x = (tex->offset_x * tex->icon_h) / TILES_S;
    if (tex->offset_x > tex->icon_w)
        tex->offset_x = tex->icon_w - 1;
}
 
void    draw_strips(t_player *p, int x, double top_pxl)
{
    double    y;
    int        next;
    double    tmp_top_pxl;

    y = 0;
    next = x + WALL_STRIP_L;
    tmp_top_pxl = top_pxl;
    while (x < next)
    {
        y = 0;
        top_pxl = tmp_top_pxl + y;
        while (top_pxl < 0)
            top_pxl = tmp_top_pxl + y++;
        while (top_pxl < WIN_H)
        {
            my_mlx_pixel_put(p->cub->image, x, top_pxl, choose_color(&p->r[x],
                    y));
            y += 1;
            top_pxl = tmp_top_pxl + y;
            if (y > p->r[x].wall_height)
                break ;
        }
        x++;
    }
}