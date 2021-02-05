#include "cube3D.h"

#define texWidth 64
#define texHeight 64

void            my_mlx_pixel_put(t_info_image *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

unsigned int            take_pixel_from_texture(t_info_image *img, int x, int y)
{
    unsigned int color;
    char    *dst;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    // *(unsigned int *)dst = color;
    // write(1, "1", 1);
    color = *(unsigned int *)dst;
    return (color);
}

int threatment_color(int r, int g, int b)
{
  return (r << 16 | g << 8 | b);
}

// защитить malloc
void malloc_array_sprite(t_object_on_scene *objects)
{
  objects->pos_sprite_x = malloc(sizeof(float) * objects->quantity_sprite);
  objects->pos_sprite_y = malloc(sizeof(float) * objects->quantity_sprite);
  objects->struct_array = malloc(sizeof(t_info_image) * objects->quantity_sprite);
}

void search_sprite(t_object_on_scene *objects)
{
  int i;
  int j;
  int count;

  i = 0;
  j = 0;
  count = 0;
  while (objects->map[i] != NULL)
  {
    while (objects->map[i][j] != '\0')
    {
        if (objects->map[i][j] == '2')
        {
          objects->pos_sprite_x[count] = i + 0.5f;
          objects->pos_sprite_y[count] = j + 0.5f;
          count++;
        }
        j++;
    }
    j = 0;
    i++;
  }
}

void quantity_sprite1(t_object_on_scene *objects)
{
  int i;
  int j;
  int quantity_sprite;

  i = 0;
  j = 0;
  quantity_sprite = 0;
  while (objects->map[i] != NULL)
  {
    while (objects->map[i][j] != '\0')
    {
        if (objects->map[i][j] == '2')
          quantity_sprite++;
        j++;
    }
    j = 0;
    i++;
  }
  objects->quantity_sprite = quantity_sprite;
  malloc_array_sprite(objects);
  search_sprite(objects);
}

void  miscalculation_distance(t_object_on_scene *objects)
{
  int i;

  i = 0;
  while (i < objects->quantity_sprite)
  {
    objects->struct_array[i].distance = ((objects->player_position_x - objects->pos_sprite_x[i]) * (objects->player_position_x - objects->pos_sprite_x[i])
      + (objects->player_position_y - objects->pos_sprite_y[i]) * (objects->player_position_y - objects->pos_sprite_y[i]));
      i++;
  }
}

void  sorting_sprite(t_object_on_scene *objects)
{
  int i;
  int j;
  float tmp;
  float position;

  i = 0;
  j = 0;
  while (i < objects->quantity_sprite)
  {
    while (j < objects->quantity_sprite)
    {
      if (objects->struct_array[i].distance > objects->struct_array[j].distance)// && j < objects->quantity_sprite)
      {
        // подмена дистанций
        tmp = objects->struct_array[j].distance;
        objects->struct_array[j].distance = objects->struct_array[i].distance;
        objects->struct_array[i].distance = tmp;
        // подмена x позиций
        position = objects->pos_sprite_x[i];
        objects->pos_sprite_x[i] = objects->pos_sprite_x[j];
        objects->pos_sprite_x[j] = position;
        // подмена y позиций
        position = objects->pos_sprite_y[i];
        objects->pos_sprite_y[i] = objects->pos_sprite_y[j];
        objects->pos_sprite_y[j] = position;
      }
      j++;
    }
    j = 0;
    i++;
  }
}

void  draw_sprite(t_object_on_scene *objects)
{
    miscalculation_distance(objects);
    sorting_sprite(objects);
    //after sorting the sprites, do the projection and draw them
    for(int i = 0; i < objects->quantity_sprite; i++)
    {
      translate_sprite_pos(objects, i);
      calculate_height_sprite(objects);
      calculate_width_sprite(objects);
      //loop through every vertical stripe of the sprite on screen
      draw_vertical_line(objects);
    }
}

int rebuild_scene(t_object_on_scene *objects)
{
    int x;

    x = 0;
    while (x < objects->s_value_from_map.resolution_x)
    {
      raycast(objects, x);
      if (objects->side == 0)
        objects->per_wall_dst = (objects->posmapx - objects->player_position_x +
          (1 - objects->step_x) / 2) / objects->rdx;
      else
        objects->per_wall_dst = (objects->posmapy - objects->player_position_y +
          (1 - objects->step_y) / 2) / objects->rdy;
      objects->perp_dist[x] = objects->per_wall_dst;
      objects->line_ray = (int)(objects->s_value_from_map.resolution_y / objects->per_wall_dst);
      calculate_start_end_wall(objects);
      objects->steps_texture = 1.0 * texHeight / objects->line_ray;
      objects->texture_pos = (objects->start_wall - objects->s_value_from_map.resolution_y /
        2 + objects->line_ray / 2) * objects->steps_texture;
      paint_wall(objects, x);
      x++;
    }
    draw_sprite(objects);
    return (1);
}

// int				key_hook(int keycode, t_object_on_scene *obj)
// {
//   // printf("keycode: %d\n", keycode);
//   // printf("x: %f, y: %f\n", obj->player_direction_x, obj->player_direction_y);
//   double moveSpeed = 0.1; //the constant value is in squares/second
//   double rotSpeed = 0.1; // speed rotation
//   if (keycode == 53)
//   {
//     system("killall afplay");
//     exit(1);
//   }
//   if (keycode == 13) // up
//   {
//     // write(1, "1", 1);
//     if (obj->map[(int)(obj->player_position_x + obj->player_direction_x * moveSpeed)][(int)(obj->player_position_y)] == '0')
//       obj->player_position_x += obj->player_direction_x * moveSpeed;
//     if (obj->map[(int)(obj->player_position_x)][(int)(obj->player_position_y + obj->player_direction_y * moveSpeed)] == '0')
//         obj->player_position_y += obj->player_direction_y * moveSpeed;
//     // printf("x = %f, y = %f\n", obj->player_position_x, obj->player_position_y);
//   }
//   if (keycode == 1) // down
//   {
//     if (obj->map[(int)(obj->player_position_x - obj->player_direction_x * moveSpeed)][(int)(obj->player_position_y)] == '0')
//       obj->player_position_x -= obj->player_direction_x * moveSpeed;
//     if (obj->map[(int)(obj->player_position_x)][(int)(obj->player_position_y - obj->player_direction_y * moveSpeed)] == '0')
//       obj->player_position_y -= obj->player_direction_y * moveSpeed;
//   }
//   if (keycode == 0) // влево
//   {
//     // printf("obj->player_position_x + obj->planeX = %f\n", obj->player_position_x + obj->planeX);
//     if(obj->map[(int)(obj->player_position_x)][(int)(obj->player_position_y + obj->player_direction_x * moveSpeed)] == '0')
//       obj->player_position_y += obj->player_direction_x * moveSpeed;
//     if(obj->map[(int)(obj->player_position_x - obj->player_direction_y * moveSpeed)][(int)(obj->player_position_y)] == '0')
//       obj->player_position_x -= obj->player_direction_y * moveSpeed;
//   }
//   if (keycode == 2) // вправо
//   {
//     if(obj->map[(int)(obj->player_position_x)][(int)(obj->player_position_y - obj->player_direction_x * moveSpeed)] == '0')
//       obj->player_position_y -= obj->player_direction_x * moveSpeed;
//     if(obj->map[(int)(obj->player_position_x + obj->player_direction_y * moveSpeed)][(int)(obj->player_position_y)] == '0')
//       obj->player_position_x += obj->player_direction_y * moveSpeed;
//   }

//   if(keycode == 124) // стрелочка вправо
//     {
//       //both camera direction and camera plane must be rotated
//       double oldDirX = obj->player_direction_x;
//       obj->player_direction_x = obj->player_direction_x * cos(-rotSpeed) - obj->player_direction_y * sin(-rotSpeed);
//       obj->player_direction_y = oldDirX * sin(-rotSpeed) + obj->player_direction_y * cos(-rotSpeed);
//       double oldPlaneX = obj->planeX;
//       obj->planeX = obj->planeX * cos(-rotSpeed) - obj->planeY * sin(-rotSpeed);
//       obj->planeY = oldPlaneX * sin(-rotSpeed) + obj->planeY * cos(-rotSpeed);
//     }
//     //rotate to the left
//     if(keycode == 123) // стрелочка влево
//     {
//       //both camera direction and camera plane must be rotated
//       double oldDirX = obj->player_direction_x;
//       obj->player_direction_x = obj->player_direction_x * cos(rotSpeed) - obj->player_direction_y * sin(rotSpeed);
//       obj->player_direction_y = oldDirX * sin(rotSpeed) + obj->player_direction_y * cos(rotSpeed);
//       double oldPlaneX = obj->planeX;
//       obj->planeX = obj->planeX * cos(rotSpeed) - obj->planeY * sin(rotSpeed);
//       obj->planeY = oldPlaneX * sin(rotSpeed) + obj->planeY * cos(rotSpeed);
//     }
//     mlx_destroy_image(obj->mlx, obj->window.img);
//     obj->window.img = mlx_new_image(obj->mlx, obj->s_value_from_map.resolution_x, obj->s_value_from_map.resolution_y);
//         obj->window.addr = mlx_get_data_addr(obj->window.img, &obj->window.bits_per_pixel,
//             &obj->window.line_length, &obj->window.endian);
//     rebuild_scene(obj);
//     mlx_put_image_to_window(obj->mlx, obj->win, obj->window.img, 0, 0);
//   return (1);
// }

// определение направление взгляда
void  cardinal_points(t_object_on_scene *objects)
{
  if (objects->cardinal_point == 'N') // смотрит вверх
  {
    objects->player_direction_x = -1;
    objects->planeY = 0.66;
  }
  if (objects->cardinal_point == 'S') // смотрит вниз
  {
    objects->player_direction_x = 1;
    objects->planeY = -0.66;
  }
  if (objects->cardinal_point == 'W') // смотрет влево
  {
    objects->player_direction_y = -1;
    objects->planeX = -0.66;
  }
  if (objects->cardinal_point == 'E') // смотрит вправо
  {
    objects->player_direction_y = 1;
    objects->planeX = 0.66;
  }
}

void take_position_player(t_object_on_scene *objects)
{
    int i = 0;
    int j = 0;
    while (objects->map[i] != NULL)
    {
      while (objects->map[i][j] != '\0')
      {
        if (objects->map[i][j] == 'N' || objects->map[i][j] == 'W' || objects->map[i][j] == 'E'
          || objects->map[i][j] == 'S')
        {
          objects->player_position_x = i + 0.1;
          objects->player_position_y = j + 0.1;
          objects->cardinal_point = objects->map[i][j];
        }
        j++;
      }
      i++;
      j = 0;
    }
    objects->map[(int)(objects->player_position_x)][(int)(objects->player_position_y)] = '0';
}

void convert_xpm_to_image(t_object_on_scene *objects, t_info_image *texture, char *path)
{
    char *relative_path = path;
    void *img = mlx_xpm_file_to_image(objects->mlx, relative_path, &texture->width_x, &texture->height_y);
    if (img != NULL) // если картинка найдена
    {
      texture->addr = mlx_get_data_addr(img, &texture->bits_per_pixel,
          &texture->line_length, &texture->endian);
    }
    else
      threatment_error(1, "Not valide path to texture", objects);
}

void filling_struct_texture(t_object_on_scene *objects)
{
  convert_xpm_to_image(objects, &objects->texture_north, objects->s_value_from_map.north_texture);
  convert_xpm_to_image(objects, &objects->texture_east, objects->s_value_from_map.east_texture);
  convert_xpm_to_image(objects, &objects->texture_south, objects->s_value_from_map.south_texture);
  convert_xpm_to_image(objects, &objects->texture_west, objects->s_value_from_map.west_texture);
  convert_xpm_to_image(objects, &objects->texture_sprite, objects->s_value_from_map.sprite_texture);
}

void	filling_file_screenshot(int fd, t_object_on_scene *obj)
{
	int	i;
	int	j;
	int	color;

	i = obj->s_value_from_map.resolution_y;
	while (--i >= 0)
	{
		j = -1;
		while (++j < obj->s_value_from_map.resolution_x)
		{
			color = *(int*)(obj->window.addr + (i * obj->window.line_length
					+ j * (obj->window.bits_per_pixel / 8)));
			write(fd, &color, 4);
		}
	}
}

void  screenshot(t_object_on_scene *objects)
{
  int fd;
  int size_screen = objects->s_value_from_map.resolution_x * objects->s_value_from_map.resolution_y * 4 + 54;
  int zero = 0;
  int pos_pixel_data = 54;
  short plane = 1;
  int size = objects->s_value_from_map.resolution_x * objects->s_value_from_map.resolution_y;

  fd = open("screen.bmp", O_CREAT | O_RDWR, 0666);
  if (fd < 0) // вывод ошибки
    exit(1);
  write(fd, "BM", 2);
  write(fd, &size_screen, 4);
  write(fd, &zero, 4);
  write(fd, &pos_pixel_data, 4);
  pos_pixel_data = 40;
  write(fd, &pos_pixel_data, 4);
  write(fd, &objects->s_value_from_map.resolution_x, 4);
  write(fd, &objects->s_value_from_map.resolution_y, 4);
  write(fd, &plane, 2);
  plane = 32;
  write(fd, &plane, 2);
  write(fd, &zero, 4);
  write(fd, &size, 4);
  size_screen = 1000;
  write(fd, &size_screen, 4);
  write(fd, &size_screen, 4);
  write(fd, &zero, 4);
  write(fd, &zero, 4);
  // write(fd, &objects->window, 4);

  filling_file_screenshot(fd, objects);
}

int  close_window(t_object_on_scene *objects)
{
  mlx_destroy_window(objects->mlx, objects->win);
  exit(1);
  return (1);
}

void  standart_value_map(t_object_on_scene *objects)
{
  objects->s_value_from_map.resolution_x = -1;
  objects->s_value_from_map.resolution_y = -1;
  objects->s_value_from_map.north_texture = NULL;
  objects->s_value_from_map.south_texture = NULL;
  objects->s_value_from_map.west_texture = NULL;
  objects->s_value_from_map.east_texture = NULL;
  objects->s_value_from_map.sprite_texture = NULL;
  objects->s_value_from_map.ceilling_color_r = -1;
  objects->s_value_from_map.ceilling_color_g = -1;
  objects->s_value_from_map.ceilling_color_b = -1;
  objects->s_value_from_map.floor_color_r = -1;
  objects->s_value_from_map.floor_color_g = -1;
  objects->s_value_from_map.floor_color_b = -1;
  objects->s_value_from_map.valide_map = 1;
  objects->s_value_from_map.quantity_string = 0;
  objects->s_value_from_map.quantity_player = 0;
  objects->s_value_from_map.quantity_string_map = 0;
  objects->s_value_from_map.quantity_string_before_map = 0;
  objects->s_value_from_map.meet_map = 0;
}

int main(int argc, char **argv)
{
    t_object_on_scene objects;
    standart_value_map(&objects);
    validate_arguments(argv[1], &objects, argc, argv);
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
      threatment_error(1, "Not exist file!", &objects);
    manage_function(fd, &objects.s_value_from_map, &objects);
    validate_map1(&objects, fd, argv[1]);
    objects.perp_dist = malloc(sizeof(float) * objects.s_value_from_map.resolution_x);
    objects.mlx = mlx_init();
    objects.win = mlx_new_window(objects.mlx, objects.s_value_from_map.resolution_x, objects.s_value_from_map.resolution_y, "Cube3D");
    take_position_player(&objects);
    cardinal_points(&objects);
    // system("afplay DJ_Vasya_Deep_House.mp3 & "); // музыка
    quantity_sprite1(&objects);
    objects.speed = 5;
    objects.window.img = mlx_new_image(objects.mlx, objects.s_value_from_map.resolution_x, objects.s_value_from_map.resolution_y);
       objects.window.addr = mlx_get_data_addr(objects.window.img, &objects.window.bits_per_pixel,
           &objects.window.line_length, &objects.window.endian);
    filling_struct_texture(&objects);
    if (argc == 3)
    {
      rebuild_scene(&objects);
      screenshot(&objects);
    }
    else
    {
      rebuild_scene(&objects);
      mlx_put_image_to_window(objects.mlx, objects.win, objects.window.img, 0, 0);
      mlx_hook(objects.win, 2, 1L << 0, key_hook, &objects);
      mlx_hook(objects.win, 17, 1L << 0, close_window, &objects);
      mlx_loop(objects.mlx);
    }
}
