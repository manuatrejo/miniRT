/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_scene_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 00:00:00 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/07 18:39:41 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	count_spheres(t_sphere_list *s)
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

int	count_planes(t_plane_list *p)
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

int	count_cylinders(t_cylind_list *c)
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

int	count_cones(t_cone_list *c)
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

int	count_lights(t_light_list *l)
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
