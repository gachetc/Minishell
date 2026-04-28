#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>
# include <termios.h>

// signal
# include <signal.h>

// sys
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/resource.h>
# include <sys/stat.h>

// error
# include <errno.h>

// readline
# include <readline/readline.h>
# include <readline/history.h>

//*********** Libs ***********//
# include "../Libft/includes/ft_printf.h"
# include "../Libft/includes/get_next_line_bonus.h"
# include "../Libft/includes/libft.h"

//*********** Colors ***********//
# define DEF	"\033[0m"
# define GRAY	"\033[1;30m"
# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[1;34m"
# define MGNTA	"\033[1;35m"
# define CYAN	"\033[1;36m"
# define WHITE	"\033[1;37m"

//*********** Define ***********//
# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1

//*********** Structs ***********//
typedef struct s_envv
{
	char				*env_key;
	char				*env_value;
	int					is_exported;
}				t_envv;

typedef struct s_cmd
{
	char				*command;
	t_list				*arguments;
	char				*input_file;
	char				*output_file;
	int					in_fd;
	int					out_fd;
	bool				is_append;
	char				*heredoc_delimiter;
	char				*heredoc_data;
	bool				is_grep;
}				t_cmd;

typedef struct s_shell
{
	t_list				*envvar;
	char				*input;
	t_list				*tokens;
	t_list				*cmd_queue;
	int					num_of_cmds;
	t_list				*pids;
	struct sigaction	sigactions;
	sigset_t			sigset;
	struct termios		original_termios;
	struct termios		updated_termios;
	int					last_exit_status;
	bool				contains_echo;
	bool				quotes_closed;
	bool				in_single_quote;
	bool				in_double_quote;
	int					original_stdin;
	int					original_stdout;
	bool				contains_pipe;
	bool				contains_export;
	bool				is_heredoc;
	char 				first_quote;
	char				*no_quote;
}				t_shell;

typedef struct s_exec_params
{
	t_shell				*shell;
	t_cmd				*cmd;
	int					**pipes;
	int					num_pipes;
	int					cmd_index;
	int					num_cmds;
}	t_exec_params;

//*********** Builtin ***********//

// cd.c
int				ft_cd(t_shell *shell, t_cmd *cmd_struct);

// echo.c
int				ft_echo(t_shell *shell, t_cmd *cmd);
void			process_arguments(t_shell *shell, t_cmd *cmd, char **result, \
bool *print_newline);
bool			initialize_echo(t_shell *shell, t_cmd *cmd, \
bool *print_newline, char **result);

//echo_quotes.c
void			handle_quotes(char c, t_shell *shell);
char			*process_character(char c, char *arg, size_t *i, \
t_shell *shell);

// echo_utils.c 
void			add_space(t_list *arg_node, char **result);
void			handle_n_argument(t_list **arg_node, bool *print_newline);

// echo_arguments.c
void			process_argument(t_shell *shell, char *arg, char **result);
void			handle_argument(t_shell *shell, t_list *arg_node, \
char **result, bool print_newline);

// env.c
int				ft_env(t_shell *shell, t_cmd *cmd);

// exit.c
int				handle_too_many_args(void);
int				ft_exit(t_shell *shell, t_cmd *cmd);

// export.c
int				ft_export(t_shell *shell, t_cmd *cmd);
int				export_args(t_shell *msh, t_cmd *cmd_struct);
void			sort_list(t_list **head);
t_list			*clone_list(t_list *original);
int				free_and_set_error(char **str_array, t_shell *msh);
int				handle_str_array(t_shell *msh, char **str_array, \
char *arg_concat);
int				handle_syntax_check(t_shell *msh, char *arg_concat, \
int syntax_check);
int				handle_no_equal_sign(t_shell *msh, char *arg_concat);

int				export_no_args(t_shell *msh, t_cmd *cmd);
char			**split_arg_export(char *str, t_shell *shell);
int				check_syntax(char *str);
int				handle_str_array_removal(char *arg_concat, char **str_array, \
t_shell *msh);
int				handle_no_quotes_error(char *arg_concat, char **str_array, \
t_shell *msh);
int				update_or_add_env_var(t_shell *msh, char **str_array);

// pwd.c
int				ft_pwd(t_shell *shell, t_cmd *cmd);

// unset.c
int				ft_unset(t_shell *shell, t_cmd *cmd);

//*********** Cleanup ***********//

// free_cloned_list.c
void			free_cloned_list(t_list *head);

// free_cmd_struct.c
void			free_cmd_struct(void *data);

// free_data.c
void			free_data(void *data);
void			free_array(void **arr_ptr);

// free_envv_struct.c
void			free_envv_struct(void *data);

// free_everything.c
void			free_everything(t_shell *shell);

// free_input.c
void			free_input(t_shell *shell);

// free_tokens.c
void			free_tokens(t_shell *shell);

// minishell_error_exit.c
void			error_and_exit(t_shell *shell, char *error_message);

//*********** Envvar ***********//

// expand_envvar.c
char			*evaluate_envvars(char *str, t_shell *shell);
void			expand_envvar(t_shell *shell, int *i);

// envvar_utils2.c
void			handle_envv_var(char **str, char **result, t_shell *shell);

// envvar_utils.c
t_list			*find_envvar_node(t_list *envvar, char *key);
char			*get_env_key(char *str);
char			*get_env_value(t_list *envvar, char *key);
void			update_node_value(t_list *envvar_node, char *new_value);

// handle_vars.c
void			handle_no_value(t_shell *shell, int *i, char *key);
char			*handle_single_quotes(char *str, char *var_start, \
char **result);
char			*handle_special_vars(char *var_start, \
t_shell *shell, char **result);

//*********** Execute ***********//

// cmd_is_builtin.c
bool			cmd_is_builtin(char *command);

// cmd_path.c
bool			has_path(char *str);
char			*get_path(t_shell *shell, char *command);

// convert_envvar_to_array.c
char			**convert_envvar_to_array(t_shell *shell);

// exec_cmd_builtin.c
void			setup_child_pipes(t_exec_params *params);
void			execute_builtin_with_pipes(t_shell *shell, \
t_cmd *cmd, t_exec_params *params);

// exec_commands.c
void			execute_command(t_shell *shell, t_cmd *cmd, \
t_exec_params *params);
void			execute_command_child(t_exec_params *params, \
char **env, char **args, t_shell *shell);
void			execute_command_parent(t_exec_params *params, \
pid_t pid);

// exec_pipeline.c
int				ft_lstindex(t_list *head, t_list *node);
void			execute_pipeline(t_shell *shell, t_exec_params params);
void			execute_command_wrapper(t_shell *shell, \
t_list *curr_cmd, t_exec_params *params);

// exec_utils.c
void			free_exec_arrays(char **env, char **arg);
void			reset_file_descriptors(t_shell *shell);
int				**init_pipes(t_exec_params *params);
void			close_pipes(t_exec_params *params);
void			close_pipe(int fd);

// exec_utils2.c
void			get_pid_exit_status(t_shell *shell, t_list **pids);
void			check_command_access(char *path, t_shell *shell);

// execute_builtin.c
void			execute_builtin(t_shell *shell, t_cmd *cmd);

// handle_redirections.c
void			handle_redirections(t_cmd *cmd, t_shell *shell);

// put_args_in_array.c
char			**put_args_in_array(t_cmd *cmd_struct);

//*********** Get_input ***********//

// input.c
char			*get_input(t_shell *shell);

bool			is_just_whitespace(char *input);
bool			check_unclosed_quotes(char *input);

//*********** Init ***********//

// clone_env_to_duplist.c
char			**split_variables(char *envv);
t_envv			*put_str_in_envv_struct(char **cloned_substrs);
void			add_envv_to_dlist(t_shell *shell, t_envv *s_envv);
void			clone_envv_to_dlist(t_shell *shell, char **envv);

// init.c
t_shell			*init_minishell(char **envv);
t_exec_params	init_exec_params(t_shell *shell);

//*********** Lexer ***********//

// add_token_to_list.c
void			create_and_add_token(t_shell *shell, int start, int end);
void			tokenise_arg(t_shell *shell, const char *input, int *i);
int			separate_tokens(t_shell *shell, const char *input);
int			add_tokens_to_list(t_shell *shell);

// add_token_utils.c
char			*remove_quotes(char *str);
t_list			*safe_new_token_node(t_shell *shell, char *str);
char			*copy_without_quotes(char *str, char *result);

// handle_meta_chars.c
int			check_redir(t_shell *shell, const char *input, int *i);
bool			is_valid_arg_char(char c);
bool			is_redirect_or_pipe(char c);
void			check_state(char current_char, int *state);

//*********** Parse ***********//

// commands_initialisation.c
t_cmd			*initialize_cmd(t_list **curr_token_ptr, t_shell *shell);
t_cmd			*initialize_cmd_struct(t_list **curr_token_ptr, t_shell *shell);

// commands_processing.c
void			add_args_to_cmd(t_shell *shell, t_cmd *cmd, char *data);
int				add_cmd_to_list(t_shell *shell, t_cmd *cmd_struct);
void			extract_commands(t_shell *shell);

// handle_redirection.c
char			*read_heredoc(char *delimiter);
bool			file_exists(const char *file_name);
void			handle_redirection(t_cmd *cmd, t_list **token_ptr, \
t_shell *shell);
void			preprocess_redirections(t_cmd *cmd, t_list **curr_token_ptr, \
t_shell *shell);

// parse_utils.c
bool			is_redirect(char *str);
int				get_open_flags(bool is_append);

// process_fds.c
void			process_fds(t_shell *shell);

// process_input.c
void			process_input(t_shell *shell);
int				validate_tokens(t_shell *shell);

//redirections_utils.c
void			process_redirections(t_cmd *cmd, t_list **token_ptr, \
t_shell *shell);
void			copy_redirections(t_cmd *src, t_cmd *dest);
void			check_and_free_cmd_struct(t_cmd *cmd, t_list *last_token);

//*********** Signals ***********// 

// signals.c
void			reset_signal_handlers(void);

//*********** Lib_utils ***********//

// error_free_utils.c
void			error_exit(const char *error);
void			error(const char *error, char *arg);
void			free_null(void **mem_ptr);
char			*ft_strjoin_free(char *s1, char *s2, int to_free);

// list_utils.c
bool			ft_lsthas_node(t_list *lst_head, t_list *node_to_find);
void			ft_lstdel_head(t_list **lst_head, void (*del)(void*));
void			ft_lstdel_node(t_list **lst_head, t_list *node_to_del, \
	void (*del)(void*));

// list_utils2.c
void			ft_lstswap_nodes(t_list **head, t_list *node1, t_list *node2);

// malloc_utils.c
void			*malloc_and_check_alloc(size_t bytes, char *error_message);
void			*calloc_and_check_alloc(size_t number, size_t size, \
char *error_message);

// moded_split.c
char			**ft_split_first(const char *input_str, const char delimiter);

// lib_utils.c
char			*ft_replace_substr(char *str, int start, int end, char *substr);
char			*ft_strjoin_any(int num_of_str, ...);
char			*ft_strcpy(char *dest, char *src);
bool			ft_isspace(int c);
int				ft_strcmp(char *s1, char *s2);

// lib_utils2.c
char			*ft_strstr(char *str, char *to_find);

void			signal_handler(int signal);
int				set_signal_handling(t_shell *shell);
int				set_termios(t_shell *shell);
char			*single_dollar_checker(char *var_start, char **result);

int	free_and_return(char	*path, char	*old_pwd, int return_value);
void	free_resources(char *path, char *old_pwd);
char *get_path_from_args(t_cmd *cmd_struct);
char	*remove_all_quotes(char *str);
char	*get_new_path(t_cmd	*cmd_struct);
void add_char_to_result(char **str, char **result);

char *ft_strjoin_char(char *str, char c);
void	concat_before_var(char *str, char *var_start, char **result);
void	free_arguments(t_list *arguments);


char	*get_command_path(t_shell *shell, char *command);

char	*process_argument_main(char *arg, t_shell *shell);
void handle_bin_paths(char **args, t_shell *shell, t_exec_params *params);
void copy_after_quote(const char *cmd, int *i, int *j, t_shell *shell);
void copy_until_quote(const char *cmd, int *i, int *j, t_shell *shell);

#endif
