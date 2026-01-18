#ifndef MINIRT_H
# define MINIRT_H
# define HEIGHT 1000
# define WIDTH 1000

# ifndef TYPE_REAL
#  define TYPE_REAL 
typedef float t_real;

# else
typedef double t_real;

# endif

# ifndef MULT_LIGHTS
#  define MULT_LIGHTS 1
# endif

typedef struct	s_coord3
{
	t_real x;
	t_real y;
	t_real z;
}	t_coord3;

typedef t_coord3	t_point;
typedef t_coord3	t_dir;

# include "libft.h"

typedef struct	s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct	s_ray
{
	t_point	orig;
	t_dir	dir;//always normalized
}	t_ray;

typedef struct	s_camera
{
	t_point	orig;
	t_dir	dir;//always normalized
	double	fov;
}	t_camera;

typedef struct	s_a_light
{
	t_real	intensity;
	t_color	color;
}	t_a_light;

typedef struct	s_light
{
	t_coord3	point;
	t_real		intensity;
	t_color		color;
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

typedef struct	s_scene
{
	t_a_light	a_light;
	t_camera	cam;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylind	*cylinder;
}	t_scene;

t_coord3	vec_add(t_coord3 vec1, t_coord3 vec2);
t_coord3	vec_sub(t_coord3 vec1, t_coord3 vec2);
t_coord3	vec_x_scalar(t_coord3 vec, t_real scalar);
t_coord3	vec_product(t_coord3 vec1, t_coord3 vec2);
t_coord3	vec_normalize(t_coord3 v);
t_real		vec_length(t_coord3 v);
t_scene		*parse_file(char *file);

#endif
