/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:08:27 by oismail           #+#    #+#             */
/*   Updated: 2024/07/16 15:08:30 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
	s[i] = '\0';
}

// #include <stdio.h>
// #include "libft.h"

// void increment_ascii(unsigned int i, char *c)
// {
//     *c = *c + i;
// }

// int main(void)
// {
//     char str[] = "hello";

//     printf("Original string: %s\n", str);
//     ft_striteri(str, increment_ascii);
//     printf("Modified string: %s\n", str);

//     return 0;
// }
