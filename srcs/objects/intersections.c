/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 23:48:25 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/07 17:42:49 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	update_sp_hit(t_ray ray, t_sphere sp, t_hit *hit)
{
	hit->p = vec_add(ray.orig, vec_x_scalar(ray.dir, hit->t));
	hit->n = vec_div(vec_sub(hit->p, sp.center), sp.radius);
	hit->color = sp.color;
	hit->albedo = sp.albedo;
	hit->metallic = sp.metallic;
	hit->roughness = sp.roughness;
}

static void	intersect_sphere(t_ray ray, t_sphere sp, t_hit *hit)
{
	t_dir	oc;
	t_real	a;
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

static void	intersect_plane(t_ray ray, t_plane plane, t_hit *hit)
{
	t_real	t;
	t_real	dot;
	t_dir	plane_to_ray;

	dot = dot_product(plane.normal, ray.dir);
	if (double_abs(dot) < 1e-6)
		return ;
	plane_to_ray = vec_sub(plane.point, ray.orig);
	t = dot_product(plane.normal, plane_to_ray) / dot;
	if (t <= 1e-6 || t > hit->t)
		return ;
	hit->t = t;
	hit->p = vec_add(ray.orig, vec_x_scalar(ray.dir, t));
	hit->n = plane.normal;
	if (dot_product(hit->n, ray.dir) > (t_real)0.0)
		hit->n = vec_x_scalar(hit->n, (t_real) - 1.0);
	hit->color = plane.color;
	hit->albedo = plane.albedo;
	if (CHECK_BOARD && ((int)floorf(hit->p.x) + (int)floorf(hit->p.z)) & 1)
	{
		hit->color = (t_color){0.0, 0.0, 0.0};
		hit->albedo = (t_color){0.0, 0.0, 0.0};
	}
	hit->metallic = plane.metallic;
	hit->roughness = plane.roughness;
}



t_hit	get_closest_hit(t_ray ray, t_scene *scene)
{
	t_hit	first_hit;
	int		i;

	first_hit.t = (t_real)INFINITE;
	i = 0;
	while (i < scene->n_planes)
		intersect_plane(ray, scene->plane[i++], &first_hit);
	i = 0;
	while (i < scene->n_spheres)
		intersect_sphere(ray, scene->sphere[i++], &first_hit);
	i = 0;
	while (i < scene->n_cylinders)
		intersect_cylinder(ray, scene->cylinder[i++], &first_hit);
	i = 0;
	while (i < scene->n_cones)
		intersect_cone(ray, scene->cone[i++], &first_hit);
	return (first_hit);
}
