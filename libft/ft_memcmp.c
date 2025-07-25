/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:03:42 by oismail           #+#    #+#             */
/*   Updated: 2024/07/16 15:03:46 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char			*str1;
	char			*str2;
	size_t			i;

	str1 = (char *)s1;
	str2 = (char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char )str1[i] - (unsigned char )str2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>

// int main()
// {
//     char str1[] = "Hello";
//     char str2[] = "World";
//     int result;

//     result = ft_memcmp(str1, str2, 5);
//     printf( "%d", result);
//     return 0;
// }
