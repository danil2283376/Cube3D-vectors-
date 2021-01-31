SRC = $(shell find . -name "ft_*.c") get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c cube3D.c

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
