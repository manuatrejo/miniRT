/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:07 by maanguit          #+#    #+#             */
/*   Updated: 2026/01/30 02:01:46 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	parse_sphere(t_parse **scene, char **split_l)
{
	t_sphere_list	*sp;
	double			diameter;

	if (!scene || !*scene)
		return (false);
	if (!ensure_token_count(split_l, 4))
		return (ft_putendl_fd("Error: sp format", 2), false);
	sp = ft_calloc(1, sizeof(t_sphere_list));
	if (!sp)
		return (false);
	if (!parse_coord(&sp->sphere.center, split_l[1])
		|| !parse_positive_double(split_l[2], &diameter)
		|| !parse_color(&sp->sphere.color, split_l[3]))
		return (free(sp), ft_putendl_fd("Error: sp invalid params", 2), false);
	sp->sphere.radius = (t_real)diameter / 2;
	sp->next = (*scene)->sphere;
	(*scene)->sphere = sp;
	return (true);
}

bool	parse_plane(t_parse **scene, char **split_l)
{
	t_plane_list	*pl;

	if (!scene || !*scene)
		return (false);
	if (!ensure_token_count(split_l, 4))
		return (ft_putendl_fd("Error: pl format", 2), false);
	pl = ft_calloc(1, sizeof(t_plane_list));
	if (!pl)
		return (false);
	if (!parse_coord(&pl->plane.point, split_l[1])
		|| !parse_dir_normalized(&pl->plane.normal, split_l[2])
		|| !parse_color(&pl->plane.color, split_l[3]))
		return (free(pl), ft_putendl_fd("Error: pl invalid params", 2), false);
	pl->next = (*scene)->plane;
	(*scene)->plane = pl;
	return (true);
}

bool	parse_cylinder(t_parse **scene, char **split_l)
{
	t_cylind_list	*cy;
	double			diameter;
	double			length;

	if (!scene || !*scene)
		return (false);
	if (!ensure_token_count(split_l, 6))
		return (ft_putendl_fd("Error: cy format", 2), false);
	cy = ft_calloc(1, sizeof(t_cylind_list));
	if (!cy)
		return (false);
	if (!parse_coord(&cy->cylind.point, split_l[1])
		|| !parse_dir_normalized(&cy->cylind.axis, split_l[2])
		|| !parse_positive_double(split_l[3], &diameter)
		|| !parse_positive_double(split_l[4], &length)
		|| !parse_color(&cy->cylind.color, split_l[5]))
		return (free(cy), ft_putendl_fd("Error: cy invalid params", 2), false);
	cy->cylind.diameter = (t_real)diameter;
	cy->cylind.length = (t_real)length;
	cy->next = (*scene)->cylinder;
	(*scene)->cylinder = cy;
	return (true);
}
