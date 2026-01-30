/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:02 by maanguit          #+#    #+#             */
/*   Updated: 2026/01/30 00:03:09 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	parse_amb_light(t_parse **scene, char **split_l)
{
	double	intensity;

	if (!scene || !*scene)
		return (false);
	if (!ensure_token_count(split_l, 3))
		return (ft_putendl_fd("Error: A format", 2), false);
	if ((*scene)->a_light.defined)
		return (ft_putendl_fd("Error: A already defined", 2), false);
	if (!parse_range_double(split_l[1], 0.0, 1.0, &intensity))
		return (ft_putendl_fd("Error: A ratio out of range [0,1]", 2), false);
	(*scene)->a_light.intensity = (t_real)intensity;
	if (!parse_color(&(*scene)->a_light.color, split_l[2]))
		return (ft_putendl_fd("Error: A invalid color", 2), false);
	(*scene)->a_light.defined = true;
	return (true);
}

bool	parse_camera(t_parse **scene, char **split_l)
{
	t_camera	*cam;

	if (!scene || !*scene)
		return (false);
	if (!ensure_token_count(split_l, 4))
		return (ft_putendl_fd("Error: C format", 2), false);
	cam = &(*scene)->cam;
	if (cam->defined)
		return (ft_putendl_fd("Error: C already defined", 2), false);
	if (!parse_coord(&cam->orig, split_l[1]))
		return (ft_putendl_fd("Error: C invalid origin", 2), false);
	if (!parse_dir_normalized(&cam->dir, split_l[2]))
		return (ft_putendl_fd("Error: C vec must be normalized", 2), false);
	if (!parse_range_double(split_l[3], 0.0, 180.0, &cam->fov))
		return (ft_putendl_fd("Error: C fov out of range [0,180]", 2), false);
	cam->defined = true;
	return (true);
}

bool	parse_light(t_parse **scene, char **split_l)
{
	t_light	*light;
	double	intensity;

	if (!scene || !*scene)
		return (false);
	if (!ensure_token_count(split_l, 4))
		return (ft_putendl_fd("Error: L format", 2), false);
	light = &(*scene)->light;
	if (light->defined)
		return (ft_putendl_fd("Error: L already defined", 2), false);
	if (!parse_coord(&light->point, split_l[1]))
		return (ft_putendl_fd("Error: L invalid position", 2), false);
	if (!parse_range_double(split_l[2], 0.0, 1.0, &intensity))
		return (ft_putendl_fd("Error: L ratio out of range [0,1]", 2), false);
	light->intensity = (t_real)intensity;
	if (!parse_color(&light->color, split_l[3]))
		return (ft_putendl_fd("Error: L invalid color", 2), false);
	light->defined = true;
	return (true);
}
