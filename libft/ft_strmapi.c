/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:10:10 by oismail           #+#    #+#             */
/*   Updated: 2024/07/16 15:10:14 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	str = ft_strdup(s);
	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		str[i] = (*f)(i, str[i]);
		i++;
	}
	return (str);
}

// #include <stdio.h>
// #include "libft.h"

// char to_upper(unsigned int n, char c)
// {
//     if (n == 1 && c >= 'a' && c <= 'z')
//         return c - 32;
//     return c;
// }

// int main(void)
// {
//     char *str = "hello world";
//     char *result;

//     result = ft_strmapi(str, to_upper);
//     if (result)
//     {
//         printf("%s", result);
//         free(result);
//     }

//     return 0;
// }
