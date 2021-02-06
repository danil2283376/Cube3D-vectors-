SRC = $(shell find . -name "ft_*.c") get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c cube3D.c validate_map/valide_settings.c \
	validate_map/valide_map.c validate_keys/validate_file_cub.c raycasting/raycast.c \
	raycasting/draw_scene.c draw_sprite/translate_sprite_pos.c draw_sprite/calculate_pos_sprite.c \
	draw_sprite/output_vertical_line_sprite.c key_events/key_hook.c key_events/move.c \
	key_events/rotation.c transform_pixel/transform_color.c transform_pixel/my_mlx_pixel.c \
	transform_pixel/take_pixel_from_texture.c screenshot_engine/screenshot.c \
	standart_value_struct/standart_value_map.c standart_value_struct/take_position_player.c \
	standart_value_struct/cardinal_points.c draw_sprite/miscalculation_distance.c \
	draw_sprite/sorting_sprite.c draw_sprite/draw_sprite.c draw_sprite/quantity_sprite.c \
	draw_sprite/search_sprite_in_map.c


OBJC = ${SRS:.c=.o}

NAME = cube3D.a

FLAG = -Wall -Wextra -Werror

OBJC = ${SRC:.c=.o}

GCC = gcc

.c.o:
	${GCC} ${FLAG} -I. -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJC} libmlx.dylib
	ar rc ${NAME} ${OBJC}

bonus: all

clean:
	rm -f ${OBJC}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
