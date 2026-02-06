/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:10:58 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/06 23:30:16 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	ambient_radiance(t_scene *scene)
{
	if (!scene->a_light.defined)
		return ((t_color){0.0, 0.0, 0.0});
	return (vec_x_scalar(scene->a_light.color, scene->a_light.intensity));
}

bool	in_shadow(t_scene *scene, t_hit hit, t_dir ldir, t_real dist)
{
	t_ray	shadow;
	t_hit	occ;

	shadow.orig = vec_add(hit.p, vec_x_scalar(hit.n, (t_real)1e-3));
	shadow.dir = ldir;
	occ = get_closest_hit(shadow, scene);
	if (occ.t < dist - (t_real)1e-4)
		return (true);
	return (false);
}

t_color	direct_light(t_scene *scene, t_hit hit, t_dir wo)
{
	t_dir	ldir;
	t_real	dist;
	t_real	nl;
	t_color	radiance;

	if (!scene->light.defined)
		return ((t_color){0.0, 0.0, 0.0});
	ldir = vec_sub(scene->light.point, hit.p);
	dist = vec_length(ldir);
	if (dist <= (t_real)0.0)
		return ((t_color){0.0, 0.0, 0.0});
	ldir = vec_div(ldir, dist);
	nl = fmax(dot_product(hit.n, ldir), (t_real)0.0);
	if (nl <= (t_real)0.0)
		return ((t_color){0.0, 0.0, 0.0});
	if (in_shadow(scene, hit, ldir, dist))
		return ((t_color){0.0, 0.0, 0.0});
	radiance = vec_x_scalar(scene->light.color, scene->light.intensity);
	return (vec_x_scalar(vec_prod(brdf_eval(hit, hit.n, wo, ldir),
				radiance), nl));
}
