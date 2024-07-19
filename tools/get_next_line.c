/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:22:05 by yessemna          #+#    #+#             */
/*   Updated: 2024/07/19 11:29:40 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *join(char *s1, char *s2)
{
    char *s;
    int n1;
    int n2;
    int i = -1;
    int j = 0;

    if (!s1 && !s2)
        return (NULL);
    if (!s1)
        return (join("", s2));
    if (!s2)
        return (join("", s1));
    n1 = ft_strlen(s1);
    n2 = ft_strlen(s2);
    s = (char *)malloc(sizeof(char) * (n1 + n2 + 1));
    if (!s)
        return (NULL);
    while (++i < n1)
        s[i] = s1[i];
    while (j < n2)
        s[i++] = s2[j++];
    s[i] = '\0';
    return (s);
}

void get_line_(char *buff, char **tmp ,char **line)
{
    int i = 0;
    while (buff[i] && buff[i] != '\n')
        i++;
    if (buff[i] == '\0')
    {
        *tmp = NULL;
        *line = join(buff, "");
        return ;
    }
    *tmp = join(buff + i + 1, "");
    buff[i + 1] = '\0';
    *line = join(buff, "");
}

char *get_next_line(int fd)
{
    static char *tmp;
    char buff[BUFFER_SIZE + 1];
    char *line;
    char *res;
    int r = 1;

    if (fd < 0 || read(fd, "", 0) < 0)
        return (free(tmp), tmp = NULL, NULL);
    if (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
        return (free(tmp), tmp = NULL, NULL);
    line = join(tmp, "");
    if (!line)
        return (free(tmp), NULL);
    free(tmp);
    tmp = NULL;
    while (r)
    {
        r = read(fd, buff, BUFFER_SIZE);
        if (r <= 0 && !ft_strlen(line))
            return (free(line) ,NULL);
        buff[r] = '\0';
        res = join(line, buff);
        if (!res)
            return (free(line), NULL);
        free(line);
        get_line_(res, &tmp, &line);
        free(res);
        if (tmp)
            break ;
    }
    return (line);
}
