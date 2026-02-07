/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_scene2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:13:44 by cress             #+#    #+#             */
/*   Updated: 2026/02/07 17:45:33 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	alloc_scene_arrays2(t_scene *scene)
{
	if (scene->n_cylinders > 0)
	{
		scene->cylinder = ft_calloc(scene->n_cylinders, sizeof(t_cyl));
		if (!scene->cylinder)
			return (false);
	}
	if (scene->n_cones > 0)
	{
		scene->cone = ft_calloc(scene->n_cones, sizeof(t_cone));
		if (!scene->cone)
			return (false);
	}
	return (true);
}

bool	alloc_scene_arrays(t_scene *scene)
{
	if (scene->n_lights > 0)
	{
		scene->lights = ft_calloc(scene->n_lights, sizeof(t_light));
		if (!scene->lights)
			return (false);
	}
	if (scene->n_spheres > 0)
	{
		scene->sphere = ft_calloc(scene->n_spheres, sizeof(t_sphere));
		if (!scene->sphere)
			return (false);
	}
	if (scene->n_planes > 0)
	{
		scene->plane = ft_calloc(scene->n_planes, sizeof(t_plane));
		if (!scene->plane)
			return (false);
	}
	return (alloc_scene_arrays2(scene));
}

void	alloc_parse_to_scene3(t_scene scene, t_parse *parse)
{
	t_plane_list	*pl;
	int				i;

	i = 0;
	pl = parse->plane;
	while (pl)
	{
		scene.plane[i++] = pl->plane;
		pl = pl->next;
	}
}

void	alloc_parse_to_scene2(t_scene scene, t_parse *parse)
{
	t_cylind_list	*cy;
	t_cone_list		*cn;
	int				i;

	i = 0;
	cy = parse->cyl;
	while (cy)
	{
		scene.cylinder[i++] = cy->cyl;
		cy = cy->next;
	}
	i = 0;
	cn = parse->cnl;
	while (cn)
	{
		scene.cone[i++] = cn->cone;
		cn = cn->next;
	}
	alloc_parse_to_scene3(scene, parse);
}

void	alloc_parse_to_scene(t_scene scene, t_parse *parse)
{
	t_light_list	*l;
	t_sphere_list	*sp;
	int				i;

	i = 0;
	l = parse->lights;
	while (l)
	{
		scene.lights[i++] = l->light;
		l = l->next;
	}
	i = 0;
	sp = parse->sphere;
	while (sp)
	{
		scene.sphere[i++] = sp->sphere;
		sp = sp->next;
	}
	alloc_parse_to_scene2(scene, parse);
}
