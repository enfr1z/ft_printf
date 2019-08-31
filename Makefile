# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/11 19:11:06 by vsanta            #+#    #+#              #
#    Updated: 2019/07/01 16:17:23 by vsanta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= libftprintf.a
NAME_LIB 		= libft/libft.a

INC_DIR 		= ./includes/
SRC_DIR 		= ./src/
OBJ_DIR 		= ./obj/

SRC_NAME 		= ft_printf.c parse_flags.c utils.c utils_float.c \
					utils_float_ldb.c write.c write_float.c write_int.c \
					write_percent.c write_unsigned.c init.c round_float.c \
					utils_flags.c utils_float_lda.c utils_int.c write_char.c \
					write_hex.c write_oct.c write_pointer.c utils_hex_oct.c 

OBJ_NAME 		= $(SRC_NAME:.c=.o)

SRC 			= $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJ 			= $(addprefix $(OBJ_DIR), $(OBJ_NAME))

FLAGS 			= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_DIR) $(NAME_LIB) $(OBJ)
	@cp $(NAME_LIB) $(NAME)
	@ar rc $(NAME) $(OBJ)

$(OBJ_DIR):
	@mkdir -p obj

$(NAME_LIB):
	@make -C libft/

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	gcc -c -I $(INC_DIR) -I libft/includes/ $(FLAGS) $< -o $@

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@make clean -C libft/

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft/

re: fclean all