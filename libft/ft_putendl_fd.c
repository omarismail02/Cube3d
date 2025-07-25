/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:05:30 by oismail           #+#    #+#             */
/*   Updated: 2024/07/16 15:05:49 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

// #include <stdio.h>

// int main()
// {
// 	int fd = 1; // Assuming 1 for standard output (stdout)
// 	char *str = "Hello, World!";

// 	ft_putendl_fd(str, fd);

// 	return 0;
// }
