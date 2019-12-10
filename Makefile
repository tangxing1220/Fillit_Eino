# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elindber <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 19:39:02 by elindber          #+#    #+#              #
#    Updated: 2019/12/09 14:48:16 by elindber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = *.c

LIB = ./libft/libft.a

all: $(NAME)

$(NAME):
	@ gcc -o $(NAME) $(SRC) $(LIB)
	@ echo compiled and executable created
	@ echo READY TO ROLL

clean:
	@ /bin/rm -f *.o
	@ echo dummy clean done

fclean: clean
	@ /bin/rm $(NAME)
	@ echo executable removed

re: fclean all
