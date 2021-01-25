#include <math.h>
#include "minilibx_mms_20200219/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cube3D.h"

//place the example code below here:

#define screenWidth 1920
#define screenHeight 1080
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void            my_mlx_pixel_put(t_info_image *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int threatment_color(int r, int g, int b)
{
  return (r << 16 | g << 8 | b);
}

void drawBuffer(unsigned int *buffer)
{

}

int rebuild_scene(t_object_on_scene *objects)
{
    // mlx_destroy_image(objects->mlx, objects->window.img);
    int h = screenHeight;
    int w = screenWidth;
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
        if(objects->map[mapX][mapY] != '0')
        {
          // printf("worldMap: %d\n", worldMap[mapX][mapY]);
          hit = 1;
        }
      }
      // printf("stepX: %d, stepY: %d\n", stepX, stepY);
      //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
      if (side == 0) perpWallDist = (mapX - objects->player_position_x + (1 - stepX) / 2) / rayDirX;
      else          perpWallDist = (mapY - objects->player_position_y + (1 - stepY) / 2) / rayDirY;

      // int a = mapWidth * mapWidth * mapWidth;
      // else if (side == 0)
      //   color = 0xFFFFFF;
      // else if (side == 1)
      //   color = 0x000000;
      // printf("worldMap: %d\n", worldMap[mapY][mapX]);
      // else
      //   color = 0x000000;

      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h) drawEnd = h - 1;
      for (int y = 0; y < h; y++)
      {
        if (y < drawStart)
          my_mlx_pixel_put(&objects->window, x, y, threatment_color(objects->s_value_from_map.ceilling_color_r, objects->s_value_from_map.ceilling_color_g, objects->s_value_from_map.ceilling_color_b));
        if (y >= drawStart && y <= drawEnd)
        {
          if (side == 0) // N OR S
          {
            if (stepX > 0)
              my_mlx_pixel_put(&objects->window, x, y, 0x808080);
            else if (stepX < 0)
               my_mlx_pixel_put(&objects->window, x, y, 0xFF0000);
          }
          else if (side == 1) // W OR E
          {
            if (stepY > 0)
              my_mlx_pixel_put(&objects->window, x, y, 0x0000FF);
            else if (stepY < 0)
              my_mlx_pixel_put(&objects->window, x, y, 0xFFFFFF);
          }
        }
        if (y > drawEnd)
          my_mlx_pixel_put(&objects->window, x, y, threatment_color(objects->s_value_from_map.floor_color_r, objects->s_value_from_map.floor_color_g, objects->s_value_from_map.floor_color_b));
      }
      //choose wall color
      //draw the pixels of the stripe as a vertical line

// //texturing calculations
//         int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

//         //calculate value of wallX
//         double wallX; //where exactly the wall was hit
//         if (side == 0) wallX = objects->player_position_y + perpWallDist * rayDirY;
//         else           wallX = objects->player_position_x + perpWallDist * rayDirX;
//         wallX -= floor((wallX));

//         //x coordinate on the texture
//         int texX = (int)(wallX * (double)(texWidth));
//         if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
//         if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

//               // How much to increase the texture coordinate per screen pixel
//         double step = 1.0 * texHeight / lineHeight;
//         // Starting texture coordinate
//         double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
//         for(int y = drawStart; y<drawEnd; y++)
//         {
//           // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
//           int texY = (int)texPos & (texHeight - 1);
//           texPos += step;
//           unsigned int color = objects->texture[texNum][texHeight * texY + texX];
//           //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
//           if(side == 1) color = (color >> 1) & 8355711;
//           objects->buffer[y][x] = color;
//         }

//       drawBuffer(objects->buffer[0]);
//       for(int y = 0; y < h; y++)
//         for(int x = 0; x < w; x++)
//          objects->buffer[y][x] = 0;
    }
    // printf("x = %f, y = %f\n", objects->player_position_x, objects->player_position_y);
    return (1);
}

int				key_hook(int keycode, t_object_on_scene *obj)
{
  // printf("x: %f, y: %f\n", obj->planeX, obj->planeY);
  // printf("x: %f, y: %f\n", obj->player_direction_x, obj->player_direction_y);
  double moveSpeed = 0.1; //the constant value is in squares/second
  double rotSpeed = 0.05; // speed rotation
  if (keycode == 53)
      exit(1);
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
  obj->window.img = mlx_new_image(obj->mlx, screenWidth, screenHeight);
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

int main()
{
    int fd = open("map.cub", O_RDONLY);
    t_object_on_scene objects;
    objects.map = manage_function(fd, &objects.s_value_from_map);

    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, screenWidth, screenHeight, "Cube3D");
    int h = screenHeight;
    int w = screenWidth;
    // while (img[i][j])
    // {
    //   while ()
    //   {

    //   }
    // }
    // new
    // unsigned int buffer[screenHeight][screenWidth];
    // int texture[8][texWidth * texHeight];

    // unsigned int **buffer = malloc(screenHeight);
    // for (int i = 0; i < screenHeight; i++)
    //   buffer[i] = malloc(texWidth * sizeof(unsigned int));
    // int **texture = malloc(8 * sizeof(int));
    // for (int i = 0; i < 8 ; i++)
    //   texture[i] = malloc(texWidth * texHeight);


    // objects.buffer = buffer;
    // objects.texture = texture;
    // t_info_image window;
    objects.player_position_x = 22;
    objects.player_position_y = 12;  //x and y start position
    int i = 0;
    int j = 0;
    while (objects.map[i] != NULL)
    {
      while (objects.map[i][j] != '\0')
      {
        if (objects.map[i][j] == 'N' || objects.map[i][j] == 'W' || objects.map[i][j] == 'E'
          || objects.map[i][j] == 'S')
        {
          objects.player_position_x = i;
          objects.player_position_y = j;
          objects.cardinal_point = objects.map[i][j];
        }
        j++;
      }
      i++;
      j = 0;
    }
    objects.map[(int)(objects.player_position_x)][(int)(objects.player_position_y)] = '0';
    printf("x: %f, y: %f\n", objects.player_position_x, objects.player_position_y);
    // objects.player_direction_x = 0;
    // objects.player_direction_y = 1; //initial direction vector
    // objects.planeX = 0.66;
    // objects.planeY = 0; //the 2d raycaster version of camera plane
    cardinal_points(&objects);
    char *relative_path = objects.s_value_from_map.south_texture;
    int wid;
    int height;
    void *img = mlx_xpm_file_to_image(mlx, relative_path, &wid, &height);
    objects.speed = 5;
    objects.mlx = mlx;
    objects.win = win;
    objects.window.img = mlx_new_image(mlx, w, h);
       objects.window.addr = mlx_get_data_addr(objects.window.img, &objects.window.bits_per_pixel,
           &objects.window.line_length, &objects.window.endian);

       objects.texture.addr = mlx_get_data_addr(img, &objects.texture.bits_per_pixel,
           &objects.texture.line_length, &objects.texture.endian);
           write(1, "1", 1);
    rebuild_scene(&objects);
    mlx_put_image_to_window(mlx, win, objects.window.img, 0, 0);
    // mlx_loop_hook(mlx, rebuild_scene, &objects);
    mlx_hook(win, 2, 1L << 0, key_hook, &objects);
    mlx_loop(objects.mlx);
}
