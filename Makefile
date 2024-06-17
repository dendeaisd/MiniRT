# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 18:58:12 by fvoicu            #+#    #+#              #
#    Updated: 2024/06/17 14:35:33 by mevangel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= miniRT
CFLAGS		:= -Wunreachable-code -Ofast -g -Wall -Wextra -Werror 
LIBMLX		:= ./MLX42
LIB			:= ./Lib
CC			:= cc
# LSAN	:= -LLeakSanitizer -llsan

HEADERS	:= -I ./include -I $(LIB)/Libft -I $(LIBMLX)/include
LIB_M		:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS		:= $(wildcard src/*.c \
						src/vector/*.c \
						src/objects/*.c \
						src/parsing/*.c \
						src/init/*.c \
						src/cleanup/*.c \
						src/utils/*.c)
OBJS		:= ${SRCS:.c=.o}

all: libft libmlx $(NAME)

libft:
	@make -C $(LIB)

libmlx:
	@if [ ! -d "./MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@cd MLX42 && cmake -B build
	@cd MLX42 && cmake --build build -j4

# $(LIBMLX):
# 	@if [ ! -d "./MLX42" ]; then cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4; fi

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)..."

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIB)/lib.a $(LIB_M) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make --directory=Lib/ clean

fclean: clean
	@rm -rf $(NAME)
	@make --directory=Lib/ fclean
	
re: clean all

.PHONY: all, clean, fclean, re, libmlx