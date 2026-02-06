/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ops2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:35 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/03 09:49:17 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_dir	vec_div(t_dir u, t_real n)
{
	t_dir	res;

	res.x = u.x / n;
	res.y = u.y / n;
	res.z = u.z / n;
	return (res);
}

t_dir	vec_normalize(t_dir v)
{
	t_dir	res;
	t_real	len;

	len = vec_length(v);
	if (len == 0.0)
	{
		res.x = 0.0;
		res.y = 0.0;
		res.z = 0.0;
		return (res);
	}
	return (vec_div(v, len));
}

t_dir	vec_cross_prod(t_dir u, t_dir v)
{
	t_dir	res;

	res.x = u.y * v.z - u.z * v.y;
	res.y = u.z * v.x - u.x * v.z;
	res.z = u.x * v.y - u.y * v.x;
	return (res);
}

t_real	t_real_sqrt(t_real n)
{
	if (sizeof(n) == 8)
		return (sqrt(n));
	return (sqrtf(n));
}

bool	equal_vecs(t_dir u, t_dir v)
{
	const t_real	epsilon = 1e-3;
	t_real			x_diff;
	t_real			y_diff;
	t_real			z_diff;

	x_diff = u.x - v.x;
	y_diff = u.y - v.y;
	z_diff = u.z - v.z;
	if (x_diff > epsilon || x_diff < -epsilon
		|| y_diff > epsilon || y_diff < -epsilon
		|| z_diff > epsilon || z_diff < -epsilon)
		return (false);
	return (true);
}
