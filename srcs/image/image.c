/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:21:07 by maanguit          #+#    #+#             */
/*   Updated: 2026/01/30 03:36:22 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_dir	get_dir_up(t_camera camera)
{
	static const t_dir	up = {0.0f, 1.0f, 0.0f};
	static const t_dir	right = {1.0f, 0.0f, 0.0f};
	static const t_dir	down = {0.0f, -1.0f, 0.0f};

	if (equal_vecs(camera.dir, up) || equal_vecs(camera.dir, down))
		return (right);
	return (up);
}

t_dir	get_ray_dir(t_vport vport, t_dir ray_dir)
{
	t_real	mult_right;
	t_real	mult_up;//números entre 0 y 1

	mult_right = ((t_real)vport.w_iter - ((t_real)WIDTH / 2)) /
		((t_real)WIDTH / 2);
	mult_up = -(((t_real)vport.h_iter - ((t_real)HEIGHT / 2)) /
		((t_real)HEIGHT / 2));
	return (vec_add(ray_dir, vec_add(vec_x_scalar(vport.right, mult_right),
		vec_x_scalar(vport.up, mult_up))));
}

int	ray_to_color(t_ray ray, t_scene scene)
{
	//comprobar con cual de todos los objetos choca antes

	//guardar el tipo de objeto, color, punto de choque y la normal
}

int	ray_color(t_vport vport, t_scene scene)//devuelve el color completo
{
	t_ray	ray;
	int		color;

	ray.orig = scene.cam.orig;
	ray.dir = scene.cam.dir;
	//calcular t_dir del rayo actual(lanzar múltiples rayos para mejor imagen)
	ray.dir = vec_normalize(get_ray_dir(vport, ray.dir));
	color = ray_to_color(ray, scene);
	
	//comprobar intersección
	//calcular iluminación path tracing
	//tema de muestras y eso

	return (color);
}

void	image_loop(t_scene scene, t_mlx mlx)
{
	t_vport	vport;
			
	vport.right = vec_cross_prod(get_dir_up(scene.cam), scene.cam.dir);
	vport.up = vec_cross_prod(vport.right, scene.cam.dir);
	vport.vport_h = tan(((scene.cam.fov * M_PI) / 180.0f) / 2.0f);
	vport.vport_w = vport.vport_h * ((t_real)WIDTH / (t_real)HEIGHT);
	vport.h_iter = 0;
	while (vport.h_iter < HEIGHT)
	{
		vport.w_iter = 0;
		while (vport.w_iter < WIDTH)
		{
			//key hook por si salen de la ventana de mlx
			my_put_pixel(mlx, vport.w_iter, vport.h_iter, ray_color(vport, scene));
			vport.w_iter++;
		}
		vport.h_iter++;
	}
}
