# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clundber <clundber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 11:59:53 by clundber          #+#    #+#              #
#    Updated: 2024/01/13 15:10:45 by clundber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ------------ PROJECT -------#
NAME = libft.a

# ------------ DIRECTORIES ---#
SRC_DIR = srcs
LIBFT_DIR = srcs/libft
FT_PRINTF_DIR = srcs/ft_printf
GNL_DIR = srcs/get_next_line

#------------- SOURCE FILES ------#

SRC_FLS = $(LIBFT_FLS) $(FT_PRINTF_FLS) $(GNL_FLS)

LIBFT_FLS = $(LIBFT_DIR)/ft_atoi.c $(LIBFT_DIR)/ft_strlen.c $(LIBFT_DIR)/ft_bzero.c $(LIBFT_DIR)/ft_calloc.c $(LIBFT_DIR)/ft_isalnum.c \
		$(LIBFT_DIR)/ft_isalpha.c $(LIBFT_DIR)/ft_isascii.c $(LIBFT_DIR)/ft_isdigit.c $(LIBFT_DIR)/ft_isprint.c $(LIBFT_DIR)/ft_memchr.c \
		$(LIBFT_DIR)/ft_memcmp.c $(LIBFT_DIR)/ft_memcpy.c $(LIBFT_DIR)/ft_memmove.c $(LIBFT_DIR)/ft_memset.c $(LIBFT_DIR)/ft_putchar_fd.c \
		$(LIBFT_DIR)/ft_putendl_fd.c $(LIBFT_DIR)/ft_putnbr_fd.c $(LIBFT_DIR)/ft_putstr_fd.c $(LIBFT_DIR)/ft_strchr.c $(LIBFT_DIR)/ft_strdup.c \
		$(LIBFT_DIR)/ft_strjoin.c $(LIBFT_DIR)/ft_strlcat.c $(LIBFT_DIR)/ft_strlcpy.c $(LIBFT_DIR)/ft_strlen.c $(LIBFT_DIR)/ft_strncmp.c \
		$(LIBFT_DIR)/ft_strnstr.c $(LIBFT_DIR)/ft_strrchr.c $(LIBFT_DIR)/ft_strtrim.c $(LIBFT_DIR)/ft_substr.c $(LIBFT_DIR)/ft_tolower.c \
		$(LIBFT_DIR)/ft_toupper.c $(LIBFT_DIR)/ft_itoa.c $(LIBFT_DIR)/ft_strmapi.c $(LIBFT_DIR)/ft_split.c $(LIBFT_DIR)/ft_striteri.c \
		$(LIBFT_DIR)/ft_lstnew_bonus.c $(LIBFT_DIR)/ft_lstadd_front_bonus.c $(LIBFT_DIR)/ft_lstsize_bonus.c \
		$(LIBFT_DIR)/ft_lstlast_bonus.c $(LIBFT_DIR)/ft_lstadd_back_bonus.c $(LIBFT_DIR)/ft_lstdelone_bonus.c\
		$(LIBFT_DIR)/ft_lstclear_bonus.c $(LIBFT_DIR)/ft_lstiter_bonus.c $(LIBFT_DIR)/ft_lstmap_bonus.c

FT_PRINTF_FLS = $(FT_PRINTF_DIR)/ft_printf.c $(FT_PRINTF_DIR)/ft_printhex.c $(FT_PRINTF_DIR)/ft_putnbr_return.c \
		$(FT_PRINTF_DIR)/ft_putstr_return.c $(FT_PRINTF_DIR)/ft_putnbr_u_return.c $(FT_PRINTF_DIR)/ft_putchar_return.c

GNL_FLS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

OFILES = $(SRC_FLS:.c=.o)

#--------- FLAGS ----------

cc = cc
CFLAGS = -Wall -Wextra -Werror -I includes

all: $(NAME)

$(NAME): $(OFILES)

	ar rcs $(NAME) $(OFILES)

clean:
	rm -f $(OFILES) 

fclean: clean
	rm -f $(NAME) 
	
re: fclean $(NAME) 

.PHONY: all clean fclean re