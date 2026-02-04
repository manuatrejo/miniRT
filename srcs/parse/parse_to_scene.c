/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 23:25:34 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/04 06:19:07 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	count_spheres(t_sphere_list *s)
{
	int	n;

	n = 0;
	while (s)
	{
		n++;
		s = s->next;
	}
	return (n);
}

static int	count_planes(t_plane_list *p)
{
	int	n;

	n = 0;
	while (p)
	{
		n++;
		p = p->next;
	}
	return (n);
}

static int	count_cylinders(t_cylind_list *c)
{
	int	n;

	n = 0;
	while (c)
	{
		n++;
		c = c->next;
	}
	return (n);
}

static bool	alloc_scene_arrays(t_scene *scene)
{
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
	if (scene->n_cylinders > 0)
	{
		scene->cylinder = ft_calloc(scene->n_cylinders, sizeof(t_cyl));
		if (!scene->cylinder)
			return (false);
	}
	return (true);
}

t_scene	parse_to_scene(t_parse *parse)
{
	t_scene			scene;
	t_sphere_list	*sp;
	t_plane_list	*pl;
	t_cylind_list	*cy;
	int				i;

	ft_bzero(&scene, sizeof(t_scene));
	if (!parse)
		return (scene);
	scene.a_light = parse->a_light;
	scene.cam = parse->cam;
	scene.light = parse->light;
	scene.n_spheres = count_spheres(parse->sphere);
	scene.n_planes = count_planes(parse->plane);
	scene.n_cylinders = count_cylinders(parse->cyl);
	if (!alloc_scene_arrays(&scene))
	{
		ft_putendl_fd("Error: malloc scene arrays", 2);
		free_scene(parse);
		ft_bzero(&scene, sizeof(t_scene));
		return (scene);
	}
	i = 0;
	sp = parse->sphere;
	while (sp)
	{
		scene.sphere[i++] = sp->sphere;
		sp = sp->next;
	}
	i = 0;
	pl = parse->plane;
	while (pl)
	{
		scene.plane[i++] = pl->plane;
		pl = pl->next;
	}
	i = 0;
	cy = parse->cyl;
	while (cy)
	{
		scene.cylinder[i++] = cy->cyl;
		cy = cy->next;
	}
	free_scene(parse);
	return (scene);
}
