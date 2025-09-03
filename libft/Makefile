# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kadferna <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/18 15:37:19 by kadferna          #+#    #+#              #
#    Updated: 2024/12/18 15:37:23 by kadferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# =========================
# Color and Formatting
# =========================
ifneq (,$(findstring xterm,${TERM}))
	BOLD    := \033[1m
	GREEN   := \033[32m
	BLUE    := \033[34m
	CYAN    := \033[36m
	YELLOW  := \033[33m
	RED     := \033[31m
	RESET   := \033[0m
	CHECK   := ✓
	WRENCH  := 🛠 
	LIB     := 📦
	CLEAN   := ♻
else
	BOLD    := ""
	GREEN   := ""
	BLUE    := ""
	CYAN    := ""
	YELLOW  := ""
	RED     := ""
	RESET   := ""
	CHECK   := "[✓]"
	WRENCH  := "[*]"
	LIB     := "[lib]"
	CLEAN   := "[clean]"
endif

# =========================
# Project Configuration
# =========================
NAME        := libft.a
CC          := gcc
CFLAGS      := -Wall -Wextra -Werror
SRC_COUNT   := $(words $(SRCS))

# =========================
# Source Files
# =========================
SRCS        := \
	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
	ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_putnbr_base.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS        := $(SRCS:.c=.o)

# =========================
# Build Targets
# =========================
all: $(NAME)
	@printf "$(GREEN)$(CHECK) $(BOLD)Libft compilation complete$(RESET)\n"

$(NAME): $(OBJS)
	@printf "$(BLUE)$(LIB) Creating $(NAME)...$(RESET)\n"
	@ar rcs $(NAME) $(OBJS)
	@printf "$(GREEN)$(CHECK) $(BOLD)%d files compiled into $(NAME)$(RESET)\n" $(words $(OBJS))

# Silent compilation rule (no per-file output)
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(CYAN)$(WRENCH) Compiled %-20s$(RESET)\r" $(notdir $<)

clean:
	@printf "$(YELLOW)$(CLEAN) Cleaning object files...$(RESET)\n"
	@rm -f $(OBJS)

fclean: clean
	@printf "$(RED)$(CLEAN) Removing $(NAME)...$(RESET)\n"
	@rm -f $(NAME)
	@printf "$(GREEN)$(CHECK) $(BOLD)Libft fully cleaned!$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
