RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
NC=\033[0m

NAME = minishell

SRC = src/Main/main.c \
src/Builtin/cd.c src/Builtin/env.c src/Builtin/exit.c src/Builtin/pwd.c src/Builtin/unset.c \
src/Builtin/export/export_args.c src/Builtin/export/export_clone.c src/Builtin/export/export_handle.c src/Builtin/export/export_print.c src/Builtin/export/export_split.c src/Builtin/export/export_syntax.c src/Builtin/export/export_update.c src/Builtin/export/export.c \
src/Builtin/echo/echo_arguments.c src/Builtin/echo/echo_quotes.c src/Builtin/echo/echo_utils.c src/Builtin/echo/echo.c \
src/Cleanup/free_cloned_list.c src/Cleanup/free_cmd_struct.c src/Cleanup/free_data.c src/Cleanup/free_envv_struct.c src/Cleanup/free_everything.c src/Cleanup/free_input.c src/Cleanup/free_tokens.c src/Cleanup/minishell_error_exit.c \
src/Envvar/expand_envvar.c src/Envvar/handle_vars.c src/Envvar/envvar_utils.c src/Envvar/envvar_utils2.c \
src/Execute/cmd_is_builtin.c src/Execute/cmd_path.c src/Execute/convert_envvar_to_array.c src/Execute/execute_builtin.c src/Execute/exec_cmd_builtin.c src/Execute/exec_commands.c src/Execute/exec_pipeline.c src/Execute/put_args_in_array.c src/Execute/exec_utils.c src/Execute/exec_utils2.c src/Execute/handle_redirections.c \
src/Get_input/input.c \
src/init/init.c src/init/clone_env_to_duplist.c \
src/Lexer/add_token_to_list.c src/Lexer/handle_meta_chars.c src/Lexer/add_token_utils.c \
src/Parse/commands_processing.c src/Parse/handle_redirections.c src/Parse/parse_utils.c src/Parse/process_fds.c src/Parse/process_input.c src/Parse/commands_initialisation.c src/Parse/redirections_utils.c src/Parse/parse_utils2.c \
src/Signals/signals.c \
src/Lib_utils/lib_utils.c src/Lib_utils/lib_utils2.c src/Lib_utils/list_utils2.c src/Lib_utils/error_free_utils.c src/Lib_utils/list_utils.c src/Lib_utils/malloc_utils.c src/Lib_utils/moded_split.c

OBJ_DIR = objets
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

LFT_DIR = ./Libft
LFT_LIB = $(LFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wextra -Wall -Werror -g
READLINE_DIR = $(shell brew --prefix readline)
READLINE_INCLUDE = -I$(READLINE_DIR)/include
READLINE_LIB = -L$(READLINE_DIR)/lib -lreadline

all: $(LFT_LIB) $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Compilation de $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) -L$(LFT_DIR) -lft $(READLINE_LIB) -o $(NAME)
	@echo "$(GREEN)$(NAME) compilé avec succès.$(NC)"

debug: $(OBJ)
	@echo "$(RED)Compilation pour le debug, avec fsanitize...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) -g -fsanitize=address -L$(LFT_DIR) -lft $(READLINE_LIB) -o $(NAME)

$(LFT_LIB):
	@echo "$(YELLOW)Compilation de la Libft...$(NC)"
	@$(MAKE) -C $(LFT_DIR)
	@echo "$(GREEN)Libft compilée avec succès.$(NC)"

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(READLINE_INCLUDE) -I$(LFT_DIR) -Iincludes -c $< -o $@

clean:
	@echo "$(RED)Suppression des objets...$(NC)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LFT_DIR) clean
	@echo "$(GREEN)Suppression terminée.$(NC)"

fclean:
	@echo "$(RED)Nettoyage complet en cours...$(NC)"
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@$(MAKE) -C $(LFT_DIR) fclean
	@echo "$(GREEN)Nettoyage terminé et executable supprimé.$(NC)"

re: fclean all

norme:
	@echo "$(RED)Lancement de la commande Norminette$(NC)"
	@norminette -R CheckForbiddenSourceHeader $(SRC)

leaks:
	@echo "$(RED)Recherche de leaks...$(NC)"
	leaks -atExit -- ./$(NAME)

.PHONY: clean norme fclean re all debug leaks