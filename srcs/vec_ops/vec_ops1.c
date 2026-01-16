#include "miniRT.h"

t_coord3	vec_add(t_coord3 vec1, t_coord3 vec2)
{
	t_coord3	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
}

t_coord3	vec_sub(t_coord3 vec1, t_coord3 vec2)
{
	t_coord3	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}

t_coord3	vec_x_scalar(t_coord3 vec, double scalar)
{
	t_coord3	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	result.z = vec.z * scalar;
	return (result);
}

t_coord3	vec_product(t_coord3 vec1, t_coord3 vec2)
{
	t_coord3	result;

	result.x = vec1.x * vec2.x;
	result.y = vec1.y * vec2.y;
	result.z = vec1.z * vec2.z;
	return (result);
}

t_real	vec_length(t_coord3 v)
{
	if (sizeof(t_real) == 8)
		return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}
