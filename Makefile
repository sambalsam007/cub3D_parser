# project name and compilation settings
NAME        = cub3D

CC          = cc
CFLAGS      = -g3 -Wall -Werror -Wextra
MAKEFLAGS   += -s
PFLAGS		= -l Xext -l X11 -lm

# directories
SRC_DIR     = ./sources
LIBFT_DIR   = ./sources/libft
MLX_DIR		= ./sources/minilibx-linux

# source and object files
SRC_FILES = $(SRC_DIR)/main.c \
			$(SRC_DIR)/init.c \
			$(SRC_DIR)/parsing.c \
			$(SRC_DIR)/map_check.c \
			$(SRC_DIR)/close.c \
			$(SRC_DIR)/utils.c

OBJ_FILES        = $(SRC_FILES:.c=.o)

# libraries
LIBFT       = $(LIBFT_DIR)/libft.a
LIBMLX		= $(MLX_DIR)/libmlx.a

# define colors
MAGENTA = \033[1;35m
YELLOW  = \033[1;33m
GREEN   = \033[1;32m
GREENBLUE = \033[1;36m
RESET   = \033[0m

# ---------------------------------------------------------------------------- #
#                              Build Targets                                   #
# ---------------------------------------------------------------------------- #

all: $(LIBFT) $(LIBMLX) $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT) $(LIBMLX)
	@echo "$(MAGENTA)Using compiler: $(CC)$(RESET)"
	@echo "$(MAGENTA)Using flags: $(CFLAGS) $(PROJECTFLAGS) $(RESET)"
	@echo "$(GREENBLUE)Linking $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(LIBMLX) $(PFLAGS) -o $(NAME)
	@echo "$(GREEN)Compilation successful!$(RESET)"

# Rule to build object files for normal build
%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -I $(SRC_DIR) -c $< -o $@

# Libmlx build
$(LIBMLX):
	@echo "$(GREENBLUE)Building libmlx$(RESET)"
	$(MAKE) -C $(MLX_DIR)
	@echo "$(GREEN)Libmlx compiled succesfully!$(RESET)"

# Libft build
$(LIBFT):
	@echo "$(GREENBLUE)Building libft...$(RESET)"
	$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft compiled successfully!$(RESET)"

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@rm -f $(OBJ_FILES) $(DEBUG_OBJ_FILES)
	$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@echo "$(GREEN)Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(YELLOW)Removing $(NAME) and $(DEBUG_NAME) executables...$(RESET)"
	@rm -f $(NAME) $(DEBUG_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)Executables removed!$(RESET)"

re: fclean all 

.PHONY: all clean fclean re debug both
