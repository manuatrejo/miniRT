/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 23:48:25 by maanguit          #+#    #+#             */
/*   Updated: 2026/01/30 02:02:23 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_real	get_closest_hit(t_ray ray, t_scene scene)
{
	t_real	first_hit;//t_hit
	int		i;

	i = 0;
	first_hit = -1;//ponerle un valor grande
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

void	intersect_sphere(t_ray ray, t_sphere sphere, t_real *closer_hit)
{
	//si chocan calcular en qué punto

	//si el discriminante es > 0 el rayo choca

	
	//choca en dos puntos t = (-b +- raiz(discriminante)) / 2a
	

	//si es válido y menor que *closer_hit reasignar el valor
	
}
