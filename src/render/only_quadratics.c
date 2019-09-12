/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_quadratics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 17:58:58 by akulaiev          #+#    #+#             */
/*   Updated: 2019/02/11 17:58:59 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			solve_quadratic(t_quadratic var, t_intersection *its,
double height)
{
	double	m;

	var.discriminant = pow(var.b, 2) - 4 * var.a * var.c;
	if (var.discriminant < 0 || (var.a == 0 && var.b == 0))
		return (0);
	its->t0 = (-var.b - sqrt(var.discriminant)) / (2 * var.a);
	its->t1 = (-var.b + sqrt(var.discriminant)) / (2 * var.a);
	if (height > 0.00001)
	{
		m = vector_scalar(var.ray.direction, var.figure.direction) *
		its->t0 + vector_scalar(var.delta_p, var.figure.direction);
		if (m > var.figure.height || m <= 0.00001)
			its->t0 = 0;
		m = vector_scalar(var.ray.direction, var.figure.direction) *
		its->t1 + vector_scalar(var.delta_p, var.figure.direction);
		if (m > var.figure.height || m <= 0.00001)
			its->t1 = 0;
	}
	if (its->t0 > 0.00001 && its->t1 > 0.00001)
		its->t = fmin(its->t0, its->t1);
	else
		its->t = fmax(its->t0, its->t1);
	return (its->t > 0.00001);
}

int				solve_quadratic_two(double c[3], double s[2])
{
	double	p;
	double	q;
	double	d;
	double	sqrt_d;

	p = c[1] / (2 * c[2]);
	q = c[0] / c[2];
	d = p * p - q;
	if (d > -1e-9 && d < 1e-9)
	{
		s[0] = -p;
		return (1);
	}
	else if (d < 0)
		return (0);
	else
	{
		sqrt_d = sqrt(d);
		s[0] = sqrt_d - p;
		s[1] = -sqrt_d - p;
		return (2);
	}
}
