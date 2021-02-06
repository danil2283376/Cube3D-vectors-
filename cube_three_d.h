/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_three_d.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:13:51 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:40:25 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_THREE_D_H
# define CUBE_THREE_D_H

# include "minilibx_mms_20200219/mlx.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <errno.h>

typedef	struct			s_value_from_map
{
	int					resolution_x;
	int					resolution_y;

	char				*north_texture;
	char				*south_texture;
	char				*west_texture;
	char				*east_texture;
	char				*sprite_texture;

	int					floor_color_r;
	int					floor_color_g;
	int					floor_color_b;

	int					ceilling_color_r;
	int					ceilling_color_g;
	int					ceilling_color_b;
	int					valide_map;
	int					quantity_string;
	int					quantity_player;
	int					quantity_string_map;
	int					quantity_string_before_map;
	int					meet_map;
	int					is_map;
}						t_value_from_map;

typedef struct			s_info_image
{
	void				*mlx;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width_x;
	int					height_y;
	int					color;
	float				distance;
}						t_info_image;

typedef	struct			s_object_on_scene
{
	t_info_image		texture_north;
	t_info_image		texture_south;
	t_info_image		texture_west;
	t_info_image		texture_east;
	t_info_image		texture_sprite;
	t_value_from_map	s_value_from_map;
	t_info_image		player;
	int					map_hide;
	float				player_position_x;
	float				player_position_y;
	float				player_direction_x;
	float				player_direction_y;
	float				plane_x;
	float				plane_y;
	float				player_angle;
	float				speed;
	float				rot_speed;
	float				min_angle;
	float				max_angle;
	float				width_screen;
	float				heigth_screen;
	float				fov;
	char				cardinal_point;

	int					quantity_sprite;
	float				*pos_sprite_x;
	float				*pos_sprite_y;
	t_info_image		*struct_array;
	float				*perp_dist;

	t_info_image		window;
	t_info_image		floor;
	t_info_image		wall;
	t_info_image		prize;
	t_info_image		ray;
	float				top_ray;
	float				down_ray;
	float				left_ray;
	float				right_ray;
	float				position_ray_x;
	float				position_ray_y;
	float				ray_min_angle;
	float				ray_max_angle;
	char				**map;
	void				*mlx;
	void				*win;
	int					width_bloks_x;
	int					height_bloks_y;

	float				pos_camera_x;
	float				rdx;
	float				rdy;
	int					posmapx;
	int					posmapy;
	float				del_dis_x;
	float				del_dis_y;
	int					step_x;
	int					step_y;
	float				side_dist_x;
	float				side_dist_y;
	float				per_wall_dst;
	int					hit;
	int					side;
	int					line_ray;
	int					start_wall;
	int					end_wall;
	float				hit_wall;
	float				steps_texture;
	float				texture_pos;
	float				texture_x;
	float				texture_y;

	float				position_sprite_x;
	float				position_sprite_y;
	float				inverse_matrix;
	float				transform_pos_x;
	float				transform_pos_y;
	int					screen_pos_x;
	int					sprite_height;
	int					start_sprite_y;
	int					end_sprite_y;
	int					start_sprite_x;
	int					end_sprite_x;
	int					width_sprite;
	int					texture_sprite_x;
	int					texture_sprite_y;
	int					color_pixel_sprite;
}						t_object_on_scene;

int						len_number(int number);
int						ft_strcmp(const char *str1, const char *str2);
int						pass_space(char *substr);
int						count_comma(char *substr);
void					get_value_resolution(char *line,
	t_value_from_map *value_map);
void					get_path_sprite(char *line,
	t_value_from_map *value_map);
void					get_path_east(char *line,
	t_value_from_map *value_map);
void					get_path_north(char *line,
	t_value_from_map *value_map);
void					get_path_south(char *line,
	t_value_from_map *value_map);
void					get_path_west(char *line,
	t_value_from_map *value_map);
void					get_value_color(char *line,
	t_value_from_map *value_map);
void					get_value_color_floor(char *line,
	t_value_from_map *value_map);
void					standart_value_struct(t_value_from_map *value_map);
int						value_from_maps_not_null(t_value_from_map *value_map);
void					paint_map(char **map, t_value_from_map *value_map);
char					**manage_function(int fd, t_value_from_map *value_map,
	t_object_on_scene *objects);
void					validate_map1(t_object_on_scene *object,
	int fd, char *name_file);
void					threatment_error(int fd, char *error,
	t_object_on_scene *objects);
void					check_valide_map(t_object_on_scene *objects);
void					validate_arguments(char *line,
	t_object_on_scene *objects, int argc, char **argv);
void					validate_save(char *line, t_object_on_scene *objects);
void					raycast(t_object_on_scene *objects, int x);
void					paint_wall(t_object_on_scene *objects, int x);
unsigned int			take_pixel_from_texture(t_info_image *img,
	int x, int y);
void					my_mlx_pixel_put(t_info_image *img,
	int x, int y, int color);
void					threatment_error(int fd,
	char *error, t_object_on_scene *objects);
int						threatment_color(int r, int g, int b);
void					calculate_start_end_wall(t_object_on_scene *objects);
void					translate_sprite_pos(t_object_on_scene *objects, int i);
void					calculate_height_sprite(t_object_on_scene *objects);
void					calculate_width_sprite(t_object_on_scene *objects);
void					draw_vertical_line(t_object_on_scene *objects);
int						key_hook(int keycode, t_object_on_scene *obj);
int						rebuild_scene(t_object_on_scene *objects);
void					move_up(t_object_on_scene *obj, float move_speed);
void					move_down(t_object_on_scene *obj, float move_speed);
void					move_left(t_object_on_scene *obj, float move_speed);
void					move_right(t_object_on_scene *obj, float move_speed);
void					rotation_left(t_object_on_scene *obj,
	float speed_rotation);
void					rotation_right(t_object_on_scene *obj,
	float speed_rotation);
void					screenshot(t_object_on_scene *objects);
void					standart_value_map(t_object_on_scene *objects);
void					filling_struct_texture(t_object_on_scene *objects);
void					convert_xpm_to_image(t_object_on_scene *objects,
	t_info_image *texture, char *path);
void					take_position_player(t_object_on_scene *objects);
void					cardinal_points(t_object_on_scene *objects);
void					miscalculation_distance(t_object_on_scene *objects);
void					sorting_sprite(t_object_on_scene *objects);
void					draw_sprite(t_object_on_scene *objects);
void					quantity_sprite1(t_object_on_scene *objects);
void					search_sprite(t_object_on_scene *objects);
void					malloc_array_sprite(t_object_on_scene *objects);
int						return_value(char *line, int start, int count_space);
void					is_screenshot(t_object_on_scene *objects);
#endif
