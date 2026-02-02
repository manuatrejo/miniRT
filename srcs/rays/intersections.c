/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 23:48:25 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/02 06:36:11 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	update_sp_hit(t_ray ray, t_sphere sp, t_hit *hit)
{
	hit->p = vec_add(ray.orig, vec_x_scalar(ray.dir, hit->t));
	hit->n = vec_div(vec_sub(hit->p, sp.center), sp.radius);
	hit->color = sp.color;
	hit->o_type = OBJ_SPHERE;
	// hit->ref_c = sp.ref_c; (reflexión cuando haya)
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
	t_dir	ca;
	t_dir	oc;
	t_real	r;
	t_real	card;
	t_real	caoc;
	t_real	a;
	t_real	b;
	t_real	c;
	t_real	d;
	t_real	sqrt_d;
	t_real	t;
	t_real	y;
	t_point	p;
	t_dir	n;
	// caps
	t_real	dn;
	t_real	tcap;
	t_point	pcap;
	t_dir	v;

	if (!hit)
		return ;
	r = cyl.diameter / (t_real)2.0;
	if (r <= (t_real)0.0 || cyl.length <= (t_real)0.0)
		return ;
	ca = vec_normalize(cyl.axis);
	oc = vec_sub(ray.orig, cyl.point);
	card = dot_product(ca, ray.dir);
	caoc = dot_product(ca, oc);

	a = dot_product(ray.dir, ray.dir) - card * card;
	b = dot_product(ray.dir, oc) - card * caoc;
	c = dot_product(oc, oc) - caoc * caoc - r * r;

	if (double_abs(a) >= 1e-6)
	{
		d = b * b - a * c;
		if (d >= (t_real)0.0)
		{
			sqrt_d = t_real_sqrt(d);
			t = (-b - sqrt_d) / a;
			if (t <= (t_real)1e-6 || t >= hit->t)
			{
				t = (-b + sqrt_d) / a;
				if (t <= (t_real)1e-6 || t >= hit->t)
					t = (t_real)-1.0;
			}
			if (t > (t_real)0.0)
			{
				y = caoc + t * card;
				if (y >= (t_real)0.0 && y <= cyl.length)
				{
					p = vec_add(ray.orig, vec_x_scalar(ray.dir, t));
					n = vec_sub(vec_sub(p, cyl.point), vec_x_scalar(ca, y));
					n = vec_normalize(n);
					hit->t = t;
					hit->p = p;
					hit->n = n;
					hit->color = cyl.color;
					hit->o_type = OBJ_CYLINDER;
				}
			}
		}
	}
	dn = dot_product(ray.dir, ca);
	if (double_abs(dn) >= 1e-6)
	{
		tcap = -caoc / dn;
		if (tcap > (t_real)1e-6 && tcap < hit->t)
		{
			pcap = vec_add(ray.orig, vec_x_scalar(ray.dir, tcap));
			v = vec_sub(pcap, cyl.point);
			v = vec_sub(v, vec_x_scalar(ca, dot_product(v, ca)));
			if (dot_product(v, v) <= r * r)
			{
				hit->t = tcap;
				hit->p = pcap;
				hit->n = vec_x_scalar(ca, (t_real)-1.0);
				hit->color = cyl.color;
				hit->o_type = OBJ_CYLINDER;
			}
		}
		tcap = (cyl.length - caoc) / dn;
		if (tcap > (t_real)1e-6 && tcap < hit->t)
		{
			pcap = vec_add(ray.orig, vec_x_scalar(ray.dir, tcap));
			v = vec_sub(pcap, cyl.point);
			v = vec_sub(v, vec_x_scalar(ca, dot_product(v, ca)));
			if (dot_product(v, v) <= r * r)
			{
				hit->t = tcap;
				hit->p = pcap;
				hit->n = ca;
				hit->color = cyl.color;
				hit->o_type = OBJ_CYLINDER;
			}
		}
	}
}

t_hit	get_closest_hit(t_ray ray, t_scene scene)
{
	t_hit	first_hit;
	int		i;

	i = 0;
	first_hit.t = 1000000.0;//ponerle valor con una MACRO
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
