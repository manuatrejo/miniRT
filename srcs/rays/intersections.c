/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 23:48:25 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/03 10:01:28 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// hit->ref_c = sp.ref_c; (reflexión cuando haya)
static void	update_sp_hit(t_ray ray, t_sphere sp, t_hit *hit)
{
	hit->p = vec_add(ray.orig, vec_x_scalar(ray.dir, hit->t));
	hit->n = vec_div(vec_sub(hit->p, sp.center), sp.radius);
	hit->color = sp.color;
	hit->o_type = OBJ_SPHERE;
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
	hit->color = plane.color;
	hit->o_type = OBJ_PLANE;
}

static void	intersect_cylinder(t_ray ray, t_cylind cyl, t_hit *hit)
{
	t_utils	u;

	u.oc = vec_sub(ray.orig, cyl.point);
	u.card = dot_product(cyl.axis, ray.dir);
	u.caoc = dot_product(cyl.axis, u.oc);
	u.a = dot_product(ray.dir, ray.dir) - u.card * u.card;
	u.b = dot_product(ray.dir, u.oc) - u.card * u.caoc;
	u.c = dot_product(u.oc, u.oc) - u.caoc * u.caoc - cyl.radius * cyl.radius;
	u.d = u.b * u.b - u.a * u.c;
	cylin_sides(ray, cyl, hit, u);
	cylin_caps(ray, cyl, hit, u);
}

t_hit	get_closest_hit(t_ray ray, t_scene scene)
{
	t_hit	first_hit;
	int		i;

	i = 0;
	first_hit.t = (t_real)INFINITE;
	while (i < scene.n_spheres)
		intersect_sphere(ray, scene.sphere[i++], &first_hit);
	i = 0;
	while (i < scene.n_planes)
		intersect_plane(ray, scene.plane[i++], &first_hit);
	i = 0;
	while (i < scene.n_cylinders)
		intersect_cylinder(ray, scene.cylinder[i++], &first_hit);
	return (first_hit);
}
