/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:56:44 by oismail           #+#    #+#             */
/*   Updated: 2024/07/16 14:56:49 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

// #include <stdio.h>

// int main()
// {
//     char str[30] = "ABCD EFGH";
//     printf("Before bzero: %s\n", str);

//     ft_bzero(str, 2);
//     printf("After bzero: %s\n", str);

//     return 0;
// }
