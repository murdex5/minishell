/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:19:36 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/16 17:19:39 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	append_to_result(char *result, int j, char *str_to_append)
{
	return (append_str(result, j, str_to_append));
}

int	handle_special_vars(char *str, int *i, t_expand_data *data)
{
	char	*temp_str;

	if (str[*i + 1] == '?')
	{
		temp_str = ft_itoa(data->exit_code);
		data->j += append_to_result(data->result, data->j, temp_str);
		free(temp_str);
		*i += 2;
	}
	else if (str[*i + 1] == '$')
	{
		temp_str = ft_itoa(getpid());
		data->j += append_to_result(data->result, data->j, temp_str);
		free(temp_str);
		*i += 2;
	}
	return (data->j);
}

int	handle_env_var_expansion(char *var_name, t_expand_data *data)
{
	int		env_index;
	char	*var_value;

	env_index = check_on_evnp(var_name, *(data->envp_ptr));
	if (env_index >= 0)
	{
		var_value = get_variable_value(env_index, *(data->envp_ptr));
		data->j += append_to_result(data->result, data->j, var_value);
		free(var_value);
	}
	return (env_index);
}

int	handle_regular_vars(char *str, int *i, t_expand_data *data)
{
	char	*var_name;

	var_name = detect_varaible_name(&str[*i]);
	if (var_name && ft_strlen(var_name) > 0)
	{
		handle_env_var_expansion(var_name, data);
		*i += ft_strlen(var_name) + 1;
		free(var_name);
	}
	else
	{
		data->result[data->j++] = str[(*i)++];
		if (var_name)
			free(var_name);
	}
	return (data->j);
}

int	process_dollar_sign(char *str, int *i, t_expand_data *data)
{
	if (str[*i + 1] == '?' || str[*i + 1] == '$')
	{
		data->j = handle_special_vars(str, i, data);
	}
	else
	{
		data->j = handle_regular_vars(str, i, data);
	}
	return (data->j);
}
