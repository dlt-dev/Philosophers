# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/18 12:49:25 by jdelattr          #+#    #+#              #
#    Updated: 2025/12/18 12:52:47 by jdelattr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

CC = cc
CFLAGS = -Werror -Wall -Wextra -g3
RM = rm -rf

SRCS = srcs/main.c srcs/utils.c
SRCS_BONUS =

OBJS = $(SRCS:srcs/%.c=.obj/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	make all -C libft
	$(CC) $(CFLAGS) $(OBJS) -Iincludes libft/libft.a -o $(NAME)

.obj/%.o: srcs/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@
	
fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

clean:
	$(RM) .obj
	make clean -C libft

re: fclean all

bonus: 
	make all -C libft
	$(CC) $(CFLAGS) $(SRCS_BONUS) libft/libft.a -o $(NAME)
	
.PHONY: all clean fclean re bonus
