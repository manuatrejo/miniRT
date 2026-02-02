/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:39:47 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/01 22:00:13 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# include "libft.h"
# include "../minilibx-linux/mlx.h" 
# include <math.h>
# include <limits.h>
# include <X11/keysym.h>
# include <fcntl.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

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

typedef enum e_obj
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj;

typedef struct s_sphere
{
	t_coord3	center;
	t_real		radius;
	t_color		color;
}	t_sphere;

typedef struct s_sphere_list
{
	t_sphere				sphere;
	struct s_sphere_list	*next;
}	t_sphere_list;

typedef struct s_plane
{
	t_coord3	point;
	t_dir		normal;
	t_color		color;
}	t_plane;	

typedef struct s_plane_list
{
	t_plane				plane;
	struct s_plane_list	*next;
}	t_plane_list;

typedef struct s_cylind
{
	t_coord3	point;
	t_dir		axis;
	t_real		diameter;
	t_real		length;
	t_color		color;
}	t_cylind;

typedef struct s_cylind_list
{
	t_cylind				cylind;
	struct s_cylind_list	*next;
}	t_cylind_list;

typedef struct s_parse
{
	t_a_light		a_light;
	t_camera		cam;
	t_light			light;
	t_sphere_list	*sphere;
	t_plane_list	*plane;
	t_cylind_list	*cylinder;
}	t_parse;

typedef struct s_scene
{
	t_a_light	a_light;
	t_camera	cam;
	t_light		light;
	t_sphere	*sphere;
	int			n_spheres;
	t_plane		*plane;
	int			n_planes;
	t_cylind	*cylinder;
	int			n_cylinders;
}	t_scene;

typedef struct s_vport
{
	t_dir	up;
	t_dir	right;
	t_real	vport_h;
	t_real	vport_w;
	int		w_iter;
	int		h_iter;
}	t_vport;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	void	*image;
	void	*addr;
	int		bpp;
	int		line_l;
	int		endian;
}	t_mlx;

typedef struct s_hit
{
	t_dir	n;
	t_real	t;
	t_point	p;
	t_color	color;
	t_real	ref_c;
	t_obj	o_type;
}	t_hit;

t_dir	vec_add(t_dir vec1, t_dir vec2);
t_dir	vec_sub(t_dir vec1, t_dir vec2);
t_dir	vec_x_scalar(t_dir vec, t_real scalar);
t_dir	vec_div(t_dir u, t_real n);
t_real	dot_product(t_dir vec1, t_dir vec2);
t_dir	vec_normalize(t_dir v);
t_dir	vec_cross_prod(t_dir u, t_dir v);
t_real	vec_length(t_dir v);
bool	equal_vecs(t_dir u, t_dir v);
t_parse	*parse_file(char *file);
t_scene	parse_to_scene(t_parse *parse);
t_real	t_real_sqrt(t_real n);

void	free_scene(t_parse *scene);

// Parsing helpers
bool	line_is_blank(const char *s);
bool	ensure_token_count(char **tokens, int expected);
bool	parse_positive_double(const char *s, double *out);
bool	parse_dir_normalized(t_dir *dir, char *str);
bool	parse_coord(t_coord3 *coord, char *str);
bool	parse_color(t_color *color, char *str);
bool	parse_range_double(const char *s, double min, double max,
			double *out);

// Element parsers
bool	parse_amb_light(t_parse **scene, char **split_l);
bool	parse_camera(t_parse **scene, char **split_l);
bool	parse_light(t_parse **scene, char **split_l);
bool	parse_sphere(t_parse **scene, char **split_l);
bool	parse_plane(t_parse **scene, char **split_l);
bool	parse_cylinder(t_parse **scene, char **split_l);

// Image
void	image_loop(t_scene scene, t_mlx);

// Intersections
t_hit	get_closest_hit(t_ray ray, t_scene scene);

#endif
