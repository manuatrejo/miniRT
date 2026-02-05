/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:39:47 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/05 15:54:42 by maanguit         ###   ########.fr       */
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
# define INFINITE 1e6
# ifndef SAMPLES_NUMBER
#  define SAMPLES_NUMBER 1000
# endif
# define MAX_DEPTH 2

# ifndef TYPE_REAL
#  define TYPE_REAL

typedef float		t_real;

# else

typedef double		t_real;

# endif

# ifndef MULT_LIGHTS
#  define MULT_LIGHTS 1
# endif

typedef struct s_vec3
{
	t_real	x;
	t_real	y;
	t_real	z;
}	t_vec3;

typedef t_vec3	t_point;
typedef t_vec3	t_color;
typedef t_vec3	t_dir;

typedef struct	s_rng
{
	__uint32_t state;
}	t_rng;

typedef struct s_ray
{
	t_point	orig;
	t_dir	dir;
}	t_ray;

typedef struct s_camera
{
	t_point	orig;
	t_dir	dir;
	t_real	fov;
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
	t_vec3	point;
	t_real		intensity;
	t_color		color;
	bool		defined;
}	t_light;

typedef struct s_sphere
{
	t_vec3	center;
	t_real	radius;
	t_color	color;
	t_color	albedo;
	t_real	metallic;
	t_real	roughness;
}	t_sphere;

typedef struct s_sphere_list
{
	t_sphere				sphere;
	struct s_sphere_list	*next;
}	t_sphere_list;

typedef struct s_plane
{
	t_vec3	point;
	t_dir	normal;
	t_color	color;
	t_color	albedo;
	t_real	metallic;
	t_real	roughness;
}	t_plane;	

typedef struct s_plane_list
{
	t_plane				plane;
	struct s_plane_list	*next;
}	t_plane_list;

typedef struct s_cyl
{
	t_vec3	point;
	t_dir	axis;
	t_real	radius;
	t_real	length;
	t_color	color;
	t_color	albedo;
	t_real	metallic;
	t_real	roughness;
}	t_cyl;

typedef struct s_cylind_list
{
	t_cyl					cyl;
	struct s_cylind_list	*next;
}	t_cylind_list;

typedef struct s_parse
{
	t_a_light		a_light;
	t_camera		cam;
	t_light			light;
	t_sphere_list	*sphere;
	t_plane_list	*plane;
	t_cylind_list	*cyl;
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
	t_cyl	*cylinder;
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
	t_real	metallic;
	t_real	roughness;
	t_color	albedo;
}	t_hit;

typedef struct s_cy_utils
{
	t_dir	oc;
	t_real	card;
	t_real	caoc;
	t_real	a;
	t_real	b;
	t_real	c;
	t_real	d;
	t_real	t;
	t_real	sqrt_d;
}	t_cy_utils;

typedef struct s_ct
{
	t_dir	h;
	t_dir	l_c;
	t_real	nl;
	t_real	nv;
	t_real	nh;
	t_real	vh;
	t_vec3	f0;
	t_vec3	f;
	t_real	d;
	t_real	g;
	t_real	res;
	t_vec3	specular;
	t_vec3	kd;
	t_color	diffuse;
	t_color	radiance;
}	t_ct;


t_dir	vec_add(t_dir vec1, t_dir vec2);
t_dir	vec_sub(t_dir vec1, t_dir vec2);
t_dir	vec_x_scalar(t_dir vec, t_real scalar);
t_dir	vec_prod(t_dir u, t_dir v);
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
bool	parse_positive_double(const char *s, t_real *out);
bool	parse_dir_normalized(t_dir *dir, char *str);
bool	parse_coord(t_vec3 *coord, char *str);
bool	parse_color(t_color *color, char *str);
bool	parse_range_double(const char *s, t_real min, t_real max, t_real *out);

// Element parsers
bool	parse_amb_light(t_parse **scene, char **split_l);
bool	parse_camera(t_parse **scene, char **split_l);
bool	parse_light(t_parse **scene, char **split_l);
bool	parse_sphere(t_parse **scene, char **split_l);
bool	parse_plane(t_parse **scene, char **split_l);
bool	parse_cylinder(t_parse **scene, char **split_l);
bool	p_material(t_real *r, t_real *m, t_color *albedo, char **split);

// Image
void	image_loop(t_scene scene, t_mlx *mlx);

// Intersections
t_hit	get_closest_hit(t_ray ray, t_scene *scene);
void	cylin_sides(t_ray ray, t_cyl cyl, t_hit *hit, t_cy_utils u);
void	cylin_caps(t_ray ray, t_cyl cyl, t_hit *hit, t_cy_utils u);

//Post-processing
int	color_proccessing(t_color color);

//Ilumination
t_color	cook_torrance(t_hit	*hit, t_light l, t_dir view);
t_color	trace_path(t_ray ray, t_scene *scene, t_rng *rng);

//Samples
t_rng	init_rng(int x, int y);
float	rand01(t_rng *rng);

#endif
