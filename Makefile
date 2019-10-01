# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/22 15:11:00 by iel-bouh          #+#    #+#              #
#    Updated: 2019/09/30 14:47:19 by iel-bouh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC  = builtin.c dolar.c env.c free.c\
		 main.c parce_exec.c cd.c built_env.c utile.c parcing.c tilde.c
C       = gcc
CFLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
		@make -C libft
		@$(C) $(CFLAGS) libft/libft.a $(OBJ) -o $(NAME)

%.o	: %.c
		$(C) $(CFLAGS)  -o $@ -c $<

clean	:
		@make clean -C libft
		@rm -rf $(OBJ)

fclean	: clean
		@make fclean -C libft
		@rm -f $(NAME)

re	: fclean all