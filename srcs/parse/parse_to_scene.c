/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 23:25:34 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/07 16:59:52 by maanguit         ###   ########.fr       */
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

static int	count_lights(t_light_list *l)
{
	int	n;

	n = 0;
	while (l)
	{
		n++;
		l = l->next;
	}
	return (n);
}

t_scene	parse_to_scene(t_parse *parse)
{
	t_scene			scene;

	ft_bzero(&scene, sizeof(t_scene));
	if (!parse)
		return (scene);
	scene.a_light = parse->a_light;
	scene.cam = parse->cam;
	scene.n_lights = count_lights(parse->lights);
	scene.n_spheres = count_spheres(parse->sphere);
	scene.n_planes = count_planes(parse->plane);
	scene.n_cylinders = count_cylinders(parse->cyl);
	if (!alloc_scene_arrays(&scene))
	{
		ft_putendl_fd("Error:\n malloc scene arrays", 2);
		free_scene(parse);
		ft_bzero(&scene, sizeof(t_scene));
		return (scene);
	}
	alloc_parse_to_scene(scene, parse);
	free_scene(parse);
	return (scene);
}
