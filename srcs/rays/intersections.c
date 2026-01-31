/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 23:48:25 by maanguit          #+#    #+#             */
/*   Updated: 2026/01/31 00:24:37 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	update_sp_hit(t_ray ray, t_sphere sp, t_hit *hit)
{
	hit->p = vec_add(ray.orig, vec_x_scalar(ray.dir, hit->t));
	hit->n = vec_div(vec_sub(hit->p, sp.center), sp.radius);
	hit->color = sp.color;
	// hit->ref_c = sp.ref_c; (reflexión cuando haya)
}

static void	intersect_sphere(t_ray ray, t_sphere sp, t_hit *hit)
{
	t_dir	oc;
	t_real	a;//t_vars para norminette
	t_real	b;
	t_real	c;
	t_real	discriminant;

	oc = vec_sub(sp.center, ray.orig);
	a = dot_product(ray.dir, ray.dir);
	b = dot_product(ray.dir, oc);
	c = dot_product(oc, oc) - (sp.radius * sp.radius);
	discriminant = b * b - a * c;
	if (discriminant < (t_real)0.0)
		return ;
	discriminant = t_real_sqrt(discriminant);
	c = (b - discriminant) / a;
	if (c <= (t_real)0.0 || c >= hit->t)
	{
		c = (b + discriminant) / a;
		if (c <= (t_real)0.0 || c >= hit->t)
			return ;
	}
	hit->t = c;
	update_sp_hit(ray, sp, hit);
}

t_hit	get_closest_hit(t_ray ray, t_scene scene)
{
	t_hit	first_hit;
	int		i;

	i = 0;
	first_hit.t = 1000000.0;//ponerle un valor grande (MACRO)
	while (i < scene.n_spheres)
		intersect_sphere(ray, scene.sphere[i++], &first_hit);
	// i = 0;
	// while (i < scene.n_planes)
	// 	intersect_plane(ray, scene.plane[i++], &first_hit);
	// i = 0;
	// while (i < scene.n_cylinders)
	// 	intersect_cylinder(ray, scene.cylinder[i++], &first_hit);
	return (first_hit);
}
