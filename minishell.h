#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/param.h>
#include <limits.h>
#include <dirent.h>
#include <termios.h>


# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
// # define RESET "\033[0m"
# define CYELLOW "\001\e[0;31m\002"
#define COLOR_WHITE "\033[37m" 
#define COLOR_ORANGE "\033[38;5;214m" 
# define MAXCMD 1024
# define MAXLIST 100
# define GET 0
# define SET 1


// get_next_line

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

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
}	t_type;


typedef struct s_token
{
	char	*key;
	t_type	value;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env    *next;
}	t_env;

typedef struct s_cmd
{
	int     redir_in;
	int     redir_out;
	char	**cmds;
	struct s_cmd    *next;
}	t_cmd;

typedef struct s_export
{
	char *key;
	char *value;
	struct s_export	*next;	
}	t_export;

// tools
char *ft_strcpy(char *dest, const char *src);
int     ft_strlen(const char *str);
int     ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putendl_fd(char *s, int fd);
void 	print_error(char *str);
char 	**dbl_join(char **s1, char *s2);
char	*ft_strdup(const char *s);
char	*get_next_line(int fd);
//finders

int is_space(char c);
int is_special(char c);
int find_char(char *str, char c);
int is_alnum(char c);
char *cpy_part(char *src, int start, int end);

//tokenazing
char *ft_srtjoin(char *s1, char *s2);
char	*ft_strjoin(char const *s1, char const *s2, int len);
int processline(char *line, t_token **list);
void print_list(t_token *list);
void join_nodes(t_token **list);

void pipe_redirection(char *line, t_token **list, int *i);
void dollar_sign(char *line, t_token **list, int *i, int start, int end);
int prepare_cmd(t_token *list, t_cmd **cmd, t_env *envi);
// parsing

int catch_errors(t_token **arg);

//lst_tools.c
void    lst_add_back(t_token **head, t_token *new);
t_token   *lst_new(char *key, t_type value);
int ft_lstsize(t_env *lst);

void    lst_add_back_env(t_env **head, t_env *new);
t_env   *lst_new_env(char *key, char *value);
void	ft_lstclear(t_token **lst);
void	ft_lstclear_env(t_env **lst);
void find_node(t_env *envi, t_token *list);
int count_word(char *str);
char *join_char(char *str, char c);


// guarbage collector

typedef struct s_col
{
	void			*ptr;
	struct s_col	*next;
}t_col;

typedef enum e_call
{
	FREE,
	MALLOC
}t_call;


t_col	*new_node(void	*ptr);
t_col	*last_node(t_col **head);
void	add_back(t_col	**head, t_col *new);
void	clear_all(t_col **head);
void	*g_malloc(size_t size, t_call call);


void	*g_malloc_env(size_t size, t_call call);

char *ft_strdup_env(const char *s);
char	**ft_split_env(char const *s, char c);
char	*ft_substr_env(char const *s, unsigned int start, size_t len);

char  *heredoc_expand(char *line, t_env *envi);

//exection
void	ft_execution (t_cmd **cmnds, t_env **env);


void ft_here_doc(t_token *cmd, t_env *envi, int *red_in);

//builtsin
void 	ft_env(t_env **env, t_cmd *cmnds);
void	ft_putstr_fd(char *s, int fd);
void	ft_cd(t_cmd *cmnd, t_env **env);
void	ft_echo(t_cmd *cmnd);
void	ft_pwd(t_env **env);
void	ft_exit(t_cmd *cmnd);
void	ft_export(t_cmd *cmnd, t_env **env, t_export **export);
void		insert_end(t_export **head, char *key, char *value);
t_export	*create_node(char *key, char *value);
void	ft_unset(t_cmd *cmnd, t_export **export, t_env **env);
int		ft_check_key(char *key);// in file
int		ft_find_key(t_export **export, char *key);// in file
char	*ft_strjoin_(char const *s1, char const *s2);
//signals
void ft_signal(void);
//exit_status
void	ft_exit_status(int value, int set);
//sort_export
void ft_sort_export(t_export **export);
#endif

// Structure for the command line


