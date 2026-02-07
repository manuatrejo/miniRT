/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 00:00:00 by GitHub Copilot     #+#    #+#             */
/*   Updated: 2026/02/07 00:00:00 by GitHub Copilot     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Finite cone intersection.
**
** Cone model used here matches the parser's convention:
** - cone.axis is normalized
** - cone.length is the height
** - cone.radius is the base radius
** - cone.point is the cone base center shifted by -axis*(length/2) in parser,
**   i.e. it represents the *bottom cap center* (same convention as cylinder).
**
** Tip is: tip = cone.point + cone.axis * cone.length
** Base center is: cone.point
*/
static void	cone_cap(t_ray ray, t_cone cone, t_hit *hit)
{
	t_real	dot;
	t_real	t;
	t_vec3	p;
	t_vec3	v;
	t_vec3	n;

	/* Cap is a disk on the base plane (center=cone.point, normal=-axis) */
	n = vec_x_scalar(cone.axis, (t_real)-1.0);
	dot = dot_product(n, ray.dir);
	if (double_abs(dot) < 1e-6)
		return ;
	t = dot_product(n, vec_sub(cone.point, ray.orig)) / dot;
	if (t <= (t_real)1e-6 || t >= hit->t)
		return ;
	p = vec_add(ray.orig, vec_x_scalar(ray.dir, t));
	v = vec_sub(p, cone.point);
	v = vec_sub(v, vec_x_scalar(cone.axis, dot_product(v, cone.axis)));
	if (dot_product(v, v) > cone.radius * cone.radius)
		return ;
	if (dot_product(n, ray.dir) > (t_real)0.0)
		n = vec_x_scalar(n, (t_real)-1.0);
	hit->t = t;
	hit->p = p;
	hit->n = n;
	hit->color = cone.color;
	hit->albedo = cone.albedo;
	hit->metallic = cone.metallic;
	hit->roughness = cone.roughness;
}

static void	cone_side(t_ray ray, t_cone cone, t_hit *hit)
{
	t_vec3	apex;
	t_vec3	co;
	t_real	k;
	t_real	a;
	t_real	b;
	t_real	c;
	t_real	d;
	t_real	sqrt_d;
	t_real	t;
	t_real	y;
	t_vec3	p;
	t_vec3	n;

	apex = vec_add(cone.point, vec_x_scalar(cone.axis, cone.length));
	co = vec_sub(ray.orig, apex);
	k = (cone.radius / cone.length);
	k = k * k;
	/*
	** Quadratic for infinite cone aligned with axis:
	** Let dv = dot(d, a), cv = dot(co, a)
	** a = dot(d,d) - (1+k)*dv^2
	** b = 2*(dot(d,co) - (1+k)*dv*cv)
	** c = dot(co,co) - (1+k)*cv^2
	*/
	{
		t_real	dv;
		t_real	cv;

		dv = dot_product(ray.dir, cone.axis);
		cv = dot_product(co, cone.axis);
		a = dot_product(ray.dir, ray.dir) - ((t_real)1.0 + k) * dv * dv;
		b = (t_real)2.0 * (dot_product(ray.dir, co)
				- ((t_real)1.0 + k) * dv * cv);
		c = dot_product(co, co) - ((t_real)1.0 + k) * cv * cv;
		d = b * b - (t_real)4.0 * a * c;
		if (d < (t_real)0.0 || double_abs(a) < 1e-6)
			return ;
		sqrt_d = t_real_sqrt(d);
		t = (-b - sqrt_d) / ((t_real)2.0 * a);
		if (t <= (t_real)1e-6 || t >= hit->t)
		{
			t = (-b + sqrt_d) / ((t_real)2.0 * a);
			if (t <= (t_real)1e-6 || t >= hit->t)
				return ;
		}
		p = vec_add(ray.orig, vec_x_scalar(ray.dir, t));
		/* y measured from apex downwards */
		y = dot_product(vec_sub(apex, p), cone.axis);
		if (y < (t_real)0.0 || y > cone.length)
			return ;
		/* normal from gradient with apex-origin: n = (p - apex) + axis*(1+k)*y */
		n = vec_add(vec_sub(p, apex),
				vec_x_scalar(cone.axis, ((t_real)1.0 + k) * y));
		n = vec_normalize(n);
		if (dot_product(n, ray.dir) > (t_real)0.0)
			n = vec_x_scalar(n, (t_real)-1.0);
		hit->t = t;
		hit->p = p;
		hit->n = n;
		hit->color = cone.color;
		hit->albedo = cone.albedo;
		hit->metallic = cone.metallic;
		hit->roughness = cone.roughness;
	}
}

void	intersect_cone(t_ray ray, t_cone cone, t_hit *hit)
{
	cone_side(ray, cone, hit);
	cone_cap(ray, cone, hit);
}
