/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:26 by maanguit          #+#    #+#             */
/*   Updated: 2026/01/23 19:40:27 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	free_spheres(t_sphere *s)
{
	t_sphere	*next;

	while (s)
	{
		next = s->next;
		free(s);
		s = next;
	}
}

static void	free_planes(t_plane *p)
{
	t_plane	*next;

	while (p)
	{
		next = p->next;
		free(p);
		p = next;
	}
}

static void	free_cylinders(t_cylind *c)
{
	t_cylind	*next;

	while (c)
	{
		next = c->next;
		free(c);
		c = next;
	}
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_spheres(scene->sphere);
	free_planes(scene->plane);
	free_cylinders(scene->cylinder);
	free(scene);
}
