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

void	intersect_cone(t_ray ray, t_cone cone, t_hit *hit)
{
	t_vec3	co;
	t_real	k;
	t_real	a;
	t_real	b;
	t_real	c;
	t_real	d;
	t_real	sqrt_d;
	t_real	t;
	t_vec3	p;
	t_vec3	n;

	co = vec_sub(ray.orig, cone.point);
	k = (cone.radius / cone.length);
	k = k * k;
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
	{
		t_real t0;
		t_real t1;

		t0 = (-b - sqrt_d) / ((t_real)2.0 * a);
		t1 = (-b + sqrt_d) / ((t_real)2.0 * a);
		t = (t0 > 1e-6) ? t0 : t1;
		if (t <= 1e-6 || t >= hit->t)
			return ;
	}
	p = vec_add(ray.orig, vec_x_scalar(ray.dir, t));
	cv = dot_product(vec_sub(p, cone.point), cone.axis);
	n = vec_sub(vec_sub(p, cone.point),
			vec_x_scalar(cone.axis, ((t_real)1.0 + k) * cv));
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
