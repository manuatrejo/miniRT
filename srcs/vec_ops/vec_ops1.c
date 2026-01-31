/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ops1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:32 by maanguit          #+#    #+#             */
/*   Updated: 2026/01/30 22:32:13 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_dir	vec_add(t_dir vec1, t_dir vec2)
{
	t_dir	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
}

t_dir	vec_sub(t_dir vec1, t_dir vec2)
{
	t_dir	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}

t_dir	vec_x_scalar(t_dir vec, t_real scalar)
{
	t_dir	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	result.z = vec.z * scalar;
	return (result);
}
t_real	dot_product(t_dir vec1, t_dir vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_real	vec_length(t_dir v)
{
	return (t_real_sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
