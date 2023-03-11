CC = gcc
FLAGS = -Wall -Wextra -Werror

FILE_NAME = fractol
MLX = -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(shell find . -name "*.c")
OBJS = $(subst $(SRC_DIR),$(OBJ_DIR), $(SRCS:.c=.o))

INCLUDE = -I ./include/

RM = rm -rf

# Colors
RESET  = \033[0m
RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m


all: $(FILE_NAME)

bonus: all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

# %.o: %.c | $(OBJDIR)
# 	@echo "$(YELLOW)Compiling $<...$(RESET)"
# 	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(FILE_NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(FILE_NAME)...$(RESET)"
	@$(CC) $(FLAGS) $(INCLUDE) $^ $(MLX) -o $(FILE_NAME)
	@echo "$(GREEN)Done!$(RESET)"


clean:
	@echo "$(RED)Cleaning...$(RESET)"
	@$(RM) $(OBJS)
	@echo "$(GREEN)Done!$(RESET)"

fclean: clean
	@echo "$(RED)Removing out file...$(RESET)"
	@$(RM) $(FILE_NAME)
	@echo "$(GREEN)Done!$(RESET)"

re: fclean all