# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/31 17:34:05 by davidga2          #+#    #+#              #
#    Updated: 2023/09/05 22:47:36 by davidga2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = src/pipex.c

OBJS = $(SRC:%.c=%.o)

CC = cc -Wall -Wextra -Werror
RM = rm -f

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(SRC) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: clean fclean

.PHONY: all clean fclean re
