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
    DBL_VAR
}	t_type;


typedef struct s_env
{
    char	*key;
    t_type	value;
    struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
    char	*cmd;
    char	**args;
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

// parsing

int catch_errors(t_env **arg);

//lst_tools.c

void    lst_add_back(t_env **head, t_env *new);
t_env   *lst_new(char *key, t_type value);
void	ft_lstclear(t_env **lst);


#endif

// Structure for the command line




