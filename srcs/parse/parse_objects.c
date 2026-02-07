/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:07 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/07 12:19:45 by amonteag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	parse_sphere(t_parse **scene, char **split_l)
{
	t_sphere_list	*sp;

	if (!scene || !*scene)
		return (false);
	if (!ensure_token_count(split_l, 4) && !ensure_token_count(split_l, 7))
		return (ft_putendl_fd("Error: sp format", 2), false);
	sp = ft_calloc(1, sizeof(t_sphere_list));
	if (!sp)
		return (false);
	if (!parse_coord(&sp->sphere.center, split_l[1])
		|| !parse_positive_double(split_l[2], &sp->sphere.radius)
		|| !parse_color(&sp->sphere.color, split_l[3]))
		return (free(sp), ft_putendl_fd("Error: sp invalid params", 2), false);
	sp->sphere.albedo = sp->sphere.color;
	if (!p_material(&sp->sphere.roughness, &sp->sphere.metallic,
			&sp->sphere.albedo, split_l))
		return (free(sp), ft_putendl_fd("Error: sp material", 2), false);
	sp->sphere.radius = sp->sphere.radius / 2;
	sp->next = (*scene)->sphere;
	(*scene)->sphere = sp;
	return (true);
}

bool	parse_plane(t_parse **scene, char **split_l)
{
	t_plane_list	*pl;

	if (!scene || !*scene)
		return (false);
	if (!ensure_token_count(split_l, 4) && !ensure_token_count(split_l, 7))
		return (ft_putendl_fd("Error: pl format", 2), false);
	pl = ft_calloc(1, sizeof(t_plane_list));
	if (!pl)
		return (false);
	if (!parse_coord(&pl->plane.point, split_l[1])
		|| !parse_dir_normalized(&pl->plane.normal, split_l[2])
		|| !parse_color(&pl->plane.color, split_l[3]))
		return (free(pl), ft_putendl_fd("Error: pl invalid params", 2), false);
	pl->plane.albedo = pl->plane.color;
	if (!p_material(&pl->plane.roughness, &pl->plane.metallic,
			&pl->plane.albedo, split_l))
		return (free(pl), ft_putendl_fd("Error: pl material", 2), false);
	pl->next = (*scene)->plane;
	(*scene)->plane = pl;
	return (true);
}

bool	parse_cylinder(t_parse **scene, char **split_l)
{
	t_cylind_list	*cy;

	if (!ensure_token_count(split_l, 6) && !ensure_token_count(split_l, 9))
		return (ft_putendl_fd("Error: cy format", 2), false);
	cy = ft_calloc(1, sizeof(t_cylind_list));
	if (!cy)
		return (false);
	if (!parse_coord(&cy->cyl.point, split_l[1])
		|| !parse_dir_normalized(&cy->cyl.axis, split_l[2])
		|| !parse_positive_double(split_l[3], &cy->cyl.radius)
		|| !parse_positive_double(split_l[4], &cy->cyl.length)
		|| !parse_color(&cy->cyl.color, split_l[5])
		|| cy->cyl.radius <= (t_real)0.0 || cy->cyl.length <= (t_real)0.0)
		return (free(cy), ft_putendl_fd("Error: cy invalid params", 2), false);
	cy->cyl.albedo = cy->cyl.color;
	if (!p_material(&cy->cyl.roughness, &cy->cyl.metallic, &cy->cyl.albedo,
			split_l))
		return (free(cy), ft_putendl_fd("Error: cy material", 2), false);
	cy->cyl.radius = (t_real)cy->cyl.radius / 2;
	cy->cyl.point = vec_sub(cy->cyl.point,
			vec_x_scalar(cy->cyl.axis, cy->cyl.length / (t_real)2.0));
	cy->next = (*scene)->cyl;
	(*scene)->cyl = cy;
	return (true);
}

bool	parse_cone(t_parse **scene, char **split_l)
{
	t_cone_list	*cone;

	if (!ensure_token_count(split_l, 6) && !ensure_token_count(split_l, 9))
		return (ft_putendl_fd("Error: cn format", 2), false);
	cone = ft_calloc(1, sizeof(t_cone_list));
	if (!cone)
		return (false);
	if (!parse_coord(&cone->cone.point, split_l[1])
		|| !parse_dir_normalized(&cone->cone.axis, split_l[2])
		|| !parse_positive_double(split_l[3], &cone->cone.radius)
		|| !parse_positive_double(split_l[4], &cone->cone.length)
		|| !parse_color(&cone->cone.color, split_l[5])
		|| cone->cone.radius <= (t_real)0.0 || cone->cone.length <= (t_real)0.0)
		return (free(cone), ft_putendl_fd("Error: cn invalid params", 2), false);
	cone->cone.albedo = cone->cone.color;
	if (!p_material(&cone->cone.roughness, &cone->cone.metallic,
			&cone->cone.albedo, split_l))
		return (free(cone), ft_putendl_fd("Error: cn material", 2), false);
	cone->cone.radius = (t_real)cone->cone.radius / 2;
	cone->next = (*scene)->cnl;
	(*scene)->cnl = cone;
	return (true);
}