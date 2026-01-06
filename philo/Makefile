# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/18 12:49:25 by jdelattr          #+#    #+#              #
#    Updated: 2026/01/06 21:28:53 by jdelattr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Werror -Wall -Wextra -g3
RM = rm -rf

INCLUDES = Header

SRCS = \
	Srcs/main.c \
	Srcs/utils.c \
	Srcs/routine.c \
	Srcs/init.c

SRCS_BONUS =

OBJS = $(SRCS:Srcs/%.c=.obj/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDES) -o $(NAME)

.obj/%.o: Srcs/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@
	
fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) .obj

re: fclean all

bonus:
	$(CC) $(CFLAGS) $(SRCS_BONUS) -I$(INCLUDES) -o $(NAME)
	
.PHONY: all clean fclean re bonus
