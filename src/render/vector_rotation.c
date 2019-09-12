/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 15:04:18 by akulaiev          #+#    #+#             */
/*   Updated: 2018/12/20 15:04:19 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			camera_rotation(t_position *n, t_position tmp,
t_rotation ro)
{
	double		x;
	double		y;
	double		z;

	x = 0;
	y = 0;
	z = 0;
	if (ro.rot_x)
		x = (ro.rot_x * M_PI) / 180;
	if (ro.rot_y)
		y = (ro.rot_y * M_PI) / 180;
	if (ro.rot_z)
		z = (ro.rot_z * M_PI) / 180;
	tmp.x = n->x;
	tmp.y = n->y;
	tmp.z = n->z;
	n->x = tmp.x * cos(y) * cos(z) + tmp.z * sin(y) -
	tmp.y * cos(y) * sin(z);
	n->y = -tmp.z * cos(y) * sin(x) + tmp.x * (cos(z) *
	sin(x) * sin(y) + cos(x) * sin(z)) + tmp.y * (cos(x) *
	cos(z) - sin(x) * sin(y) * sin(z));
	n->z = tmp.z * cos(x) * cos(y) + tmp.x * (sin(x) *
	sin(z) - cos(x) * cos(z) * sin(y)) + tmp.y * (cos(z) *
	sin(x) + cos(x) * sin(y) * sin(z));
}

t_base			rotate_basis(t_base basis, int angle, char axis)
{
	t_rotation		rot;
	t_position		tmp;

	rot.rot_x = 0;
	rot.rot_y = 0;
	rot.rot_z = 0;
	tmp.x = 0;
	if (axis == 'x')
		rot.rot_x = angle;
	else if (axis == 'y')
		rot.rot_y = angle;
	else if (axis == 'z')
		rot.rot_z = angle;
	camera_rotation(&basis.direction_vect, tmp, rot);
	camera_rotation(&basis.up_vect, tmp, rot);
	camera_rotation(&basis.right_vect, tmp, rot);
	return (basis);
}

t_position		rotate_figure(t_object fig)
{
	t_position		tmp;

	tmp.x = 0;
	camera_rotation(&fig.direction, tmp, fig.angle);
	return (fig.direction);
}
