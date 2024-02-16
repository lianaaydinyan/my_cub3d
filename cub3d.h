#ifndef CUB3D_H
#define CUB3D_H
#include <stdio.h>

#include "./minilibx-linux/mlx.h"

#include "./libft/libft.h"
#include "get_next_line.h"
#include <math.h>
#include <fcntl.h>

//for error handling
#define T_ERROR 3
#define C_ERROR 4
#define M_ERROR 5
#define F_ERROR 6
#define E_ERROR 7
//for ray casting
#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
//paths of texture
#define north 0 //NO
#define south 1 //SO
#define west 2 //WE
#define east 3 //EA


typedef struct s_data t_data;
typedef struct s_img  t_img;
typedef struct s_hero t_hero;
typedef struct s_ray  t_ray;
typedef struct s_game t_game;

struct Sprite
{
  double x;
  double y;
  int texture;
};

typedef struct {
    unsigned int *data;
    size_t size;
    size_t capacity;
} Vector;


struct	s_img {
	int		heigth;
	int		width;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		line_higth;
	int		start;
	int		end;
	int		endian;
};

struct s_hero
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x; 
	double	plane_y;
	double	move_speed;
	double	rot_speed;
};

struct s_ray
{
	double	time;
	double	old_time;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	wall_x;
	double	tex_pos;
	int		line_height;
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		tex_x;
	int		tex_y;
	int		tex_height;
	int		pitch;
};

struct s_game
{
	t_ray	*ray;
	t_hero	*hero;
	t_img	*img;
	t_img	*wall_t;
	t_img	*n_north;
	t_img	*s_south;
	t_img	*w_west;
	t_img	*e_east;
	int		celling_c;
	int		flooring_c;
	void	*mlx_ptr;
	void	*win_ptr;
	int 	**map;
};

struct s_data
{
	char **textures;
	int f;
	int c;
	int win_w;
	int win_h;
	int **map;
	char **map_c;
	double widht;
	int height;
	int count;
	int nb;
	int to_map;
	double cam_x;
	int		tex_num;
	double cam_y;
	double dir_x;
	double dir_y;
	double pos_x;
	double pos_y;
	t_img	*imgg;
	t_hero	*hero;
	t_ray	*ray;
	t_game	*game;
	void	*mlx_ptr;
	void	*win_ptr;
};

int do_walls(t_data *data);
int	key_cross(t_data *data, int keycode, t_img img);
int	key_hook(int keycode, t_data *data, t_img img);
int just_do_it(t_data *data);
int init_win(t_data *data);
int any_invalid(char **line, int i, int j);
int check_neighbor(char **map_c, int i, int j);
int tree_nb(char *line, t_data *data, int flag);
int		parcing(t_data *data, char **argv);
int		errorik(int flag);
char	*get_next_line(int fd);
int		empty_line(char *line);
void	skip_sp(char **line);
int		is_texture(char *line);
int	create_trgb(int t, int r, int g, int b);
int	ft_strlen_t(const char *str);
char	*ft_strdup_t(const char *s1);
int first_texture(char *line, int fd, t_data *data);
int init_colors(char *line , t_data *data);
int is_color(char *line);
int first_texture(char *line, int fd, t_data *data);
int set_texture(char *line, char **textures, int i);
int fill_textures(char *line, char **textures);
int init_textures(char **line, int fd, char **textures);
int first_color(char *line, int fd, t_data *data);
int parce_map(int fd, char *line, t_data* data);
int can_be(char ch);
int direction(char ch);
void	to_int(t_data *data);
void	fill(char *line, int *z_map);
int	get_max_widht(char *file_name);
int	get_height(char **);
void	raycasting(t_data *data);
void	*mlx_xpm_file_to_image(void *mlx_ptr, char *filename,
			       int *width, int *height);
				   



void my_mlx_pixel_put(t_data *data, int x, int y, int color);

void coloring(t_data *data);

#endif