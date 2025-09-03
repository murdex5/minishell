/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:30:43 by kadferna          #+#    #+#             */
/*   Updated: 2024/12/11 12:54:01 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (dest == src)
		return (dest);
	i = -1;
	if (s < d && s + n > d)
	{
		while (++i < n)
			d[n - 1 - i] = s[n - 1 - i];
	}
	else
	{
		while (++i < n)
			d[i] = s[i];
	}
	return (dest);
}
/*
int	main(void)
{
	char	*str;
	char	*dest;

	str = "Hello, World!";
	dest = malloc(sizeof(char *) * 13);
	dest = ft_memmove(dest, str, 13);
	printf("%s \n", dest);
	free(dest);
	return (0);
}*/
