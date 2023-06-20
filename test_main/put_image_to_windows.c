#include "mlx.h"

#define WIN_WIDTH 960
#define WIN_HEIGHT 600
#define IMG_WIDTH 64
#define IMG_HEIGHT 64
#define START_X 25
#define END_X 250
#define START_Y 5
#define END_Y 50

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
}				t_data;

void put_image_to_window(t_data *data, int start_x, int end_x, int start_y, int end_y, int img_width, int img_height, unsigned int *image_data)
{
	int x, y;
	int win_width = end_x - start_x + 1;
	int win_height = end_y - start_y + 1;

	for (y = 0; y < img_height; y++)
	{
		for (x = 0; x < img_width; x++)
		{
			int win_x = start_x + x;
			int win_y = start_y + y;

			int img_index = y * img_width + x;
			int win_index = win_y * win_width + win_x;

			// Copy pixel from the image to the window's image buffer
			((unsigned int*)data->addr)[win_index] = image_data[img_index];
		}
	}
}

int main()
{
	t_data data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Window");
	data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_size, &data.endian);

	// Load your image and convert it to a suitable format (e.g., RGBA)
	unsigned int image_data[IMG_WIDTH * IMG_HEIGHT] = { /* Image pixel data here */ };

	// Put the image in the window
	put_image_to_window(&data, START_X, END_X, START_Y, END_Y, IMG_WIDTH, IMG_HEIGHT, image_data);

	// Display the image
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	mlx_loop(data.mlx);

	return 0;
}