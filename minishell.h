#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/param.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define MAXCMD 1024
# define MAXLIST 100

typedef enum e_type
{
    CMD,
    PIPE,
    SPACE,
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

typedef struct s_redir
{
    char *file_name;
    t_type type;
    struct s_redir    *next;
}t_redir;

typedef struct s_cmd
{
    char	**cmds;
    t_redir *redir;
    struct s_cmd    *next;
}	t_cmd;

char *ft_strcpy(char *dest, const char *src);
int ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putendl_fd(char *s, int fd);
void print_error(char *str);

//finders

int is_space(char c);
int is_special(char c);
int find_char(char *str, char c);
int is_alnum(char c);

//tokenazing
char *ft_srtjoin(char *s1, char *s2);
char	*ft_strjoin(char const *s1, char const *s2, int len);

void pipe_redirection(char *line, t_token **list, int *i);
void dollar_sign(char *line, t_token **list, int *i, int start, int end);
// parsing

int catch_errors(t_token **arg);

//lst_tools.c
int ft_strcmp(const char *s1, const char *s2);
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


#endif

// Structure for the command line




