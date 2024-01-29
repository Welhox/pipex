# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clundber <clundber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 11:59:53 by clundber          #+#    #+#              #
#    Updated: 2024/01/29 13:10:44 by clundber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

# ------------ PROJECT -------#
NAME = pipex
LIBFTNAME = libft.a
# ------------ DIRECTORIES ---#
LIBFT_DIR = ./libft

#------------- SOURCE FILES ------#
CFILES = pipex.c pipex_utils.c pipex_utils2.c

OFILES = $(CFILES:.c=.o)

#--------- FLAGS ----------#

CC = @cc
CFLAGS = -Wall -Wextra -Werror -g -I includes

all: $(NAME)

$(NAME): $(OFILES)
	@echo "$(COLOUR_BLUE)compiling pipex$(COLOUR_END)"
	@make -C libft
	$(CC) $(CFLAGS) $(OFILES) $(LIBFT_DIR)/$(LIBFTNAME) -o $(NAME)
	@echo "$(COLOUR_GREEN)pipex compiled successfully$(COLOUR_END)"
clean:
	@echo "$(COLOUR_GREEN)cleaning pipex$(COLOUR_END)"
	@rm -f $(OFILES) 
	@make clean -C libft/

fclean: clean
	@rm -f $(NAME) 
	@rm -f libft/libft.a

re: fclean $(NAME) 

.PHONY: all clean fclean re