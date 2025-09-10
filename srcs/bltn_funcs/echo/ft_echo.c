/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjbaiju <anjbaiju@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 22:16:08 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/10 13:37:07 by anjbaiju         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*process_arguments(const char *str)
{
	char	*processed_str;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	processed_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!processed_str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
			else
				processed_str[j++] = str[i];
			i++;
			continue ;
		}
		else
			processed_str[j++] = str[i++];
	}
	processed_str[j] = '\0';
	return (processed_str);
}

int	check_on_evnp(char *variable_name, char **envp)
{
	int		i;
	size_t	len;

	if (!variable_name || *variable_name == '\0')
	{
		if (variable_name)
			free(variable_name);
		return (-1);
	}
	variable_name = modify_variable(variable_name);
	len = ft_strlen(variable_name);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(variable_name, envp[i], len) == 0 && (envp[i][len] == '='
				|| envp[i][len] == '\0'))
		{
			free(variable_name);
			return (i);
		}
		i++;
	}
	free(variable_name);
	return (-1);
}

static char	*add_exit(char *str, char *search, char *replace)
{
	if (!str || !search || !replace) {
        return NULL;
    }

    size_t search_len = strlen(search);
    // If search string is empty, just duplicate the original string.
    if (search_len == 0) {
        return strdup(str);
    }
    
    size_t replace_len = strlen(replace);

    // First, calculate the required size for the new string.
    int count = 0;
    const char *p = str;
    while ((p = strstr(p, search))) {
        count++;
        p += search_len;
    }
    
    size_t new_len = strlen(str) + count * (replace_len - search_len);
    char *new_str = malloc(new_len + 1);
    if (!new_str) {
        return NULL;
    }

    // Now, build the new string.
    char *current_pos = new_str;
    const char *old_pos = str;
    const char *match = NULL;

    while ((match = strstr(old_pos, search))) {
        // Copy the segment before the match.
        size_t len_before = match - old_pos;
        memcpy(current_pos, old_pos, len_before);
        current_pos += len_before;

        // Copy the replacement string.
        memcpy(current_pos, replace, replace_len);
        current_pos += replace_len;

        // Move the old position pointer past the search term.
        old_pos = match + search_len;
    }

    // Copy the remainder of the string after the last match.
    strcpy(current_pos, old_pos);

    return new_str;
}

static char add_exit(char *str, int exit_code)
{
	char *exit_val;
	char *temp;
	size_t exit_len;
	size_t new_len;

	exit_val = ft_itoa(exit_code);
	len = ft_strlen(exit_val);
	new_len = ft_strlen(str) + len;
	temp = ft_strdup(str);
	if (!temp)
		return (NULL);
	str = ft_realloc(str, ft_strlen(str), new_len);
}

char	*check_variables(char *str, char ***envp_ptr, int exit_code)
{
	char	*varaible_name;
	char	*value;
	int		i;

	if (ft_strnstr(str, "$?", ft_strlen("$?")))
		str = add_exit(str, "$?", ft_itoa(exit_code));
	varaible_name = detect_varaible_name(str);
	if (!varaible_name)
		return (str);
	i = check_on_evnp(str, *envp_ptr);
	if (i < 0)
		value = NULL;
	else
		value = get_variable_value(i, *envp_ptr);
	return (value);
}

static int	process_n_flags(char **argv, int *i)
{
	int	j;
	int	new_line;

	new_line = 1;
	j = 2;
	while (argv[*i] && argv[*i][0] == '-' && argv[*i][1] == 'n')
	{
		while (argv[*i][j] == 'n')
			j++;
		if (argv[*i][j] != '\0')
			break ;
		new_line = 0;
		(*i)++;
		j = 2;
	}
	return (new_line);
}

int	ft_echo(char **argv, char ***envp_ptr, int exit_code)
{
	int		i;
	int		new_line;
	char	*str;

	i = 1;
	new_line = process_n_flags(argv, &i);
	while (argv[i] != NULL)
	{
		str = process_arguments(argv[i]);
		if (!is_single_quoted(argv[i]))
			str = check_variables(str, envp_ptr, exit_code);
		if (str)
			write(STDOUT_FILENO, str, ft_strlen(str));
		if (argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		free(str);
		i++;
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
