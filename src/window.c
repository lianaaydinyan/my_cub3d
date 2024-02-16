/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:08:06 by marihovh          #+#    #+#             */
/*   Updated: 2024/02/12 13:15:54 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../minilibx-linux/mlx.h"


void draw_colors(t_data *data);


int init_win(t_data *data)
{
    data->win_w = 640;
    data->win_h = 480;
    data->cam_x = 0;
    data->cam_y = 0.66;
    data->dir_x = -1;
    data->dir_y = 0;
    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_w,
                                   data->win_h, "Cub3d");
    return (0);
}

void draw_colors(t_data *data)
{
    int x = 0, y = 0;
    while (y < data->win_h / 2) {
        x = 0;
        while (x < data->win_w) {
            my_mlx_pixel_put(data, x, y, data->game->celling_c);
            x++;
        }
        y++;
    }
    y = data->win_h / 2;
    while (y < data->win_h) {
        x = 0;
        while (x < data->win_w) {
            my_mlx_pixel_put(data, x, y, data->game->flooring_c);
            x++;
        }
        y++;
    }
}



void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && y > 0 && data->win_w > x && data->win_h > y)
	{
		dst = data->imgg->addr + (y * data->imgg->line_length + x
				* (data->imgg->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}




int do_walls(t_data *data)
{	
	(void)data;
		//raycasting
	return (0);
}
void coloring(t_data *data)
{

    int x = 0, y = 0;
    while (y < data->win_h / 2) {
        x = 0;
        while (x < data->win_w) {
            my_mlx_pixel_put(data, x, y, data->game->celling_c);
            x++;
        }
        y++;
    }
    y = data->win_h / 2;
    while (y < data->win_h) {
        x = 0;
        while (x < data->win_w) {
            my_mlx_pixel_put(data, x, y, data->game->flooring_c);
            x++;
        }
        y++;
    }
}



int just_do_it(t_data *data)
{


    data->imgg = malloc(sizeof(t_img)); 
	// char *path = "/Users/liaydiny/Desktop/my_cub3d/textures/path_to_the_north_texture.xpm";
    
    // int width;
    // int heigth;
    // coloring(data);
	data->imgg->img = mlx_new_image(data->mlx_ptr, data->win_w, data->win_h);
	data->imgg->addr = mlx_get_data_addr(data->imgg->img, &data->imgg->bits_per_pixel,
			&data->imgg->line_length, &data->imgg->endian);

    data->game = malloc(sizeof(t_game));
	data->game->celling_c = 0x87CEEB;
    data->game->flooring_c = 0x0b701a; 
    draw_colors(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->imgg->img, 0, 0);
	return (0);
}