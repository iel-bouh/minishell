# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iel-bouh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/08 14:55:14 by iel-bouh          #+#    #+#              #
#    Updated: 2018/10/12 16:47:51 by iel-bouh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

all : $(NAME)

$(NAME):
	@gcc -Wall -Werror -Wextra -c *.c
	@ar rc $(NAME) *.o 

clean :
	@rm -f *.o

fclean : clean
	@rm -f $(NAME)

re : fclean all
