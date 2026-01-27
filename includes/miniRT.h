/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:39:47 by maanguit          #+#    #+#             */
/*   Updated: 2026/01/28 00:40:24 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# include "libft.h"
# include <math.h>
# include <fcntl.h>

# define MINIRT_H
# define HEIGHT 1000
# define WIDTH 1000

# ifndef TYPE_REAL
#  define TYPE_REAL

typedef float		t_real;

# else

typedef double		t_real;

# endif

# ifndef MULT_LIGHTS
#  define MULT_LIGHTS 1
# endif

typedef struct s_coord3
{
	t_real	x;
	t_real	y;
	t_real	z;
}	t_coord3;

typedef t_coord3	t_point;
typedef t_coord3	t_dir;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_ray
{
	t_point	orig;
	t_dir	dir;
}	t_ray;

typedef struct s_camera
{
	t_point	orig;
	t_dir	dir;
	double	fov;
	bool	defined;
}	t_camera;

typedef struct s_a_light
{
	t_real	intensity;
	t_color	color;
	bool	defined;
}	t_a_light;

typedef struct s_light
{
	t_coord3	point;
	t_real		intensity;
	t_color		color;
	bool		defined;
}	t_light;

typedef struct s_sphere
{
	t_coord3		center;
	t_real			diameter;
	t_color			color;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_plane
{
	t_coord3		point;
	t_dir			normal;
	t_color			color;
	struct s_plane	*next;
}	t_plane;

typedef struct s_cylind
{
	t_coord3		point;
	t_dir			axis;
	t_real			diameter;
	t_real			length;
	t_color			color;
	struct s_cylind	*next;
}	t_cylind;

typedef struct s_scene
{
	t_a_light	a_light;
	t_camera	cam;
	t_light		light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylind	*cylinder;
}	t_scene;

typedef struct s_vport
{
	t_real	vport_h;
	t_real	vport_w;
	t_dir	up;
	t_dir	right;
	int		w_iter;
	int		h_iter;
}	t_vport;

t_coord3	vec_add(t_coord3 vec1, t_coord3 vec2);
t_coord3	vec_sub(t_coord3 vec1, t_coord3 vec2);
t_coord3	vec_x_scalar(t_coord3 vec, t_real scalar);
t_coord3	vec_product(t_coord3 vec1, t_coord3 vec2);
t_coord3	vec_normalize(t_coord3 v);
t_coord3	vec_cross_prod(t_coord3 u, t_coord3 v);
t_real		vec_length(t_coord3 v);
bool		equal_vecs(t_dir u, t_dir v);
t_scene		*parse_file(char *file);

void		free_scene(t_scene *scene);

// Parsing helpers
bool		line_is_blank(const char *s);
bool		ensure_token_count(char **tokens, int expected);
bool		parse_positive_double(const char *s, double *out);
bool		parse_dir_normalized(t_dir *dir, char *str);
bool		parse_coord(t_coord3 *coord, char *str);
bool		parse_color(t_color *color, char *str);
bool		parse_range_double(const char *s, double min, double max,
				double *out);

// Element parsers
bool		parse_amb_light(t_scene **scene, char **split_l);
bool		parse_camera(t_scene **scene, char **split_l);
bool		parse_light(t_scene **scene, char **split_l);
bool		parse_sphere(t_scene **scene, char **split_l);
bool		parse_plane(t_scene **scene, char **split_l);
bool		parse_cylinder(t_scene **scene, char **split_l);

#endif
