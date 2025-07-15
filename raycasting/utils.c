#include "../includes/struct.h"

double	absolute(double number)
{
	if (number < 0)
		return (-1 * number);
	return (number);
}

int close_window(void *param)
{
	(void)param;
	exit(0);
}