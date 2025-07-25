/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:04:06 by oismail           #+#    #+#             */
/*   Updated: 2024/07/16 15:04:09 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *)dest;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

// #include <stdio.h>

// int main() {
// 	int src_arr[] = {1, 2, 3, 4, 5};
// 	int dest_arr[5];

// 	size_t num_bytes = sizeof(src_arr);
// 	ft_memcpy(dest_arr, src_arr, num_bytes);
// 	for (int i = 0; i < 5; i++) {
// 		printf("%d ", dest_arr[i]);
// 	}
// 	printf("\n");
// 	return 0;
// }
