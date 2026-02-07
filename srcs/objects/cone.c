/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:49:14 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/07 18:30:19 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	assign_to_cone(t_cone cone, t_hit *hit, t_real t)
{
	hit->t = t;
	hit->color = cone.color;
	hit->albedo = cone.albedo;
	hit->metallic = cone.metallic;
	hit->roughness = cone.roughness;
}

static void	cone_utils(t_ray ray, t_cone cone, t_obj_utils *u)
{
	u->oc = vec_sub(ray.orig, cone.point);
	u->card = dot_product(ray.dir, cone.axis);
	u->caoc = dot_product(u->oc, cone.axis);
	u->a = dot_product(ray.dir, ray.dir) - (t_real)2.0 * u->card * u->card;
	u->b = (t_real)2.0 * (dot_product(ray.dir, u->oc)
			- (t_real)2.0 * u->card * u->caoc);
	u->c = dot_product(u->oc, u->oc) - (t_real)2.0 * u->caoc * u->caoc;
	u->d = u->b * u->b - (t_real)4.0 * u->a * u->c;
}

static bool	cone_hit_t(t_obj_utils u, t_real *t)
{
	if (u.d < (t_real)0.0 || double_abs(u.a) < (t_real)1e-6)
		return (false);
	u.sqrt_d = t_real_sqrt(u.d);
	u.t = (-u.b - u.sqrt_d) / ((t_real)2.0 * u.a);
	if (u.t <= (t_real)1e-6)
		u.t = (-u.b + u.sqrt_d) / ((t_real)2.0 * u.a);
	if (u.t <= (t_real)1e-6)
		return (false);
	*t = u.t;
	return (true);
}

static t_dir	cone_normal(t_cone cone, t_point p)
{
	t_dir	v;
	t_real	m;

	v = vec_sub(p, cone.point);
	m = dot_product(v, cone.axis);
	return (vec_normalize(vec_sub(v,
				vec_x_scalar(cone.axis, (t_real)2.0 * m))));
}

void	intersect_cone(t_ray ray, t_cone cone, t_hit *hit)
{
	t_obj_utils	u;
	t_real		t;

	cone_utils(ray, cone, &u);
	if (!cone_hit_t(u, &t) || t >= hit->t)
		return ;
	hit->p = vec_add(ray.orig, vec_x_scalar(ray.dir, t));
	hit->n = cone_normal(cone, hit->p);
	if (dot_product(hit->n, ray.dir) > (t_real)0.0)
		hit->n = vec_x_scalar(hit->n, (t_real) - 1.0);
	assign_to_cone(cone, hit, t);
}
