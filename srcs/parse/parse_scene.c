/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:02 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/07 17:18:33 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	parse_amb_light(t_parse **scene, char **split_l)
{
	t_real	intensity;

	if (!scene || !*scene)
		return (false);
	if (!ensure_token_count(split_l, 3))
		return (ft_putendl_fd("Error:\nA format", 2), false);
	if ((*scene)->a_light.defined)
		return (ft_putendl_fd("Error:\nA already defined", 2), false);
	if (!parse_range_double(split_l[1], 0.0, 1.0, &intensity))
		return (ft_putendl_fd("Error:\nA ratio out of range [0,1]", 2), false);
	(*scene)->a_light.intensity = (t_real)intensity;
	if (!parse_color(&(*scene)->a_light.color, split_l[2]))
		return (ft_putendl_fd("Error:\nA invalid color", 2), false);
	(*scene)->a_light.defined = true;
	return (true);
}

bool	parse_camera(t_parse **scene, char **split_l)
{
	t_camera	*cam;
	t_real		fov;

	if (!scene || !*scene)
		return (false);
	if (!ensure_token_count(split_l, 4))
		return (ft_putendl_fd("Error:\nC format", 2), false);
	cam = &(*scene)->cam;
	if (cam->defined)
		return (ft_putendl_fd("Error:\nC already defined", 2), false);
	if (!parse_coord(&cam->orig, split_l[1]))
		return (ft_putendl_fd("Error:\nC invalid origin", 2), false);
	if (!parse_dir_normalized(&cam->dir, split_l[2]))
		return (ft_putendl_fd("Error:\nC vec must be normalized", 2), false);
	if (!parse_range_double(split_l[3], (t_real)0.0, (t_real)180.0, &fov))
		return (ft_putendl_fd("Error:\nC fov out of range [0,180]", 2), false);
	cam->fov = fov;
	cam->defined = true;
	return (true);
}

bool	parse_light(t_parse **scene, char **split_l)
{
	t_light_list	*node;
	t_real			intensity;

	if (!scene || !*scene)
		return (false);
	if (!ensure_token_count(split_l, 4))
		return (ft_putendl_fd("Error:\nL format", 2), false);
	node = ft_calloc(1, sizeof(t_light_list));
	if (!node)
		return (false);
	if (!parse_coord(&node->light.point, split_l[1]))
		return (free(node),
			ft_putendl_fd("Error:\nL invalid position", 2), false);
	if (!parse_range_double(split_l[2], (t_real)0.0, (t_real)1.0, &intensity))
		return (free(node),
			ft_putendl_fd("Error:\nL I out of range [0,1]", 2), false);
	node->light.intensity = intensity;
	if (!parse_color(&node->light.color, split_l[3]))
		return (free(node), ft_putendl_fd("Error:\n L invalid color", 2), false);
	node->light.defined = true;
	if (!MULT_LIGHTS && (*scene)->lights && (*scene)->lights->light.defined)
		return (ft_putendl_fd("Error:\n1 Light!", 2), free(node), false);
	node->next = (*scene)->lights;
	(*scene)->lights = node;
	return (true);
}
