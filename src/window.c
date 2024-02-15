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

int init_win(t_data *data)
{
	data->win_w = 1200;
	data->win_h = 800;
	data->cam_x = 0;
	data->cam_y = 0.66;
	data->dir_x = -1;
	data->dir_y = 0;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_w,
			data->win_h, "Cub3d");
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && y > 0 && data->win_w > x && data->win_h > y)
	{
		dst = data->imgg.addr + (y * data->imgg.line_length + x
				* (data->imgg.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}


int do_walls(t_data *data)
{	
	//raycasting
	return (0);
}

int just_do_it(t_data *data)
{


	char *path = "/Users/liaydiny/Desktop/cub3d/textures/path_to_the_north_texture.xpm";
	data->imgg.img = mlx_new_image(data->mlx_ptr, data->win_w, data->win_h);
	data->imgg.addr = mlx_get_data_addr(data->imgg.img, &data->imgg.bits_per_pixel,
			&data->imgg.line_length, &data->imgg.endian);
	data->imgg.img = mlx_xpm_file_to_image(data->mlx_ptr, path, &data->win_w, &data->win_h);

	
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->imgg.img, 250, 250);
	return (0);
}