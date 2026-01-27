/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:21:07 by maanguit          #+#    #+#             */
/*   Updated: 2026/01/28 00:38:10 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
una función que defina el valor up de una u otra forma dependiendo de si la
dirección de la cámara es up o -up
*/
t_dir	get_vector_up(t_camera camera)
{
	static const t_dir	up = {0.0f, 1.0f, 0.0f};
	static const t_dir	right = {1.0f, 0.0f, 0.0f};
	static const t_dir	down = {0.0f, -1.0f, 0.0f};

	if (equal_vecs(camera.dir, up) || equal_vecs(camera.dir, down))
		return (right);
	return (up);
}

void	print_ray(t_vport vport, t_scene scene)
{
	//calcular t_dir del rayo actual(lanzar múltiples rayos para mejor imagen)
	
	//comprobar si choca
	//calcular iluminación path tracing

	//imprimir color del objeto
}

/*
Necesito los vectores up y right

Calcular el alto/2 y ancho/2 del plano proyección

up y right * alto/2 y ancho/2

Calcular valor entre -1 y 1 dependiendo de i y j
-1 para el píxel 0
0 para píxel TAMAÑO/2
1 para TAMAÑO -1

(pixel - TAMAÑO/2) / (TAMAÑO/2)

Para obtener la posición del píxel:
cam_dir + rango * vector dirección up-down
*/
void	image_loop(t_scene scene)
{
	t_vport	vport;
			
	vport.h_iter = 0;
	vport.right = vec_cross_prod(get_vector_up(scene.cam), scene.cam.dir);
	vport.up = vec_cross_prod(vport.right, scene.cam.dir);
	vport.vport_h = tan(((scene.cam.fov * M_PI) / 180.0f) / 2.0f);
	vport.vport_w = vport.vport_h * ((float)WIDTH / (float)HEIGHT);
	while (vport.h_iter < HEIGHT)
	{
		vport.w_iter = 0;
		while (vport.w_iter < WIDTH)
		{
			print_ray(vport, scene);			
			vport.w_iter++;
		}//mlx_loop por aquí?
		vport.h_iter++;
	}
}
