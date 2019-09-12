/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_parameters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 18:12:40 by akulaiev          #+#    #+#             */
/*   Updated: 2019/03/29 18:12:41 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			box_cylinder(t_object f, t_intersection *i)
{
	if (!ft_strcmp(f.object, "cube"))
	{
		i->normal.x = 0;
		i->normal.y = 0;
		i->normal.z = 0;
		if (fabs(i->its_point.x - f.pos.x) < 0.00001)
			i->normal.x = -1;
		else if (fabs(i->its_point.x - f.pos2.x) < 0.00001)
			i->normal.x = 1;
		else if (fabs(i->its_point.y - f.pos.y) < 0.00001)
			i->normal.y = -1;
		else if (fabs(i->its_point.y - f.pos2.y) < 0.00001)
			i->normal.y = 1;
		else if (fabs(i->its_point.z - f.pos.z) < 0.00001)
			i->normal.z = -1;
		else if (fabs(i->its_point.z - f.pos2.z) < 0.00001)
			i->normal.z = 1;
	}
	else if (!ft_strcmp(f.object, "cylinder"))
		i->normal = vector_subtract(vector_subtract(i->its_point, f.pos),
		vector_mult(f.direction, vector_scalar(f.direction,
		vector_subtract(i->its_point, f.pos))));
}

static void			get_its_params_2(t_object f, t_intersection *i)
{
	t_position		delta;
	double			y;
	t_position		d;
	t_position		x;

	if (!ft_strcmp(f.object, "ellipsoid"))
	{
		delta = vector_subtract(i->its_point, f.pos_mid);
		i->normal = vector_subtract(delta, vector_mult(vector_mult(f.direction,
		(1 - f.ellips_b * f.ellips_b / f.ellips_a * f.ellips_a)),
		vector_scalar(delta, f.direction)));
	}
	else if (!ft_strcmp(f.object, "torus"))
	{
		d = vector_subtract(i->its_point, f.pos);
		y = vector_scalar(d, f.direction);
		x = vector_subtract(d, vector_mult(f.direction, y));
		normalize(&x);
		x = vector_mult(x, f.radius);
		i->normal = vector_subtract(d, x);
	}
	else if (!ft_strcmp(f.object, "sphere"))
		i->normal = vector_subtract(i->its_point, f.pos);
	else
		box_cylinder(f, i);
}

void				get_its_params(t_object f, t_ray r, t_intersection *i)
{
	t_position		tmp;
	double			m;

	i->its_point = vector_add(r.origin, vector_mult(r.direction, i->t));
	if (!ft_strcmp(f.object, "cone"))
	{
		tmp = vector_subtract(i->its_point, f.pos);
		tmp = vector_add(f.pos, vector_mult(f.direction,
		vector_scalar(f.direction, tmp)));
		i->normal = vector_subtract(i->its_point, tmp);
	}
	else if (!ft_strcmp(f.object, "elliptic_paraboloid") ||
	!ft_strcmp(f.object, "hyperbolic_paraboloid"))
	{
		m = vector_scalar(vector_subtract(i->its_point, f.pos), f.direction);
		i->normal = vector_subtract(i->its_point, f.pos);
		i->normal = vector_subtract(i->normal,
		vector_mult(f.direction, i->parabol_kernel_dist + m));
	}
	else
		get_its_params_2(f, i);
	normalize(&i->normal);
}
