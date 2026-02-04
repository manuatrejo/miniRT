/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 03:25:50 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/04 06:17:40 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	assign_caps(t_ray ray, t_cyl cyl, t_hit *hit, t_cy_utils u)
{
	t_point	pcap;
	t_dir	v;

	pcap = vec_add(ray.orig, vec_x_scalar(ray.dir, u.t));
	v = vec_sub(pcap, cyl.point);
	v = vec_sub(v, vec_x_scalar(cyl.axis, dot_product(v, cyl.axis)));
	if (dot_product(v, v) <= cyl.radius * cyl.radius)
	{
		hit->t = u.t;
		hit->p = pcap;
		hit->n = cyl.axis;
		hit->color = cyl.color;
			hit->albedo = cyl.albedo;
			hit->metallic = cyl.metallic;
			hit->roughness = cyl.roughness;
	}
}

void	cylin_caps(t_ray ray, t_cyl cyl, t_hit *hit, t_cy_utils u)
{
	u.d = dot_product(ray.dir, cyl.axis);
	if (double_abs(u.d) < 1e-6)
		return ;
	u.t = -u.caoc / u.d;
	if (u.t > (t_real)1e-6 && u.t < hit->t)
	{
		assign_caps(ray, cyl, hit, u);
		hit->n = vec_x_scalar(hit->n, (t_real) - 1.0);
	}
	u.t = (cyl.length - u.caoc) / u.d;
	if (u.t > (t_real)1e-6 && u.t < hit->t)
		assign_caps(ray, cyl, hit, u);
}

void	cylin_sides(t_ray ray, t_cyl cyl, t_hit *hit, t_cy_utils u)
{
	t_real	y;

	if (double_abs(u.a) < 1e-6)
		return ;
	if (u.d < (t_real)0.0)
		return ;
	u.sqrt_d = t_real_sqrt(u.d);
	u.t = (-u.b - u.sqrt_d) / u.a;
	if (u.t <= (t_real)1e-6 || u.t >= hit->t)
	{
		u.t = (-u.b + u.sqrt_d) / u.a;
		if (u.t <= (t_real)1e-6 || u.t >= hit->t)
			return ;
	}
	y = u.caoc + u.t * u.card;
	if (y < (t_real)0.0 || y > cyl.length)
		return ;
	hit->t = u.t;
	hit->p = vec_add(ray.orig, vec_x_scalar(ray.dir, u.t));
	hit->n = vec_normalize(vec_sub(vec_sub(hit->p, cyl.point),
				vec_x_scalar(cyl.axis, y)));
	hit->color = cyl.color;
	hit->albedo = cyl.albedo;
	hit->metallic = cyl.metallic;
	hit->roughness = cyl.roughness;
}
