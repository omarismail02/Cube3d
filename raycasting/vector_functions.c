#include "../includes/struct.h"

t_coordinates	vec_to_coor(t_motion vec)
{
	t_coordinates	temp_coor;

	temp_coor.x = (int) vec.x;
	temp_coor.y = (int) vec.y;
	return (temp_coor);
}

t_motion	add_vectors(t_motion vec1, t_motion vec2)
{
	t_motion	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	return (result);
}

t_motion	subtract_vectors(t_motion vec1, t_motion vec2)
{
	t_motion	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	return (result);
}

t_motion	rotate_vector(t_motion vec, double degree)
{
	double		radians;
	t_motion	result;

	radians = (-degree / 180.0) * M_PI;
	result.x = vec.x * cos(radians) - vec.y * sin(radians);
	result.y = vec.x * sin(radians) + vec.y * cos(radians);
	return (result);
}
