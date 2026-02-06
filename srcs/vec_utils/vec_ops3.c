/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ops3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 07:45:27 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/03 07:47:08 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_dir	vec_prod(t_dir u, t_dir v)
{
	t_dir	result;

	result.x = u.x * v.x;
	result.y = u.y * v.y;
	result.z = u.z * v.z;
	return (result);
}
