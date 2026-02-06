/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 07:27:16 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/06 06:33:40 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	color_proccessing(t_color color)
{
	t_real	gamma;
	t_real	scale;
	t_real	exposure;

	scale = (t_real)1.0;
	if (color.x > (t_real)255.0
		|| color.y > (t_real)255.0
		|| color.z > (t_real)255.0)
		scale = (t_real)1.0 / (t_real)255.0;
	color = vec_x_scalar(color, scale);
	exposure = (t_real)1.4;
	color = vec_x_scalar(color, exposure);
	color.x = color.x / (1.0f + color.x);
	color.y = color.y / (1.0f + color.y);
	color.z = color.z / (1.0f + color.z);
	gamma = (t_real)1.0 / (t_real)2.2;
	color.x = pow(color.x, gamma);
	color.y = pow(color.y, gamma);
	color.z = pow(color.z, gamma);
	color.x = fmin(fmax(color.x, (t_real)0.0), (t_real)1.0);
	color.y = fmin(fmax(color.y, (t_real)0.0), (t_real)1.0);
	color.z = fmin(fmax(color.z, (t_real)0.0), (t_real)1.0);
	return ((int)(255.99f * color.x) << 16 | (int)(255.99f * color.y) << 8 |
		(int)(255.99f * color.z));
}
