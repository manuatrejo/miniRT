/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:21:07 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/04 11:20:28 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	my_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_l + x * (mlx->bpp) / 8);
	*(unsigned int *)dst = color;
}

t_dir	get_dir_up(t_camera camera)
{
	static const t_dir	up = {0.0, 1.0, 0.0};
	static const t_dir	right = {1.0, 0.0, 0.0};
	static const t_dir	down = {0.0, -1.0, 0.0};

	if (equal_vecs(camera.dir, up) || equal_vecs(camera.dir, down))
		return (right);
	return (up);
}

t_dir	get_ray_dir(t_vport vport, t_dir ray_dir)
{
	t_real	mult_right;
	t_real	mult_up;

	mult_right = ((t_real)vport.w_iter - ((t_real)WIDTH / 2))
		/ ((t_real)WIDTH / 2) * vport.vport_w;
	mult_up = -(((t_real)vport.h_iter - ((t_real)HEIGHT / 2))
			/ ((t_real)HEIGHT / 2)) * vport.vport_h;
	return (vec_add(ray_dir, vec_add(vec_x_scalar(vport.right, mult_right),
				vec_x_scalar(vport.up, mult_up))));
}

bool	point_in_shadow(t_point point, t_point light_p, t_scene scene)
{//eliminar
	const t_real	eps = (t_real)1e-4;
	t_real			dist;
	t_ray			shadow;
	t_dir			dir;
	t_hit			hit;

	dir = vec_sub(light_p, point);
	dist = vec_length(dir);
	if (dist <= eps)
		return (false);
	shadow.dir = vec_div(dir, dist);
	shadow.orig = vec_add(point, vec_x_scalar(shadow.dir, eps));
	hit = get_closest_hit(shadow, scene);
	return (hit.t != INFINITE && hit.t > eps && hit.t < dist);
}

int	ray_to_color(t_ray ray, t_scene scene)
{
	t_color	color;
	t_hit	hit;
	t_dir	view_dir;

	hit = get_closest_hit(ray, scene);
	if (hit.t >= 1000000.0)
		return (0x000000);
	view_dir = vec_x_scalar(ray.dir, (t_real)-1.0);
	color = (vec_x_scalar(scene.a_light.color, scene.a_light.intensity));
	//mientras haya luces (while)
	color = vec_add(color, cook_torrance(&hit, scene.light, view_dir));
	return (color_proccessing(color));
}

//calcular iluminación path tracing
//tema de muestras y eso
int	ray_color(t_vport vport, t_scene scene)
{
	t_ray	ray;
	int		color;

	ray.orig = scene.cam.orig;
	ray.dir = scene.cam.dir;
	ray.dir = vec_normalize(get_ray_dir(vport, ray.dir));
	color = ray_to_color(ray, scene);
	return (color);
}

void	image_loop(t_scene scene, t_mlx *mlx)
{
	t_vport	vport;

	vport.right = vec_normalize(vec_cross_prod(scene.cam.dir,
			get_dir_up(scene.cam)));
	vport.up = vec_normalize(vec_cross_prod(vport.right, scene.cam.dir));
	vport.vport_h = tan(((scene.cam.fov * M_PI) / 180.0) / 2.0);
	vport.vport_w = vport.vport_h * ((t_real)WIDTH / (t_real)HEIGHT);
	vport.h_iter = 0;
	while (vport.h_iter < HEIGHT)
	{
		vport.w_iter = 0;
		while (vport.w_iter < WIDTH)
		{
			//key hook por si salen de la ventana de mlx (manejar con estado)
			my_put_pixel(mlx, vport.w_iter, vport.h_iter, ray_color(vport, scene));
			vport.w_iter++;
		}
		vport.h_iter++;
	}
	printf("finished\n");
}
