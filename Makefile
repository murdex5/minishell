# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kadferna <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/16 18:09:13 by kadferna          #+#    #+#              #
#    Updated: 2025/09/16 18:09:16 by kadferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



# =========================
# Color and Formatting
# =========================
ifneq (,$(findstring xterm,${TERM}))
	BOLD    := \033[1m
	RED     := \033[31m
	GREEN   := \033[32m
	YELLOW  := \033[33m
	BLUE    := \033[34m
	MAGENTA := \033[35m
	CYAN    := \033[36m
	WHITE   := \033[37m
	RESET   := \033[0m
else
	BOLD    := ""
	RED     := ""
	GREEN   := ""
	YELLOW  := ""
	BLUE    := ""
	MAGENTA := ""
	CYAN    := ""
	WHITE   := ""
	RESET   := ""
endif

# =========================
# Project Configuration
# =========================
NAME        := minishell
CC          := gcc
CFLAGS      := -Wall -Werror -Wextra
LDFLAGS     := -lreadline -lncurses
LIBFT_PATH  := ./libft
LIBFT_LIB   := $(LIBFT_PATH)/libft.a
HEADER      := minishell.h

# =========================
# Source Files
# =========================
SRCS_DIR    := ./srcs
SRCS        := \
	$(SRCS_DIR)/utils0.c \
	$(SRCS_DIR)/utils1.c \
	$(SRCS_DIR)/exec/exec_utils1.c \
	$(SRCS_DIR)/exec/exec_utils.c \
	$(SRCS_DIR)/exec/exec_builtins.c \
	$(SRCS_DIR)/exec/exec.c \
	$(SRCS_DIR)/lexer/free_lexer.c \
	$(SRCS_DIR)/lexer/lexer_utils.c \
	$(SRCS_DIR)/lexer/lexer.c \
	$(SRCS_DIR)/parsing/parse_helper.c \
	$(SRCS_DIR)/parsing/parse_utils.c \
	$(SRCS_DIR)/parsing/parsing.c \
	$(SRCS_DIR)/signals/signals.c \
	$(SRCS_DIR)/errors/errors.c \
	$(SRCS_DIR)/errors/errors1.c \
	$(SRCS_DIR)/closes.c \
	$(SRCS_DIR)/free/frees2.c \
	$(SRCS_DIR)/free/frees1.c \
	$(SRCS_DIR)/free/frees.c \
	$(SRCS_DIR)/check_bltn.c \
	$(SRCS_DIR)/bltn_funcs/echo/ft_echo_utils2.c \
	$(SRCS_DIR)/bltn_funcs/echo/ft_echo_utils1.c \
	$(SRCS_DIR)/bltn_funcs/echo/ft_echo_utils.c \
	$(SRCS_DIR)/bltn_funcs/echo/ft_echo.c \
	$(SRCS_DIR)/bltn_funcs/cd/ft_cd.c \
	$(SRCS_DIR)/bltn_funcs/pwd/ft_pwd.c \
	$(SRCS_DIR)/bltn_funcs/env/ft_env.c \
	$(SRCS_DIR)/bltn_funcs/unset/ft_unset_utils.c \
	$(SRCS_DIR)/bltn_funcs/unset/ft_unset.c \
	$(SRCS_DIR)/bltn_funcs/export/ft_export_utils.c \
	$(SRCS_DIR)/bltn_funcs/export/ft_export.c \
	$(SRCS_DIR)/bltn_funcs/expand_vars/ft_expand_vars.c \
	$(SRCS_DIR)/bltn_funcs/exit/ft_exit.c \
	$(SRCS_DIR)/shell/ft_shell.c \
	main.c

OBJS        := $(SRCS:.c=.o)

# =========================
# Build Targets
# =========================
all: libft $(NAME)
	@echo "$(GREEN)✔ $(BOLD)Minishell ready!$(RESET)"
	@echo "Run with: $(BOLD)./$(NAME)$(RESET)"

libft:
	@echo "$(BLUE)🔧 Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory

$(NAME): $(OBJS) $(LIBFT_LIB)
	@echo "$(BLUE)🔗 $(BOLD)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(BOLD)Executable created: $(NAME)$(RESET)"

%.o: %.c $(HEADER)
	@echo "$(CYAN)🛠  Compiling $(notdir $<)...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# =========================
# Clean Rules
# =========================
clean:
	@echo "$(YELLOW)♻  Cleaning object files...$(RESET)"
	@rm -f $(OBJS)

fclean: clean
	@echo "$(RED)🧹 Deep cleaning...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory
	@echo "$(GREEN)✓ $(BOLD)Project fully cleaned!$(RESET)"

re: fclean all

valgrind: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.supp ./$(NAME)

.PHONY: all clean fclean re libft valgrind
