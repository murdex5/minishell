/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjbaiju <anjbaiju@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:32:34 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/10 14:41:48 by anjbaiju         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(char *r1, t_token *token, char **envp_ptr, t_ast_node *pipe)
{
	printf("exit\n");
	if (*envp_ptr || envp_ptr)
		free_environment(envp_ptr);
	if (token)
		free_token(token);
	if (pipe)
		free_ast(pipe);
	free_r1(r1);
}

int	is_single_quoted(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'' && str[strlen(str) - 1] == '\'')
		return (1);
	return (0);
}

void	*ft_realloc(void *a, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (!new_size)
	{
		free(a);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (a)
	{
		if (old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
		ft_memcpy(new_ptr, a, copy_size);
		free(a);
	}
	return (new_ptr);
}
int	get_array_len(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return (i);
	while (tokens[i] != NULL)
		i++;
	return (i);
}

char	**copy_environment(char *envp[])
{
	int		count;
	char	**new_envp;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	new_envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (i-- > 0)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *ft_strcpy(char *dest, const char *src)
{
    int i;

    i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char *ft_strstr(const char *haystack, const char *needle)
{
    size_t i;
    size_t j;

    if (*needle == '\0')
        return ((char *)haystack);
    i = 0;
    while (haystack[i] != '\0')
    {
        j = 0;
        while (haystack[i + j] != '\0' && needle[j] != '\0' && haystack[i + j] == needle[j])
        {
            j++;
        }
        if (needle[j] == '\0')
        {
            return ((char *)&haystack[i]);
        }
        i++;
    }
    return (NULL);
}
