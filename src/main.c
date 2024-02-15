/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:27:26 by marihovh          #+#    #+#             */
/*   Updated: 2024/02/10 18:01:37 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	errorik(int flag)
{
	if (flag == M_ERROR)
		ft_putstr_fd("Error: map\n", 2);
	else if (flag == F_ERROR)
		ft_putstr_fd("Error: wrong format of map\n", 2);
	else if (flag == T_ERROR)
		ft_putstr_fd("Error: some trouble with textures\n", 2);
	else if (flag == C_ERROR)
		ft_putstr_fd("Error: some trouble with colors\n", 2);
	else if (flag == E_ERROR)
		ft_putstr_fd("Error: something is missing\n", 2);
	else
		ft_putstr_fd("Error\n", 2);
	return (1);
}


void	texture_data_filling(t_data *data)
{
	data->textures = malloc(sizeof(char *) * 5);
	data->textures[north] = NULL;
	data->textures[south] = NULL;
	data->textures[west] = NULL;
	data->textures[east] = NULL;
}

void	hero_data_filling(t_data *data)
{
	data->hero->pos_x = 22.0;
	data->hero->pos_y = 11.5;
	data->hero->dir_x = -1.0;
	data->hero->dir_y = 0.0;
	data->hero->plane_x = 0.0;
	data->hero->plane_y = 0.66;
	data->hero->move_speed = 0; // for just initializing
	data->hero->rot_speed = 0; // for just initializing
}

void	ft_dda_algorithm(t_data *data)
{
	while (data->ray->hit == 0)
	{
		if (data->ray->side_dist_x < data->ray->side_dist_y)
		{
			data->ray->side_dist_x += data->ray->delta_dist_x;
			data->ray->map_x +=data->ray->step_x;
			data->ray->side = 0;
		}
		else
		{
			data->ray->side_dist_y += data->ray->delta_dist_y;
			data->ray->map_y +=data->ray->step_y;
			data->ray->side = 0;
		}
		if (data->map[data->ray->map_x][data->ray->map_y] > 0)
		{
			data->ray->hit = 1;
		}
	}
}

void	calculate_step_init_side_dist(t_data *data)
{
		//for x cordinate
		if (data->ray->ray_dir_x < 0)
		{
			data->ray->step_x = -1;
			data->ray->side_dist_x = (data->pos_x - data->ray->map_x) * data->ray->delta_dist_x;
		}
		else
		{
			data->ray->step_x = 1;
			data->ray->side_dist_x = (data->ray->map_x + 1.0 - data->pos_x) * data->ray->delta_dist_x;
		}
		//for y cordinate
		if (data->ray->ray_dir_y< 0)
		{
			data->ray->step_y = -1;
			data->ray->side_dist_y = (data->pos_y - data->ray->map_y) * data->ray->delta_dist_y;
		}
		else
		{
			data->ray->step_y = 1;
			data->ray->side_dist_y = (data->ray->map_y + 1.0 - data->pos_y) * data->ray->delta_dist_y;
		}
}

void	ft_texture_calculation(t_data	*data)
{
	//texturing calculations
	data->tex_num = data->map[data->ray->map_x][data->ray->map_y] - 1;//1 subtracted from it so that texture 0 can be used!
	if (data->ray->side == 0)
		data->ray->wall_x = data->hero->pos_y + data->ray->perp_wall_dist * data->ray->ray_dir_y;
	else
		data->ray->wall_x = data->hero->pos_y + data->ray->perp_wall_dist * data->ray->ray_dir_x;
	data->ray->wall_x -= floor(data->ray->wall_x);

	//x coordinate on the texture
	data->ray->tex_x = (int)(data->ray->wall_x * (double)texWidth);
	if (data->ray->side == 0 && data->ray->ray_dir_x > 0)
		data->ray->tex_x = texWidth - data->ray->tex_x - 1;
	if (data->ray->side == 0 && data->ray->ray_dir_y < 0)
		data->ray->tex_x = texWidth - data->ray->tex_x - 1;
	// TODO
	
}

void	counting_ray_from_side_to_next(t_data *data)
{
	//length of ray from one x or y-side to next x or y-side
	if (!(data->ray->ray_dir_x))
		data->ray->delta_dist_x = 1e30;
	else
		data->ray->delta_dist_x = abc(1 / data->ray->ray_dir_x);
	if (!(data->ray->ray_dir_y))
		data->ray->delta_dist_y = 1e30;
	else
		data->ray->delta_dist_y = abc(1 / data->ray->ray_dir_y);
	data->ray->pitch = 100;
	//calculate lowest and highest pixel to fill in current stripe
	data->imgg.start = -data->ray->line_height / 2 + data->height / 2 + data->ray->pitch;
	if (data->imgg.start < 0)
		data->imgg.start = 0;
	data->imgg.end = data->ray->line_height / 2 + data->height / 2 + data->ray->pitch;
	if (data->imgg.end >= data->height)
		data->imgg.end = data->height - 1;
	//texturing calculation
	ft_texture_calculation(data);
}


void	ray_filling_part2(t_data *data)
{
	if (data->ray->side == 0)
		data->ray->perp_wall_dist = (data->ray->side_dist_x - data->ray->delta_dist_x);
	else
		data->ray->perp_wall_dist = (data->ray->side_dist_y - data->ray->delta_dist_y);
	data->ray->line_height = (int)(data->height / data->ray->perp_wall_dist);

}

void	ray_data_filling(t_data *data)
{
	int i;

	i = 0;
	while (i < data->widht)
	{
		//calculate ray position and direction
		data->ray->camera_x = 2 * i / (data->widht - 1);
		data->ray->ray_dir_x = data->dir_x + data->cam_x * data->ray->camera_x;
		data->ray->ray_dir_y = data->dir_y + data->cam_y * data->ray->camera_x;
		//which box of the map we're in
		data->ray->map_x = (int)data->pos_x;
		data->ray->map_y = (int)data->pos_y;
		counting_ray_from_side_to_next(data);
		//hiting wall or not
		data->ray->hit = 0;
		//calculate step and initial sideDist
		calculate_step_init_side_dist(data);
 		//perform DDA
		ft_dda_algorithm(data);
		ray_filling_part2(data);
		i++;
	}
}

void	ft_filling(t_data *data)
{
	data->count = 0;
	data->nb = 0;
	data->to_map = 0;
	texture_data_filling(data);
	hero_data_filling(data);
	ray_data_filling(data);
	game_data_filling(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	ft_filling(data);

	if (argc == 2)
	{
		if (parcing(data, argv))
			return (1);
		if (init_win(data))
			return (1);
		if (just_do_it(data))
			return (1);
		mlx_hook(data->win_ptr, 2, 0, key_hook, data);
		mlx_hook(data->win_ptr, 17, (1L << 17), key_cross, data);
		mlx_loop(data->mlx_ptr);
	}
	else
		return (errorik(42));
	return (0);
}












































// #include <stdio.h>
// int main() {
//     void *mlx;
//     void *win;

//    int img_height;

//     mlx = mlx_init();
//     if (!mlx) {
//         fprintf(stderr, "Failed to initialize Minilibx.\n");
//         return 1;
//     }

//     win = mlx_new_window(mlx, 1000, 1000, "my_mlx");
//     if (!win) {
//         fprintf(stderr, "Failed to create window.\n");
//         return 1;
//     }

//     t_img *img = malloc(sizeof(t_img)); 
//     if (!img) {
//         fprintf(stderr, "Failed to allocate memory for image struct.\n");
//         return 1;
//     }

//     img->img = mlx_new_image(mlx ,1000,1000);
//     img->addr = mlx_get_data_addr(img->img ,&img->bits_per_pixel,
//             &img->line_length, &img->endian );
//     if (!img->img) {
//         fprintf(stderr, "Failed to create image.\n");
//         free(img); 
//         return 1;
//     }

//     img->img = mlx_xpm_file_to_image(mlx, "/Users/liaydiny/Desktop/cub3d/textures/path_to_the_north_texture.xpm", &img_width, &img_height);
//     if (!img->img) {
//         fprintf(stderr, "Failed to load image.\n");
//         mlx_destroy_image(mlx, img->img); 
//         free(img);
//         return 1;
//     }
//     mlx_put_image_to_window(mlx, win, img->img, 500, 500);
//     mlx_loop(mlx);

//     free(img);

//     return 0;
// }
  int img_width;
//    