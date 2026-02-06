/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:39 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/06 12:57:51 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	terminate_program(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx_destroy_image(mlx->mlx, mlx->image);
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}

int	key_hook(int key, void *param)
{
	if (key == XK_Escape)
		terminate_program(param);
	return (0);
}

int	main(int ac, char **av)
{
	t_parse	*parse;
	t_scene	scene;
	t_mlx	mlx;

	if (ac != 2)
		return (ft_putendl_fd("Error\nIncorrect args number", 2), 0);
	parse = parse_file(av[1]);
	if (!parse)
		return (1);
	scene = parse_to_scene(parse);
	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "miniRT");
	mlx.image = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.image, &mlx.bpp, &mlx.line_l, &mlx.endian);
	image_loop(scene, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.window, mlx.image, 0, 0);
	mlx_hook(mlx.window, 17, 0, terminate_program, &mlx);
	mlx_key_hook(mlx.window, key_hook, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
