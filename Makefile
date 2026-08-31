VPATH = src/client:src/server:include

EXEC1 = server
EXEC2 = client
HEADER = minitalk.h

SRCS1 =		server.c	\
			utils.c		\

SRCS2 = 	client.c	\

LIBFT_DIR = libft/
LIBFT_NAME = $(LIBFT_DIR)libft.a

CC = cc
FLAGS = -Wall -Werror -Wextra -I include -g3

OBJS_DIR = .obj/
OBJS1 = $(SRCS1:%.c=$(OBJS_DIR)%.o)
OBJS2 = $(SRCS2:%.c=$(OBJS_DIR)%.o)
OBJS = $(OBJS1) $(OBJS2)

.PHONY: all
all: $(EXEC1) $(EXEC2)

$(OBJS_DIR)%.o: %.c $(HEADER) Makefile $(LIBFT_NAME)
	@mkdir -p $(OBJS_DIR)
	@echo "$(MAGENTA)$(BOLD)[Compiling...]$(RESET) $<"
	@$(CC) $(FLAGS) -c $< -o $@

$(LIBFT_NAME): force
	@$(MAKE) -sC $(LIBFT_DIR)

$(EXEC1): Makefile $(HEADER) $(OBJS1) $(LIBFT_NAME)
	@$(CC) $(FLAGS) $(OBJS1) -L$(LIBFT_DIR) $(LIBFT_NAME) -o $(EXEC1)
	@echo "$(GREEN)$(BOLD)\nCompilation successful!$(RESET)"
	@echo "$(CYAN)  └─ Ready to run: ./$(EXEC1)\n$(RESET)"

$(EXEC2): Makefile $(HEADER) $(OBJS2) $(LIBFT_NAME)
	@$(CC) $(FLAGS) $(OBJS2) -L$(LIBFT_DIR) $(LIBFT_NAME) -o $(EXEC2)
	@echo "$(GREEN)$(BOLD)\nCompilation successful!$(RESET)"
	@echo "$(CYAN)  └─ Ready to run: ./$(EXEC2)\n$(RESET)"

.PHONY: clean
clean:
	@rm -rf $(OBJS_DIR) $(OBJS)
	@$(MAKE) clean -sC $(LIBFT_DIR)
	@echo "$(RED)$(BOLD)\nCleaning up project files...$(RESET)"
	@echo "$(YELLOW)  ├─ Removing object files$(RESET)"
	@echo "$(YELLOW)  └─ Cleaning libft$(RESET)"

.PHONY: fclean
fclean: clean
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	@$(RM) $(EXEC1) $(EXEC2)
	@echo "$(RED)$(BOLD)\nFull clean-up completed:$(RESET)"
	@echo "$(YELLOW)  ├─ Removed object files and directories$(RESET)"
	@echo "$(YELLOW)  ├─ Cleaned libft$(RESET)"
	@echo "$(YELLOW)  └─ Deleted executables: $(EXEC1), $(EXEC2)\n$(RESET)"

.PHONY: re
re: fclean all

.PHONY: force
force:
	@true

# **** COLORS **** #

BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m
BOLD = \033[1m
RESET = \033[0m
