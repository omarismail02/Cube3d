/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:08:09 by oismail           #+#    #+#             */
/*   Updated: 2024/07/16 15:08:14 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		index;
	char	*dest;
	char	*d;

	index = 0;
	dest = (char *)malloc(ft_strlen(src) * sizeof(char) + 1);
	d = dest;
	if (!d)
	{
		return (0);
	}
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return ((char *)dest);
}

// #include <stdio.h>

// int main()
// {
// 	printf("%s", ft_strdup("hello"));
// 	return (0);
// }
