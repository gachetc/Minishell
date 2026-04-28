# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ludovicbachmann <ludovicbachmann@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 13:08:34 by lubachma          #+#    #+#              #
#    Updated: 2024/08/14 01:05:43 by ludovicbach      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[1;33m
NC=\033[0m

CC=gcc

CFLAGS=-Wall -Wextra -Werror

SRC=src/ft_isalpha.c src/ft_isdigit.c src/ft_isalnum.c src/ft_isascii.c src/ft_isprint.c src/ft_strlen.c src/ft_memset.c src/ft_bzero.c src/ft_toupper.c src/ft_tolower.c src/ft_strchr.c src/ft_strrchr.c \
	src/ft_strncmp.c src/ft_memchr.c src/ft_memcmp.c src/ft_strlcpy.c src/ft_strlcat.c src/ft_memcpy.c src/ft_memmove.c src/ft_strnstr.c src/ft_atoi.c src/ft_calloc.c src/ft_strdup.c \
	src/ft_substr.c src/ft_strjoin.c src/ft_strtrim.c src/ft_putchar_fd.c src/ft_putstr_fd.c src/ft_putendl_fd.c src/ft_putnbr_fd.c  src/ft_split.c src/ft_itoa.c \
	src/ft_strmapi.c src/ft_striteri.c

SRC_BONUS = src/ft_lstnew_bonus.c src/ft_lstadd_front_bonus.c src/ft_lstsize_bonus.c src/ft_lstlast_bonus.c src/ft_lstadd_back_bonus.c src/ft_lstdelone_bonus.c src/ft_lstclear_bonus.c src/ft_lstiter_bonus.c src/ft_lstmap_bonus.c

SRC_GNL = Get_next_line/get_next_line_bonus.c Get_next_line/get_next_line_utils_bonus.c

SRC_PRINTF = Printf/ft_printf.c Printf/ft_putchar.c Printf/ft_puthex.c Printf/ft_putnbr.c Printf/ft_putptr.c Printf/ft_putstr.c Printf/ft_putunsigned.c

OBJ_DIR = objets
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o) $(SRC_BONUS:src/%.c=$(OBJ_DIR)/%.o) $(SRC_GNL:Get_next_line/%.c=$(OBJ_DIR)/%.o) $(SRC_PRINTF:Printf/%.c=$(OBJ_DIR)/%.o)

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Création de la librairie $(NAME)...$(NC)"
	@ar rcs $(NAME) $(OBJ)
	@echo "$(GREEN)Librairie $(NAME) créée avec succès.$(NC)"

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Iincludes -c $< -o $@

$(OBJ_DIR)/%.o: Get_next_line/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Iincludes -c $< -o $@

$(OBJ_DIR)/%.o: Printf/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	@echo "$(RED)Suppression des objets...$(NC)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Suppression des objets terminée.$(NC)"

fclean: clean
	@echo "$(RED)Nettoyage complet en cours...$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)Nettoyage complet terminé.$(NC)"

re: fclean all

.PHONY: clean fclean re all