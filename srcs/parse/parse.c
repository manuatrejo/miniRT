/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:22 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/07 17:22:51 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	return (free_str_array(split_l), false);
}

t_parse	*parse_file(char *file)
{
	t_parse	*scene;
	char	*line;
	int		fd;

	if (!valid_filename(file))
		return (ft_putendl_fd("Error:\n file must end with .rt", 2), NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Parsing"), NULL);
	scene = ft_calloc(1, sizeof(t_parse));
	if (!scene)
		return (close(fd), NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(&scene, replace(line, '\n', 0)))
			return (free(line), free_scene(scene), close(fd), NULL);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!scene->a_light.defined || !scene->cam.defined)
		return (ft_putendl_fd("Error:\n scene needs at least A and C", 2),
			free_scene(scene), NULL);
	return (scene);
}
