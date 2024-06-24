NAME		:= miniRT
CFLAGS		:= -mavx -Wunreachable-code -Ofast -g
LIBMLX		:= ./MLX42
LIB			:= ./Lib
CC			:= cc
# LSAN	:= -LLeakSanitizer -llsan

OBJ_DIR	=	./objs/
HEADERS	:= -I ./include -I $(LIB)/Libft -I $(LIBMLX)/include
LIB_M		:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS		:= $(wildcard src/*.c \
						src/vector/simd/*.c \
						src/objects/*.c \
						src/graphics/*.c \
						src/parsing/*.c \
						src/init/*.c \
						src/cleanup/*.c \
						src/utils/*.c)
OBJS		:= $(patsubst src/%.c,$(OBJ_DIR)src/%.o,$(SRCS))

all: libft libmlx $(NAME)

libft:
	@make -C $(LIB)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4 

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIB)/lib.a $(LIB_M) $(HEADERS) -o $(NAME)

$(OBJ_DIR)src/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)...\n"

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build
	@make --directory=Lib/ clean

fclean: clean
	@rm -rf $(NAME)
	@make --directory=Lib/ fclean
	
re: clean all

.PHONY: all clean fclean re libmlx libft
