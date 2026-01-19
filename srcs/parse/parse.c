/*
Comprobar que el formato es *.rt.

La info puede estar separada por 1 o más espacios.

Los elementos con letra mayúscula solo pueden aparecer
una vez durante el parseo.

Como hacer la iluminación del bonus si solo se permite
en el parseo una luz?

Luz ambiente: A, intensidad del 0 al 1 de la luz y color

Cámara: C, coordenadas, dirección(normalizada),
y Field Of View de x grados entre 0 y 180.

Luz: L, coordenadas, brillo(0 a 1), color(bonus)

Esfera: sp, coordenadas, diámetro, color

Plano: pl, coordenadas, vector normal del plano, color

Cilindro: cy, coordenada(centro), v_dir(del eje),
diámetro, altura, color.


Necesito un atof y atoi.

Hay coordenadas, colores, tamaños y rangos.

Las coordenadas son 3 floats separados por comas.
Los colores 3 unsigned char o int de 0 a 255.
Los tamaños son floats.
Los rangos son floats que tienen que estar en un rango.
Los vectores tienen que estar siempre normalizados y 
por tanto si su tamaño no es 1 es un Error.


Como guardo la información?
Una estructura con información común y listas de objetos.
(buscar las mejores estructuras para esto)

Funciones para parsear:
	Mensajes de error cuando algo no funcione

	ATOF(libft)
	Coordenadas
	Colores
	Rangos
	Vectores
	Una línea
	Bucle que consume líneas
*/

#include "miniRT.h"

bool	parse_color(t_color *color, char *str)
{
	char	**c_split;

	c_split = ft_split(str, ',');
	if (!c_split)
		return (false);
	if (!(c_split[0] && c_split[1] && c_split[2]) || c_split[3])
		return (false);
	color->red = ft_atoi(c_split[0]);
	color->blue = ft_atoi(c_split[1]);
	color->green = ft_atoi(c_split[2]);
	if (color->red > 255 || color->red < 0 || color->blue > 255 || color->blue < 0
		|| color->green > 255 || color->green < 0)
		return (false);
	return (true);
}

bool	parse_amb_light(t_scene **scene, char **split_l)
{
	double	intensity;

	intensity = ft_atof(split_l[1]);
	if (intensity < 0.0 || intensity > 1.0)
		return (false);
	(*scene)->a_light.intensity = intensity;
	if (!parse_color(&(*scene)->a_light.color, split_l[2]))
		return (false);
}
//False cuando falla else true
bool	parse_line(t_scene **scene, char *line)
{
	char	**split_l;

	split_l = ft_split(line, ' ');
	if (!split_l)
		return (NULL);
	if (ft_strcmp(split_l[0], "A") == 0)
		return (free_str_array(split_l), parse_amb_light(scene, split_l));
	else if (ft_strcmp(split_l[0], "C") == 0)
		return (free_str_array(split_l), parse_camera(scene, split_l));
	else if (ft_strcmp(split_l[0], "L") == 0)
		return (free_str_array(split_l), parse_light(scene, split_l));
	else if (ft_strcmp(split_l[0], "sp") == 0)
		return (free_str_array(split_l), parse_sphere(scene, split_l));
	else if (ft_strcmp(split_l[0], "pl") == 0)
		return (free_str_array(split_l), parse_plane(scene, split_l));
	else if (ft_strcmp(split_l[0], "cy") == 0)
		return (free_str_array(split_l), parse_cylinder(scene, split_l));
	else if (split_l[0][0] == '\n')
		return (free_str_array(split_l), true);
	free_str_array(split_l);
	return (false);
}

t_scene	*parse_file(char *file)
{
	t_scene	*scene;
	char	*line;
	int		fd;

	if (!valid_filename(file))
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Parsing:"), NULL);
	scene = ft_calloc(sizeof(t_scene), 1);
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(&scene, line))
			return (free(line), free_scene(scene), NULL);
		free(line);
		line = get_next_line(fd);
	}
}

bool	valid_filename(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 3 || ft_strncmp(file + len - 3, ".rt", 3) != 0)
		return (false);
	return (true);
}
