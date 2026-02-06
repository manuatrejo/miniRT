/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:26 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/04 06:18:40 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	free_spheres(t_sphere_list *s)
{
	t_sphere_list	*next;

	while (s)
	{
		next = s->next;
		free(s);
		s = next;
	}
}

static void	free_planes(t_plane_list *p)
{
	t_plane_list	*next;

	while (p)
	{
		next = p->next;
		free(p);
		p = next;
	}
}

static void	free_cylinders(t_cylind_list *c)
{
	t_cylind_list	*next;

	while (c)
	{
		next = c->next;
		free(c);
		c = next;
	}
}

static void	free_lights(t_light_list *l)
{
	t_light_list	*next;

	while (l)
	{
		next = l->next;
		free(l);
		l = next;
	}
}

void	free_scene(t_parse *scene)
{
	if (!scene)
		return ;
	free_lights(scene->lights);
	free_spheres(scene->sphere);
	free_planes(scene->plane);
	free_cylinders(scene->cyl);
	free(scene);
}
