CC = gcc
FLAGS = -Wall -Wextra -Werror

FILE_NAME = fractol
MLX = -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

SRCS = $(shell find  *.c)
OBJS_MAN = $(patsubst %.c,%.o,$(SRCS))

INCLUDE = -I ./include/

RM = rm -rf

# Colors
RESET  = \033[0m
RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m


all: $(FILE_NAME)


%.o: %.c | $(OBJDIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(FILE_NAME): $(OBJS_MAN)
	@echo "$(YELLOW)Linking $(FILE_NAME)...$(RESET)"
	@$(CC) $(FLAGS) $(INCLUDE) $^ $(MLX) -o $(FILE_NAME)
	@echo "$(GREEN)Done!$(RESET)"


clean:
	@echo "$(RED)Cleaning...$(RESET)"
	@$(RM) $(OBJS_MAN) $(OBJS_BONUS)
	@echo "$(GREEN)Done!$(RESET)"

fclean: clean
	@echo "$(RED)Removing out file...$(RESET)"
	@$(RM) $(FILE_NAME)
	@echo "$(GREEN)Done!$(RESET)"

re: fclean all