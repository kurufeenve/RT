/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_basic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 17:40:19 by akulaiev          #+#    #+#             */
/*   Updated: 2018/12/26 17:40:20 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		get_closest_shape(t_thread *data, t_ray ray, t_intersection *its)
{
	int			col;

	its->closest_t = INFINITY;
	col = blinn_phong_shading(0, data, ray, its).color;
	return (col);
}

int		cylinder_intersection(t_object *cylinder, t_ray ray,
t_intersection *its)
{
	t_quadratic	c;

	c.ray = ray;
	c.figure = *cylinder;
	c.delta_p = vector_subtract(ray.origin, cylinder->pos);
	c.tmp = vector_subtract(ray.direction,
	vector_mult(cylinder->direction, vector_scalar(ray.direction,
	cylinder->direction)));
	c.tmp1 = vector_subtract(c.delta_p, vector_mult(cylinder->direction,
	vector_scalar(c.delta_p, cylinder->direction)));
	c.a = vector_scalar(c.tmp, c.tmp);
	c.b = 2 * vector_scalar(c.tmp, c.tmp1);
	c.c = vector_scalar(c.tmp1, c.tmp1) - (cylinder->radius * cylinder->radius);
	return (solve_quadratic(c, its, cylinder->height));
}

int		cone_intersection(t_object *cone, t_ray ray, t_intersection *its)
{
	t_quadratic	c;

	c.ray = ray;
	c.figure = *cone;
	c.delta_p = vector_subtract(ray.origin, cone->pos);
	c.tmp = vector_subtract(ray.direction, vector_mult(cone->direction,
	vector_scalar(ray.direction, cone->direction)));
	c.tmp1 = vector_subtract(c.delta_p, vector_mult(cone->direction,
	vector_scalar(c.delta_p, cone->direction)));
	c.a = pow(cos(cone->cone_angle), 2) * vector_scalar(c.tmp, c.tmp) -
	pow(sin(cone->cone_angle), 2) *
	pow(vector_scalar(ray.direction, cone->direction), 2);
	c.b = 2 * pow(cos(cone->cone_angle), 2) * vector_scalar(c.tmp, c.tmp1) -
	2 * pow(sin(cone->cone_angle), 2) *
	vector_scalar(ray.direction, cone->direction) *
	vector_scalar(c.delta_p, cone->direction);
	c.c = pow(cos(cone->cone_angle), 2) * vector_scalar(c.tmp1, c.tmp1)
	- (cone->radius * cone->radius) -
	pow(sin(cone->cone_angle), 2) *
	pow(vector_scalar(c.delta_p, cone->direction), 2);
	return (solve_quadratic(c, its, cone->height));
}

int		sphere_intersection(t_object *sphere, t_ray ray, t_intersection *its)
{
	t_quadratic	s;

	s.delta_p = vector_subtract(ray.origin, sphere->pos);
	s.a = vector_scalar(ray.direction, ray.direction);
	s.b = (vector_scalar(ray.direction, s.delta_p)) * 2;
	s.c = vector_scalar(s.delta_p, s.delta_p) - pow(sphere->radius, 2);
	return (solve_quadratic(s, its, 0.0));
}

int		plane_intersection(t_object *plane, t_ray ray, t_intersection *its)
{
	double			denom;
	t_position		diff;
	double			diff2;

	its->normal = plane->direction;
	denom = vector_scalar(its->normal, ray.direction);
	if (fabs(denom) > 0.00001)
	{
		diff = vector_subtract(plane->pos, ray.origin);
		its->t = vector_scalar(diff, its->normal) / denom;
		if (its->t > 0.00001)
		{
			if (plane->radius > 0.00001)
			{
				diff2 = vector_len(vector_subtract(plane->pos,
				vector_add(ray.origin, vector_mult(ray.direction, its->t))));
				if (diff2 > plane->radius)
					return (0);
			}
			if (denom >= 0 && its->closest_t != -INFINITY)
				its->normal = vector_mult(its->normal, -1);
			return (1);
		}
	}
	return (0);
}
