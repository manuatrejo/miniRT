/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:39 by maanguit          #+#    #+#             */
/*   Updated: 2026/01/23 19:40:58 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int ac, char **av)
{
	t_scene	*scene;

	if (ac != 2)
		return (ft_putendl_fd("Error\nIncorrect args number\n", 2), 0);
	scene = parse_file(av[1]);
}
