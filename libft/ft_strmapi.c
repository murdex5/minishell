/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:36:49 by kadferna          #+#    #+#             */
/*   Updated: 2024/12/13 12:36:51 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	result = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	while (s[i] != '\0')
	{
		result[i] = (*f)(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
int	main(void) {
	// Test input string
	char *original = "hello";

	// Call ft_strmapi with the test function
	char *result = ft_strmapi(original, test_function);

	// Check the result and print it
	if (result) {
		printf("Original string: %s\n", original);
		printf("Transformed string: %s\n", result);
		free(result); // Free the allocated memory
	} else {
		printf("Memory allocation failed.\n");
	}

	return (0);
}*/