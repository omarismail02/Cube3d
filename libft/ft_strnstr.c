/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:11:56 by oismail           #+#    #+#             */
/*   Updated: 2024/07/16 15:11:59 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

// char	*ft_strnstr(const char *big, const char *little, size_t len)
// {
// 	size_t	i;

// 	if (!len || !ft_strlen(little))
// 		return ((char *)big);
// 	i = 0;
// 	while (big[i] && i < len)
// 	{
// 		if (ft_strncmp(big + i, little, ft_strlen(little)) == 0)
// 			return ((char *)big + i);
// 		i++;
// 	}
// 	return (0);
// }

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str && !len)
		return (0);
	if (to_find[0] == '\0' || to_find == str)
		return ((char *)str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == to_find[j] && (i + j) < len)
		{
			if (str[i + j] == '\0' && to_find[j] == '\0')
				return ((char *)&str[i]);
			j++;
		}
		if (to_find[j] == '\0')
			return ((char *)(str + i));
		i++;
	}
	return (0);
}
