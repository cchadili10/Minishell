/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 04:15:07 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/17 21:45:03 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/param.h>
# include <limits.h>
# include <dirent.h>
# include <termios.h>
# include <stdarg.h>
# include <sys/stat.h>
# define COLOR_WHITE "\033[37m" 
# define COLOR_ORANGE "\033[38;5;214m" 
# define MAXCMD 1024
# define MAXLIST 100
# define GET 0
# define SET 1
# define HEXA "0123456789abcdef"
# define HEXA_MAJ "0123456789ABCDEF"

// typedef struct s_fds
// {
// 	int		fd;
// 	s_fds	*next;
// }	t_fds;

typedef enum e_type
{
	CMD,
	PIPE,
	SPC,
	IN,
	HEREDOC,
	OUT,
	APPEND,
	SNGL_Q,
	DBL_Q,
	VAR,
	DBL_VAR,
	EXIT_STATUS,
}	t_type;

typedef struct s_token
{
	char			*key;
	char			*copy_key;
	t_type			value;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	int				redir_in;
	int				redir_out;
	char			**cmds;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_export
{
	char			*key;
	char			*value;
	struct s_export	*next;	
}	t_exp;

typedef struct s_export_var
{
	char	*key;
	char	*value;
	int		start;
	int		append;
	int		update_;
}	t_export_var;

typedef struct s_exection_var
{
	int		p[2];
	char	**arr_phat;
	char	**env;
	char	*arr_join;
	int		id;
	int		std_d;
	int		flag;
}	t_exection_var;

typedef struct s_main_prepare_cmd
{
	char	**cmd_strs;
	int		std;
	int		red_in;
	int		red_out;
}			t_main_prepare_cmd;

void	print_cmd(t_cmd **cmd);
void	print_list(t_token *list);
// tools
char	*ft_strcpy(char *dest, const char *src);
int		ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putendl_fd(char *s, int fd);
void	print_error(char *str);
char	**dbl_join(char **s1, char *s2);
char	*ft_strdup(const char *s);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

//finders
int		is_space(char c);
int		is_special(char c);
int		find_char(char *str, char c);
int		is_alnum(char c);
int		ft_findchar(char *str, char c);

//tokenazing
char	*ft_srtjoin(char *s1, char *s2);
char	*ft_strjoin(char const *s1, char const *s2, int len);
int		processline(char *line, t_token **list);
void	print_list(t_token *list);
void	join_nodes(t_token **list);
void	pipe_redirection(char *line, t_token **list, int *i);
// void	dollar_sign(char *line, t_token **list, int *i, int start, int end);
int		prepare_cmd(t_token *list, t_cmd **cmd, t_env *envi);

// parsing
int		processline(char *line, t_token **list);
int		catch_errors(t_token **arg);
void	spc_pipe_red(char *line, t_token **list, int *i);
int		quotes(char *line, t_token **list, int *i);
int		is_red(char c);
void	initenv(char **env, t_env **envi);
t_cmd	*lst_new_cmd(char **line, int in, int out);
void	lst_add_back_cmd(t_cmd **head, t_cmd *new);
int		handle_redir(t_token **tmp, int *red_in, int *red_out, t_env *envi);
char	*cpy_part(char *src, int start, int end);
void	token_exit_status(char **line, t_token **list, int *i);

//lst_tools.c
void	lst_add_back(t_token **head, t_token *new);
t_token	*lst_new(char *key, t_type value);
int		ft_lstsize(t_env *lst);
void	lst_add_back_env(t_env **head, t_env *new);
t_env	*lst_new_env(char *key, char *value);
void	ft_lstclear(t_token **lst);
void	ft_lstclear_env(t_env **lst);
void	find_node(t_env *envi, t_token *list);
void	handle_expand(t_env *envi, t_token **tmp, int found);
int		count_word(char *str);
char	*join_char(char *str, char c);

// guarbage collector
typedef struct s_col
{
	void			*ptr;
	struct s_col	*next;
}	t_col;

typedef enum e_call
{
	FREE,
	MALLOC
}	t_call;

t_col	*new_node(void	*ptr);
t_col	*last_node(t_col **head);
void	add_back(t_col	**head, t_col *new);
void	clear_all(t_col **head);
void	*g_malloc(size_t size, t_call call);
void	*g_malloc_env(size_t size, t_call call);
char	*ft_strdup_env(const char *s);
char	**ft_split_env(char const *s, char c);
char	*ft_substr_env(char const *s, unsigned int start, size_t len);

//signals
void	ft_signal(void);
void	ft_herdoc(int sig);

//exection
void	ft_execution(t_cmd **cmnds, t_env **env);
void	ft_here_doc(t_token *cmd, t_env *envi, int *red_in);

//exit_status
int		ft_exit_status(int value, int set);
int		ft_exit_herdog(int check, int set);

//export_functions
void	ft_replace_value_for_export(t_exp **export,
			char *key, char *value, int check);
void	ft_replace_value_for_env(t_env **env, char *key,
			char *value, int check);
void	ft_add_to_env_export(t_exp **export, t_env **env,
			char *key, char *value);
int		ft_find_key(t_exp **export, char *key);
int		ft_check_key(char *key);
void	ft_set_zero_to_struct(t_export_var *exp);
int		ft_count_eq(char *str, int chek, t_export_var *exp);

//unset_functions
void	ft_remove_key_export(t_exp **export, char *key);
void	ft_remove_key_env(t_env **env, char *key);

//cd_functions
void	ft_go_to_home_env(t_env **env);
int		ft_go_to_home_export(t_exp **export);
void	ft_set_path_for_env(t_env **env);
int		ft_set_path_for_export(t_exp **export, t_cmd *cmnd, int x);

//execution_functions
void	ft_excute(t_cmd **cmnds, t_exp **export, t_env **node_env);
void	ft_excute_one(t_cmd **cmnds, t_exp **export,
			char **env, t_env **node_env);
void	ft_buitin_cmnd(t_cmd *cmnds, t_env **env,
			t_exp **export, int place);
int		ft_check_cmnd(t_cmd *cmnd);
int		ft_count_cmnds(t_cmd **cmnds);
char	*ft_look_for_paht(t_env **env);
void	ft_fill_export(t_exp **export, t_env **env);
char	*ft_get_path(char **arr_phat, char *first_cmnd, t_exection_var *exp);
char	**ft_get_charenv(t_env **env);
int		ft_count_arg(char **str);
void	ft_first_cmnd(t_cmd *tmp, t_env **node_env,
			t_exp **export, t_exection_var *exp);
void	ft_mid_cmnd(t_cmd *tmp, t_env **node_env,
			t_exp **export, t_exection_var *exp);
void	ft_last_cmnd(t_cmd *tmp, t_env **node_env,
			t_exp **export, t_exection_var *exp);
void	ft_set_zero(t_exection_var *exp);

//sort_export
void	ft_sort_export(t_exp **export);

//ft_printf
int		ft_printf(const char *format, ...);
void	ft_putchar(char c, int *count);
void	ft_putstr(char *str, int *count);
void	ft_putnbr(int n, int *count);
void	ft_put_u_nbr(unsigned int n, int *count);
void	ft_hexa(unsigned int n, int *count, char *HEXA_);
void	ft_hexap(unsigned long long n, int *count, char *HEXA_);
//builtsin
void	ft_env(t_env **env, t_cmd *cmnds);
void	ft_putstr_fd(char *s, int fd);
void	ft_cd(t_cmd *cmnd, t_env **env, t_exp **export);
void	ft_echo(t_cmd *cmnd);
void	ft_pwd(t_env **env);
void	ft_exit(t_cmd *cmnd);
void	ft_export(t_cmd *cmnd, t_env **env, t_exp **export);
void	insert_end(t_exp **head, char *key, char *value);
void	ft_unset(t_cmd *cmnd, t_exp **export, t_env **env);
t_exp	*create_node(char *key, char *value);
int		ft_check_key(char *key);
int		ft_find_key(t_exp **export, char *key);
char	*ft_strjoin_(char const *s1, char const *s2);
//testing
int		ft_check_file_erorr(char *str);
void	ft_display_erorr(t_exection_var *exp, t_cmd *tmp);
char	*ft_loop_for_path(char **arr_phat, char *first_cmnd);
char	*ft_check_cmd_erorrs(char *first_cmnd, t_exection_var *exp, int test);

#endif
// Structure for the command line