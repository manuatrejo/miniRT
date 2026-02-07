/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:39 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/07 16:49:08 by amonteag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	terminate_program(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	mlx_loop_end(app->mlx.mlx);
	return (0);
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
	t_app	app;

	if (ac != 2)
		return (ft_putendl_fd("Error\nIncorrect args number", 2), 0);
	parse = parse_file(av[1]);
	if (!parse)
		return (1);
	scene = parse_to_scene(parse);
	app.scene = &scene;
	app.mlx.mlx = mlx_init();
	app.mlx.window = mlx_new_window(app.mlx.mlx, WIDTH, HEIGHT, "miniRT");
	app.mlx.image = mlx_new_image(app.mlx.mlx, WIDTH, HEIGHT);
	app.mlx.addr = mlx_get_data_addr(app.mlx.image, &app.mlx.bpp,
			&app.mlx.line_l, &app.mlx.endian);
	image_loop(scene, &app.mlx);
	mlx_put_image_to_window(app.mlx.mlx, app.mlx.window, app.mlx.image, 0, 0);
	mlx_hook(app.mlx.window, 17, 0, terminate_program, &app);
	mlx_key_hook(app.mlx.window, key_hook, &app);
	mlx_loop(app.mlx.mlx);
	mlx_destroy_image(app.mlx.mlx, app.mlx.image);
	mlx_destroy_window(app.mlx.mlx, app.mlx.window);
	mlx_destroy_display(app.mlx.mlx);
	return (free_runtime_scene(&scene), free(app.mlx.mlx), 0);
}
