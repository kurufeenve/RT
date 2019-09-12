/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_advanced.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 17:41:57 by akulaiev          #+#    #+#             */
/*   Updated: 2018/12/26 17:41:58 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		elliptic_paraboloid_intersection(t_object *paraboloid, t_ray ray,
t_intersection *its)
{
	t_quadratic	p;

	its->parabol_kernel_dist = 0.75;
	p.a = vector_scalar(ray.direction, ray.direction) -
	pow(vector_scalar(ray.direction, paraboloid->direction), 2);
	p.delta_p = vector_subtract(ray.origin, paraboloid->pos);
	p.b = (vector_scalar(ray.direction, p.delta_p) -
	vector_scalar(ray.direction, paraboloid->direction) *
	(vector_scalar(p.delta_p, paraboloid->direction) + 2
	* its->parabol_kernel_dist)) * 2;
	p.c = vector_scalar(p.delta_p, p.delta_p) -
	vector_scalar(p.delta_p, paraboloid->direction) *
	(vector_scalar(p.delta_p, paraboloid->direction) +
	4 * its->parabol_kernel_dist);
	return (solve_quadratic(p, its, 0.0));
}

int		hyperbolic_paraboloid_intersection(t_object *paraboloid, t_ray ray,
t_intersection *its)
{
	double		a;
	t_quadratic	p;

	a = 1.5;
	ray.origin = vector_subtract(ray.origin, paraboloid->pos);
	p.a = ray.direction.x * ray.direction.x - ray.direction.z *
	ray.direction.z;
	p.b = 2 * (ray.direction.x * ray.origin.x - ray.direction.z *
	ray.origin.z - a * a * ray.direction.y);
	p.c = ray.origin.x * ray.origin.x - ray.origin.z * ray.origin.z -
	2 * a * a * ray.origin.y;
	return (solve_quadratic(p, its, 0.0));
}

int		ellipsoid_intersection(t_object *ellipsoid, t_ray ray,
t_intersection *its)
{
	t_quadratic	e;
	double		a1;
	double		a2;

	ellipsoid->ellips_a = ellipsoid->radius / 2;
	ellipsoid->ellips_k = ellipsoid->radius * 0.9;
	ellipsoid->ellips_c = ellipsoid->ellips_k / 2;
	ellipsoid->ellips_b = sqrt(ellipsoid->ellips_a * ellipsoid->ellips_a -
	ellipsoid->ellips_c * ellipsoid->ellips_c);
	ellipsoid->pos2 = vector_add(ellipsoid->pos,
	vector_mult(ellipsoid->direction, ellipsoid->ellips_k));
	ellipsoid->pos_mid = vector_add(ellipsoid->pos,
	vector_mult(ellipsoid->direction, ellipsoid->ellips_c));
	e.delta_p = vector_subtract(ray.origin, ellipsoid->pos);
	a1 = 2 * ellipsoid->ellips_k * vector_scalar(ray.direction,
	ellipsoid->direction);
	a2 = pow(ellipsoid->radius, ellipsoid->radius) + 2 * ellipsoid->ellips_k *
	vector_scalar(e.delta_p, ellipsoid->direction) - ellipsoid->ellips_k;
	e.a = 4 * pow(ellipsoid->radius, ellipsoid->radius) *
	vector_scalar(ray.direction, ray.direction) - a1 * a1;
	e.b = 2 * (4 * pow(ellipsoid->radius, ellipsoid->radius) *
	vector_scalar(ray.direction, e.delta_p) - a1 * a2);
	e.c = 4 * pow(ellipsoid->radius, ellipsoid->radius) *
	vector_scalar(e.delta_p, e.delta_p) - a2 * a2;
	return (solve_quadratic(e, its, 0.0));
}

int		torus_intersection(t_object *torus, t_ray ray,
t_intersection *its)
{
	t_quadratic	t;
	t_torus		tr;

	torus->small_radius = torus->radius / 2;
	ray.origin = vector_subtract(ray.origin, torus->pos);
	tr.dir_scalar = vector_scalar(ray.direction, ray.direction);
	tr.dir_origin = vector_scalar(ray.direction, ray.origin);
	tr.origin_scalar = vector_scalar(ray.origin, ray.origin);
	tr.radiuses_sum = torus->small_radius * torus->small_radius +
	torus->radius * torus->radius;
	tr.ray_torus_dir = vector_scalar(ray.direction, torus->direction);
	tr.ray_origin_torus_dir = vector_scalar(ray.origin, torus->direction);
	t.e = tr.dir_scalar * tr.dir_scalar;
	t.d = 4 * tr.dir_scalar * tr.dir_origin;
	t.c = 2 * tr.dir_scalar * (tr.origin_scalar - tr.radiuses_sum) + 4 *
	(tr.dir_origin * tr.dir_origin) + 4 * torus->radius * torus->radius *
	tr.ray_torus_dir * tr.ray_torus_dir;
	t.b = 4 * (tr.origin_scalar - tr.radiuses_sum) * tr.dir_origin + 8 *
	torus->radius * torus->radius * tr.ray_torus_dir * tr.ray_origin_torus_dir;
	t.a = (tr.origin_scalar - tr.radiuses_sum) * (tr.origin_scalar -
	tr.radiuses_sum) - 4 * torus->radius * torus->radius *
	(torus->small_radius * torus->small_radius - tr.ray_origin_torus_dir *
	tr.ray_origin_torus_dir);
	return (solve_quartic(t, its));
}

int		box_intersection(t_object *box, t_ray ray,
t_intersection *its)
{
	t_box		b;

	b.inverted_dir.x = 1 / ray.direction.x;
	b.inverted_dir.y = 1 / ray.direction.y;
	b.inverted_dir.z = 1 / ray.direction.z;
	b.sign[0] = (b.inverted_dir.x < 0);
	b.sign[1] = (b.inverted_dir.y < 0);
	b.sign[2] = (b.inverted_dir.z < 0);
	b.borders[0] = box->pos;
	b.borders[1] = box->pos2;
	its->t = (b.borders[b.sign[0]].x - ray.origin.x) * b.inverted_dir.x;
	b.tmax = (b.borders[1 - b.sign[0]].x - ray.origin.x) * b.inverted_dir.x;
	b.tymin = (b.borders[b.sign[1]].y - ray.origin.y) * b.inverted_dir.y;
	b.tymax = (b.borders[1 - b.sign[1]].y - ray.origin.y) * b.inverted_dir.y;
	if ((its->t > b.tymax) || (b.tymin > b.tmax))
		return (0);
	b.tymin > its->t ? its->t = b.tymin : 0;
	b.tymax < b.tmax ? b.tmax = b.tymax : 0;
	b.tzmin = (b.borders[b.sign[2]].z - ray.origin.z) * b.inverted_dir.z;
	b.tzmax = (b.borders[1 - b.sign[2]].z - ray.origin.z) * b.inverted_dir.z;
	if ((its->t > b.tzmax) || (b.tzmin > b.tmax))
		return (0);
	b.tzmin > its->t ? its->t = b.tzmin : 0;
	b.tzmax < b.tmax ? b.tmax = b.tzmax : 0;
	return (its->t > 0.00001);
}
