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

// parsing

int catch_errors(t_token **arg);

//lst_tools.c

void    lst_add_back(t_token **head, t_token *new);
t_token   *lst_new(char *key, t_type value);

void    lst_add_back_env(t_env **head, t_env *new);
t_env   *lst_new_env(char *key, char *value);
void	ft_lstclear(t_token **lst);
void	ft_lstclear_env(t_env **lst);


#endif

// Structure for the command line




