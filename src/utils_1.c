#include "../cub3d.h"

int any_invalid(char **line, int i, int j)
{
	if ((*line[0] == '\n' && j != 2) || i == 0)
		return (1);
	if (*line[0] == ',' && j == 2)
		return (1);
	if (*line[0] == ',' &&  j != 2)
	{
		(*line)++;
		skip_sp(line);
		if (*line[0] == '\n')
			return (1);
	}
	return (0);
}

int	key_hook(int keycode, t_data *data, t_img img)
{
	(void)img;
	int	i;

	i = 0;
	if (keycode == 53)
	{
		ft_putstr_fd ("The session is over!\n", 1);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		// while (i < data->height)
		// 	free(data->z_map[i++]);
		// free(data->z_map);
		free(data);
		exit(0);
	}
	// key_if(keycode, data);
	// mlx_clear_window(data->mlx_ptr, data->win_ptr);
	// draw_map(data);
	return (0);
}

int	key_cross(t_data *data, int keycode, t_img img)
{
	(void)keycode;
	(void)img;
	(void)data;
	ft_putstr_fd ("The session is over!\n", 1);
	exit(0);
}