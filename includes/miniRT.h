/*
Plantear estructuras

Rayos con origen(3d), dirección (3d).

Objetos con distintas propiedades

Cámara(coordenadas), zoom
*/
#ifndef MINIRT_H
# define MINIRT_H
# define HEIGHT 1000
# define WIDTH 1000

# ifndef TYPE_REAL
# define TYPE_REAL 
typedef float t_real;

# else
typedef double t_real;

# endif

typedef struct	s_coord3
{
	t_real x;
	t_real y;
	t_real z;
}	t_coord3;

typedef t_coord3	t_point3;
typedef t_coord3	t_sphere;
typedef t_coord3	t_orig;
typedef t_coord3	t_dir;

typedef struct	s_ray
{
	t_orig	orig;
	t_dir	dir;//always normalized
}	t_ray;

typedef struct	s_camera
{
	t_orig	orig;
	t_dir	dir;//always normalized
	double	fov;
}	t_camera;

t_coord3	vec_add(t_coord3 vec1, t_coord3 vec2);
t_coord3	vec_sub(t_coord3 vec1, t_coord3 vec2);
t_coord3	vec_x_scalar(t_coord3 vec, t_real scalar);
t_coord3	vec_product(t_coord3 vec1, t_coord3 vec2);
t_coord3	vec_normalize(t_coord3 v);
t_real		vec_length(t_coord3 v);

#endif
