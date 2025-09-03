/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:57:39 by malshapraboth     #+#    #+#             */
/*   Updated: 2024/12/12 18:57:41 by malshapraboth    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	isin(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	start;
	size_t	end;
	size_t	trim_len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && isin(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && isin(s1[end - 1], set))
		end--;
	trim_len = end - start;
	result = malloc(sizeof(char) * (trim_len + 1));
	if (!result)
		return (NULL);
	ft_memmove(result, s1 + start, trim_len);
	result[trim_len] = '\0';
	return (result);
}
/*
int	main(void)
{
	char *str = "Hello, World!";
	char *charset = ", !l";
	char *modstr = ft_strtrim(str, charset);
	printf("%s\n", modstr);
	return (0);
}*/
