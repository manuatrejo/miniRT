/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:39 by maanguit          #+#    #+#             */
/*   Updated: 2026/01/30 03:35:46 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int ac, char **av)
{
	t_parse	*parse;
	t_scene	scene;
	t_mlx	mlx;

	if (ac != 2)
		return (ft_putendl_fd("Error\nIncorrect args number", 2), 0);
	parse = parse_file(av[1]);//pasar de listas de objetos a arrays
	scene = parse_to_scene(parse);
	//t_parse a t_scene
	//usar struct BVH si va extremadamente lento
	
	mlx_init(&mlx);
	//inicalizar cosas de mlx
		//crear ventana e imagen
		//mlx address
		//añadir la info para print ray
	

	//
	image_loop(scene, mlx);
	//mlx_loop
	return (0);
}
