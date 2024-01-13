# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clundber <clundber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 11:59:53 by clundber          #+#    #+#              #
#    Updated: 2024/01/13 11:30:43 by clundber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------ PROJECT -------#
NAME = pipex
LIBFTNAME = libft.a
# ------------ DIRECTORIES ---#
LIBFT_DIR = ./libft

#------------- SOURCE FILES ------#
CFILES = pipex.c

OFILES = $(CFILES:.c=.o)

#--------- FLAGS ----------#

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I includes

all: $(NAME)

$(NAME): $(OFILES)
	@make -C libft
	$(CC) $(CFLAGS) $(OFILES) $(LIBFT_DIR)/$(LIBFTNAME) -o $(NAME)
	
clean:
	rm -f $(OFILES) 
	@make clean -C libft/

fclean: clean
	rm -f $(NAME) 
	@make fclean -C libft

re: fclean $(NAME) 

.PHONY: all clean fclean re