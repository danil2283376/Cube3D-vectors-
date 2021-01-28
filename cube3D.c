#include <math.h>
#include "minilibx_mms_20200219/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cube3D.h"

//place the example code below here:

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
    color = *(unsigned int *)dst;
    return (color);
}

int threatment_color(int r, int g, int b)
{
  return (r << 16 | g << 8 | b);
}

int rebuild_scene(t_object_on_scene *objects)
{
    // mlx_destroy_image(objects->mlx, objects->window.img);
    int h = objects->s_value_from_map.resolution_y;
    int w = objects->s_value_from_map.resolution_x;
    int sprite = 0;
    for (int x = 0; x < w; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
      //                            -1                0                   0,001
      double rayDirX = objects->player_direction_x + objects->planeX * cameraX;
      double rayDirY = objects->player_direction_y + objects->planeY * cameraX;
      //which box of the map we're in
      int mapX = (int)(objects->player_position_x);
      int mapY = (int)(objects->player_position_y);

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

       //length of ray from one x or y-side to next x or y-side
      double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
      double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (objects->player_position_x - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - objects->player_position_x) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (objects->player_position_y - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - objects->player_position_y) * deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0; // попадание по Y
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1; // попадание по X
        }
        //Check if ray has hit a wall
        if (objects->map[mapX][mapY] == '1')
          hit = 1;
        if (objects->map[mapX][mapY] == '2')
        {
          hit = 1;
          sprite = 1;
        }
      }
      // printf("stepX: %d, stepY: %d\n", stepX, stepY);
      //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
      if (side == 0)  perpWallDist = (mapX - objects->player_position_x + (1 - stepX) / 2) / rayDirX;
      else            perpWallDist = (mapY - objects->player_position_y + (1 - stepY) / 2) / rayDirY;
      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if (drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if (drawEnd >= h) drawEnd = h - 1;

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (side == 0) wallX = objects->player_position_y + perpWallDist * rayDirY;
      else           wallX = objects->player_position_x + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(texWidth));
      if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

      double step = 1.0 * texHeight / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
      for (int y = 0; y < h; y++)
      {
        if (y < drawStart) // потолок
          my_mlx_pixel_put(&objects->window, x, y, threatment_color(objects->s_value_from_map.ceilling_color_r, objects->s_value_from_map.ceilling_color_g, objects->s_value_from_map.ceilling_color_b));
        if (y > drawStart + 3 && y < drawEnd - 3 && (sprite == 0))
        {
          //y coordinate on the texture
          int texY = (int)texPos & (texHeight - 1);
          texPos += step;
          // unsigned int color = take_pixel_from_texture(&objects->texture_north, texX, texY);
          // int color = (int)(objects->texture.addr[/*texHeight * texY + texX*/y * objects->texture.line_length + x * (objects->texture.bits_per_pixel / 8)]);
          // printf("%d\n", texHeight * texY + texX);
          if (side == 0) // N OR S
          {
            if (stepX > 0)
            {
              unsigned int color = take_pixel_from_texture(&objects->texture_north, texX, texY);
              my_mlx_pixel_put(&objects->window, x, y, color);
            }
            else if (stepX < 0)
            {
              unsigned int color = take_pixel_from_texture(&objects->texture_south, texX, texY);
               my_mlx_pixel_put(&objects->window, x, y, color);
            }
          }
          else if (side == 1) // W OR E
          {
            if (stepY > 0)
            {
              unsigned int color = take_pixel_from_texture(&objects->texture_east, texX, texY);
              my_mlx_pixel_put(&objects->window, x, y, color);
            }
            else if (stepY < 0)
            {
              unsigned int color = take_pixel_from_texture(&objects->texture_west, texX, texY);
              my_mlx_pixel_put(&objects->window, x, y, color);
            }
          }
        }
        if (y > drawEnd) // пол
          my_mlx_pixel_put(&objects->window, x, y, threatment_color(objects->s_value_from_map.floor_color_r, objects->s_value_from_map.floor_color_g, objects->s_value_from_map.floor_color_b));
      }
      // for(int i = 0; i < numSprites; i++)
      // {
      //   //translate sprite position to relative to camera
      //   int num = objects->spriteOrder[i];
      //   double spriteX = sprite[num].x - posX;
      //   double spriteY = sprite[spriteOrder[i]].y - posY;

      //   //transform sprite with the inverse camera matrix
      //   // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      //   // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      //   // [ planeY   dirY ]                                          [ -planeY  planeX ]

      //   double invDet = 1.0 / (objects->planeX * objects->player_direction_y - objects->player_direction_x * objects->planeY); //required for correct matrix multiplication

      //   double transformX = invDet * (objects->player_direction_y * spriteX - objects->player_direction_x * spriteY);
      //   double transformY = invDet * (-objects->planeY * spriteX + objects->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

      //   int spriteScreenX = (int)((w / 2) * (1 + transformX / transformY));

      //   //calculate height of the sprite on screen
      //   int spriteHeight = abs((int)(h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
      //   //calculate lowest and highest pixel to fill in current stripe
      //   int drawStartY = -spriteHeight / 2 + h / 2;
      //   if(drawStartY < 0) drawStartY = 0;
      //   int drawEndY = spriteHeight / 2 + h / 2;
      //   if(drawEndY >= h) drawEndY = h - 1;

      //   //calculate width of the sprite
      //   int spriteWidth = abs((int)(h / (transformY)));
      //   int drawStartX = -spriteWidth / 2 + spriteScreenX;
      //   if(drawStartX < 0) drawStartX = 0;
      //   int drawEndX = spriteWidth / 2 + spriteScreenX;
      //   if(drawEndX >= w) drawEndX = w - 1;

      //   //loop through every vertical stripe of the sprite on screen
      //   for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      //   {
      //     int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
      //     //the conditions in the if are:
      //     //1) it's in front of camera plane so you don't see things behind you
      //     //2) it's on the screen (left)
      //     //3) it's on the screen (right)
      //     //4) ZBuffer, with perpendicular distance
      //     if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
      //     for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
      //     {
      //       int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
      //       int texY = ((d * texHeight) / spriteHeight) / 256;
      //       unsigned int color = objects->texture_sprite//texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
      //       if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
      //     }
      //   }
      // // отрисовка спрайта
      // for (int y = 0; y < h && (sprite == 1); y++)
      // {
      //   if (y < drawStart) // потолок
      //     my_mlx_pixel_put(&objects->window, x, y, threatment_color(objects->s_value_from_map.ceilling_color_r, objects->s_value_from_map.ceilling_color_g, objects->s_value_from_map.ceilling_color_b));

      //   if (y > drawEnd) // пол
      //     my_mlx_pixel_put(&objects->window, x, y, threatment_color(objects->s_value_from_map.floor_color_r, objects->s_value_from_map.floor_color_g, objects->s_value_from_map.floor_color_b));
      // }
      sprite = 0;
      // objects->z_buffer[x] = perpWallDist;
    }
    // printf("x = %f, y = %f\n", objects->player_position_x, objects->player_position_y);
    return (1);
}

int				key_hook(int keycode, t_object_on_scene *obj)
{
  printf("x: %d\n", keycode);
  // printf("x: %f, y: %f\n", obj->player_direction_x, obj->player_direction_y);
  double moveSpeed = 0.1; //the constant value is in squares/second
  double rotSpeed = 0.05; // speed rotation
  if (keycode == 257)
  {
    moveSpeed = 1;
  }
  if (keycode == 53)
  {
     system("killall afplay");
      exit(1);
  }
  if (keycode == 13) // up
  {
    // write(1, "1", 1);
    if (obj->map[(int)(obj->player_position_x + obj->player_direction_x * moveSpeed)][(int)(obj->player_position_y)] == '0')
      obj->player_position_x += obj->player_direction_x * moveSpeed;
    if (obj->map[(int)(obj->player_position_x)][(int)(obj->player_position_y + obj->player_direction_y * moveSpeed)] == '0')
        obj->player_position_y += obj->player_direction_y * moveSpeed;
    // printf("x = %f, y = %f\n", obj->player_position_x, obj->player_position_y);
  }
  if (keycode == 1) // down
  {
    if (obj->map[(int)(obj->player_position_x - obj->player_direction_x * moveSpeed)][(int)(obj->player_position_y)] == '0')
      obj->player_position_x -= obj->player_direction_x * moveSpeed;
    if (obj->map[(int)(obj->player_position_x)][(int)(obj->player_position_y - obj->player_direction_y * moveSpeed)] == '0')
      obj->player_position_y -= obj->player_direction_y * moveSpeed;
  }
  if (keycode == 0) // влево
  {
    // printf("obj->player_position_x + obj->planeX = %f\n", obj->player_position_x + obj->planeX);
    if(obj->map[(int)(obj->player_position_x)][(int)(obj->player_position_y + obj->player_direction_x * moveSpeed)] == '0')
      obj->player_position_y += obj->player_direction_x * moveSpeed;
    if(obj->map[(int)(obj->player_position_x - obj->player_direction_y * moveSpeed)][(int)(obj->player_position_y)] == '0')
      obj->player_position_x -= obj->player_direction_y * moveSpeed;
  }
  if (keycode == 2) // вправо
  {
    if(obj->map[(int)(obj->player_position_x)][(int)(obj->player_position_y - obj->player_direction_x * moveSpeed)] == '0')
      obj->player_position_y -= obj->player_direction_x * moveSpeed;
    if(obj->map[(int)(obj->player_position_x + obj->player_direction_y * moveSpeed)][(int)(obj->player_position_y)] == '0')
      obj->player_position_x += obj->player_direction_y * moveSpeed;
  }

  if(keycode == 124) // стрелочка вправо
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = obj->player_direction_x;
      obj->player_direction_x = obj->player_direction_x * cos(-rotSpeed) - obj->player_direction_y * sin(-rotSpeed);
      obj->player_direction_y = oldDirX * sin(-rotSpeed) + obj->player_direction_y * cos(-rotSpeed);
      double oldPlaneX = obj->planeX;
      obj->planeX = obj->planeX * cos(-rotSpeed) - obj->planeY * sin(-rotSpeed);
      obj->planeY = oldPlaneX * sin(-rotSpeed) + obj->planeY * cos(-rotSpeed);
    }
    //rotate to the left
    if(keycode == 123) // стрелочка влево
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = obj->player_direction_x;
      obj->player_direction_x = obj->player_direction_x * cos(rotSpeed) - obj->player_direction_y * sin(rotSpeed);
      obj->player_direction_y = oldDirX * sin(rotSpeed) + obj->player_direction_y * cos(rotSpeed);
      double oldPlaneX = obj->planeX;
      obj->planeX = obj->planeX * cos(rotSpeed) - obj->planeY * sin(rotSpeed);
      obj->planeY = oldPlaneX * sin(rotSpeed) + obj->planeY * cos(rotSpeed);
    }
    mlx_destroy_image(obj->mlx, obj->window.img);
    obj->window.img = mlx_new_image(obj->mlx, obj->s_value_from_map.resolution_x, obj->s_value_from_map.resolution_y);
        obj->window.addr = mlx_get_data_addr(obj->window.img, &obj->window.bits_per_pixel,
            &obj->window.line_length, &obj->window.endian);
    rebuild_scene(obj);
    mlx_put_image_to_window(obj->mlx, obj->win, obj->window.img, 0, 0);
  return (1);
}

// определение направление взгляда
void  cardinal_points(t_object_on_scene *objects)
{
  if (objects->cardinal_point == 'N') // смотрит вверх
  {
    objects->player_direction_y = 1;
    objects->planeX = 0.66;
  }
  if (objects->cardinal_point == 'S') // смотрит вниз
  {
    objects->player_direction_y = -1;
    objects->planeX = -0.66;
  }
  if (objects->cardinal_point == 'W') // смотрет влево
  {
    objects->player_direction_x = -1;
    objects->planeY = 0.66;
  }
  if (objects->cardinal_point == 'E') // смотрит вправо
  {
    objects->player_direction_x = 1;
    objects->planeY = -0.66;
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
          objects->player_position_x = i;
          objects->player_position_y = j;
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
    char *relative_path = path;//objects->s_value_from_map.north_texture;
    void *img = mlx_xpm_file_to_image(objects->mlx, relative_path, &texture->width_x, &texture->height_y);
    if (img != NULL) // если картинка найдена
    {
      texture->addr = mlx_get_data_addr(img, &texture->bits_per_pixel,
          &texture->line_length, &texture->endian);
    }
    else
      objects->s_value_from_map.south_texture = NULL; // проверка на валидность
}

void filling_struct_texture(t_object_on_scene *objects)
{
  convert_xpm_to_image(objects, &objects->texture_north, objects->s_value_from_map.north_texture);
  convert_xpm_to_image(objects, &objects->texture_east, objects->s_value_from_map.east_texture);
  convert_xpm_to_image(objects, &objects->texture_south, objects->s_value_from_map.south_texture);
  convert_xpm_to_image(objects, &objects->texture_west, objects->s_value_from_map.west_texture);
  convert_xpm_to_image(objects, &objects->texture_sprite, objects->s_value_from_map.sprite_texture);
}

int main()
{
    int fd = open("map.cub", O_RDONLY);
    t_object_on_scene objects;
    objects.map = manage_function(fd, &objects.s_value_from_map);
    double ZBuffer[objects.s_value_from_map.resolution_x];
    objects.z_buffer = ZBuffer;
    objects.mlx = mlx_init();
    objects.win = mlx_new_window(objects.mlx, objects.s_value_from_map.resolution_x, objects.s_value_from_map.resolution_y, "Cube3D");
    take_position_player(&objects);
    cardinal_points(&objects);
    system("afplay DJ_Vasya_Deep_House.mp3 & ");
    objects.speed = 5;
    objects.window.img = mlx_new_image(objects.mlx, objects.s_value_from_map.resolution_x, objects.s_value_from_map.resolution_y);
       objects.window.addr = mlx_get_data_addr(objects.window.img, &objects.window.bits_per_pixel,
           &objects.window.line_length, &objects.window.endian);
    filling_struct_texture(&objects);
    rebuild_scene(&objects);
    mlx_put_image_to_window(objects.mlx, objects.win, objects.window.img, 0, 0);
    mlx_loop_hook(objects.mlx, rebuild_scene, &objects);
    mlx_hook(objects.win, 2, 1L << 0, key_hook, &objects);
    mlx_loop(objects.mlx);
}
