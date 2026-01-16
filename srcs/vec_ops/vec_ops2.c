#include "miniRT.h"

t_coord3	vec_normalize(t_coord3 v)
{
	t_coord3	res;
	double	len;

	len = vec_length(v);
	if (len == 0.0)
	{
		res.x = 0.0;
		res.y = 0.0;
		res.z = 0.0;
		return (res);
	}
	res.x = v.x / len;
	res.y = v.y / len;
	res.z = v.z / len;
	return (res);
}

t_coord3	vec_cross_prod(t_coord3 u, t_coord3 v)
{
	t_coord3	res;

	res.x = u.y * v.z - u.z * v.y;
	res.y = u.z * v.x - u.x * v.z;
	res.z = u.x * v.y - u.y * v.x;
	return (res);
}
