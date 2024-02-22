# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/28 15:25:32 by vsharma           #+#    #+#              #
#    Updated: 2024/02/21 18:22:41 by vsharma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

NAME = philo
HEADER = philo.h
BLUE = \033[34m
SRCS = main.c input_validation.c utils.c monitor.c \
		start_simulation.c eating.c sleeping.c thinking.c init_data.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "$(BLUE) Executable $(NAME) has been successfully built."

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)


re: fclean $(NAME)

.PHONY: clean fclean re