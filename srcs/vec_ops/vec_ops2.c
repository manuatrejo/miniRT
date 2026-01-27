/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ops2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:35 by maanguit          #+#    #+#             */
/*   Updated: 2026/01/28 00:02:00 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coord3	vec_normalize(t_coord3 v)
{
	t_coord3	res;
	double		len;

	len = vec_length(v);
	if (len == 0.0)
	{
		res.x = 0.0;
		res.y = 0.0;
		res.z = 0.0;
		return (res);
	}
	res.x = v.x / len;
	res.y = v.y / len;
	res.z = v.z / len;
	return (res);
}

t_coord3	vec_cross_prod(t_coord3 u, t_coord3 v)
{
	t_coord3	res;

	res.x = u.y * v.z - u.z * v.y;
	res.y = u.z * v.x - u.x * v.z;
	res.z = u.x * v.y - u.y * v.x;
	return (res);
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
