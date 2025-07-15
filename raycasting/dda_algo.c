#include "../includes/struct.h"

static void	init_dda(t_raygrid_data *data, t_motion *position, t_motion *ray)
{
	if (ray->y < 0)
	{
		data->step_of_y = -1;
		data->ray_len_y = (position->y - data->y) * data->dda_increment_y;
	}
	else
	{
		data->step_of_y = 1;
		data->ray_len_y = (data->y + 1.0 - position->y) * data->dda_increment_y;
	}
	if (ray->x < 0)
	{
		data->step_of_x = -1;
		data->ray_len_x = (position->x - data->x) * data->dda_increment_x;
	}
	else
	{
		data->step_of_x = 1;
		data->ray_len_x = (data->x + 1.0 - position->x) * data->dda_increment_x;
	}
}

static void	start_dda(t_raygrid_data *data, t_dda *result, double angle, char **map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->ray_len_x < data->ray_len_y)
		{
			data->ray_len_x += data->dda_increment_x;
			data->x += data->step_of_x;
			result->dir = 0 + (data->step_of_x + 1);
		}
		else
		{
			data->ray_len_y += data->dda_increment_y;
			data->y += data->step_of_y;
			result->dir = 1 + (data->step_of_y + 1);
		}
		if (map[data->y][data->x] == '1')
			hit = 1;
	}
	if (result->dir == EAST || result->dir == WEST)
		result->range = (data->ray_len_x - data->dda_increment_x);
	else
		result->range = (data->ray_len_y - data->dda_increment_y);
	result->view_dist = cos((angle / 180) * M_PI) * result->range;
}

t_dda	apply_dda(t_motion pos_player, t_motion ray, double angle, char **map)
{
	t_raygrid_data	dda_vars;
	t_dda		result;

	dda_vars.y = (int) pos_player.y;
	dda_vars.x = (int) pos_player.x;
	dda_vars.dda_increment_x = absolute(1 / ray.x);
	dda_vars.dda_increment_y = absolute(1 / ray.y);
	init_dda(&dda_vars, &pos_player, &ray);
	start_dda(&dda_vars, &result, angle, map);
	if (result.dir == EAST || result.dir == WEST)
		result.position = pos_player.y + result.range * ray.y;
	else
		result.position = pos_player.x + result.range * ray.x;
	result.position -= floorf(result.position);
	return (result);
}
