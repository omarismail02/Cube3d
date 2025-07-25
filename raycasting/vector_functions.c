/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:05:44 by oismail           #+#    #+#             */
/*   Updated: 2025/07/25 12:05:46 by oismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/struct.h"

t_motion	vadd(t_motion vec, t_motion vec1)
{
	t_motion	result;

	result.x = vec.x + vec1.x;
	result.y = vec.y + vec1.y;
	return (result);
}

t_motion	vsub(t_motion vec, t_motion vec1)
{
	t_motion	result;

	result.x = vec.x - vec1.x;
	result.y = vec.y - vec1.y;
	return (result);
}

t_coordinates	vec2pos(t_motion vec)
{
	t_coordinates	buffer;

	buffer.x = (int)vec.x;
	buffer.y = (int)vec.y;
	return (buffer);
}

t_motion	vrotate(t_motion vec, double deg)
{
	t_motion	result;
	double		rad;

	rad = (-deg / 180.0) * M_PI;
	result.x = vec.x * cos(rad) - vec.y * sin(rad);
	result.y = vec.x * sin(rad) + vec.y * cos(rad);
	return (result);
}
