/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:22 by maanguit          #+#    #+#             */
/*   Updated: 2026/01/31 00:23:32 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
Parseo de escena .rt

Elementos esperados:
A  <ratio 0..1> <R,G,B 0..255>
C  <x,y,z>      <nx,ny,nz normalizado> <fov 0..180>
L  <x,y,z>      <ratio 0..1>           <R,G,B 0..255>
sp <x,y,z>      <diametro >0>          <R,G,B 0..255>
pl <x,y,z>      <nx,ny,nz normalizado> <R,G,B 0..255>
cy <x,y,z>      <nx,ny,nz normalizado> <diametro >0> <altura >0> <R,G,B 0..255>

Notas:
- Ignora líneas vacías o con solo espacios.
- A, C y L solo pueden aparecer una vez.
*/
static bool	valid_filename(char *file)
{
	int	len;

	if (!file)
		return (false);
	len = ft_strlen(file);
	if (len < 3 || ft_strcmp(file + len - 3, ".rt") != 0)
		return (false);
	return (true);
}

static bool	parse_line(t_parse **scene, char *line)
{
	char	**split_l;

	if (line_is_blank(line))
		return (true);
	split_l = ft_split(line, ' ');
	if (!split_l)
		return (false);
	if (!split_l[0])
		return (free_str_array(split_l), true);
	if ((ft_strcmp(split_l[0], "A") == 0 && parse_amb_light(scene, split_l))
		|| (ft_strcmp(split_l[0], "C") == 0 && parse_camera(scene, split_l))
		|| (ft_strcmp(split_l[0], "L") == 0 && parse_light(scene, split_l))
		|| (ft_strcmp(split_l[0], "sp") == 0 && parse_sphere(scene, split_l))
		|| (ft_strcmp(split_l[0], "pl") == 0 && parse_plane(scene, split_l))
		|| (ft_strcmp(split_l[0], "cy") == 0 && parse_cylinder(scene, split_l)))
		return (free_str_array(split_l), true);
	return (ft_putendl_fd("Error:\nBad line", 2), free_str_array(split_l) ,false);
}

t_parse	*parse_file(char *file)
{
	t_parse	*scene;
	char	*line;
	int		fd;

	if (!valid_filename(file))
		return (ft_putendl_fd("Error: file must end with .rt", 2), NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Parsing"), NULL);
	scene = ft_calloc(1, sizeof(t_parse));
	if (!scene)
		return (close(fd), NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(&scene, line))
			return (free(line), free_scene(scene), close(fd), NULL);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!scene->a_light.defined || !scene->cam.defined)
		return (ft_putendl_fd("Error: scene needs at least A and C", 2),
			free_scene(scene), NULL);
	return (scene);
}
