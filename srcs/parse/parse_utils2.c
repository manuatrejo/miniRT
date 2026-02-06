/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:18 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/06 20:29:08 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	parse_coord(t_vec3 *coord, char *str)
{
	char	**c_split;

	if (!coord || !str)
		return (false);
	c_split = ft_split(str, ',');
	if (!c_split)
		return (false);
	if (!ensure_token_count(c_split, 3) || !parse_digits(c_split))
		return (free_str_array(c_split),
			ft_putendl_fd("Error: C format", 2), false);
	coord->x = ft_atof(c_split[0]);
	coord->y = ft_atof(c_split[1]);
	coord->z = ft_atof(c_split[2]);
	return (free_str_array(c_split), true);
}

bool	parse_color(t_color *color, char *str)
{
	char	**c_split;

	if (!color || !str)
		return (false);
	c_split = ft_split(str, ',');
	if (!c_split)
		return (false);
	if (!ensure_token_count(c_split, 3) || !parse_digits_color(c_split))
		return (free_str_array(c_split),
			ft_putendl_fd("Error: C format", 2), false);
	color->x = ft_atoi(c_split[0]) / (t_real)255.0;
	color->y = ft_atoi(c_split[1]) / (t_real)255.0;
	color->z = ft_atoi(c_split[2]) / (t_real)255.0;
	if (color->x < 0 || color->x > 255
		|| color->y < 0 || color->y > 255
		|| color->z < 0 || color->z > 255)
		return (free_str_array(c_split), false);
	return (free_str_array(c_split), true);
}
