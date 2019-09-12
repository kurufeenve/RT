/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_equations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:18:30 by akulaiev          #+#    #+#             */
/*   Updated: 2019/01/24 15:18:32 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void				solve_cubic_help(t_quadratic *var, double phi,
double t, double s[3])
{
	if (var->discriminant > -1e-9 && var->discriminant < 1e-9)
	{
		if (var->q > -1e-9 && var->q < 1e-9 && (s[0] = 0))
			var->num = 1;
		else if ((var->q < -1e-9 || var->q > 1e-9) && (var->num = 2))
		{
			var->u = cbrt(-var->q);
			s[0] = 2 * var->u;
			s[1] = -var->u;
		}
	}
	else if (var->discriminant < 0 && (var->num = 3))
	{
		s[0] = t * cos(phi);
		s[1] = -t * cos(phi + M_PI / 3);
		s[2] = -t * cos(phi - M_PI / 3);
	}
	else
	{
		var->sqrt_d = sqrt(var->discriminant);
		var->u = cbrt(var->sqrt_d - var->q);
		var->v = -cbrt(var->sqrt_d + var->q);
		s[0] = var->u + var->v;
		var->num = 1;
	}
}

static int				solve_cubic(double c[4], double s[3])
{
	t_quadratic var;

	var.a = c[2] / c[3];
	var.b = c[1] / c[3];
	var.c = c[0] / c[3];
	var.sq_a = var.a * var.a;
	var.p = 1.0 / 3 * (-1.0 / 3 * var.sq_a + var.b);
	var.q = 1.0 / 2 * (2.0 / 27 * var.a *
	var.sq_a - 1.0 / 3 * var.a * var.b + var.c);
	var.cb_p = var.p * var.p * var.p;
	var.discriminant = var.q * var.q + var.cb_p;
	solve_cubic_help(&var, 1.0 / 3 * acos(-var.q / sqrt(-var.cb_p)),
	2 * sqrt(-var.p), s);
	var.i = -1;
	while (++var.i < var.num)
		s[var.i] -= 1.0 / 3 * var.a;
	return (var.num);
}

static double			solve_quartic_help(t_quadratic *nw, double coeffs[4],
double roots[4], t_quadratic var)
{
	double		r;

	nw->a = var.d / var.e;
	nw->b = var.c / var.e;
	nw->c = var.b / var.e;
	nw->d = var.a / var.e;
	nw->sq_a = nw->a * nw->a;
	nw->p = -3.0 / 8 * nw->sq_a + nw->b;
	nw->q = 1.0 / 8 * nw->sq_a * nw->a - 1.0 / 2 * nw->a *
	nw->b + nw->c;
	r = -3.0 / 256 * nw->sq_a * nw->sq_a + 1.0 / 16 * nw->sq_a *
	nw->b - 1.0 / 4 * nw->a * nw->c + nw->d;
	coeffs[0] = 1.0 / 2 * r * nw->p - 1.0 / 8 * nw->q * nw->q;
	coeffs[1] = -r;
	coeffs[2] = -1.0 / 2 * nw->p;
	coeffs[3] = 1;
	solve_cubic(coeffs, roots);
	nw->z = roots[0];
	nw->u = nw->z * nw->z - r;
	nw->v = 2 * nw->z - nw->p;
	if (nw->u && nw->v && (nw->u = sqrt(nw->u)))
		nw->v = sqrt(nw->v);
	else
		return (0);
	return (1);
}

double					solve_quartic(t_quadratic var, t_intersection *its)
{
	double		coeffs[4];
	double		roots[4];
	t_quadratic nw;

	if (!solve_quartic_help(&nw, coeffs, roots, var))
		return (0);
	coeffs[0] = nw.z - nw.u;
	coeffs[1] = nw.q < 0 ? -nw.v : nw.v;
	coeffs[2] = 1;
	nw.num = solve_quadratic_two(coeffs, roots);
	coeffs[0] = nw.z + nw.u;
	coeffs[1] = nw.q < 0 ? nw.v : -nw.v;
	coeffs[2] = 1;
	nw.num += solve_quadratic_two(coeffs, roots + nw.num);
	its->t = 1e-6;
	nw.i = -1;
	while (++nw.i < nw.num)
	{
		roots[nw.i] -= 1.0 / 4 * nw.a;
		if (roots[nw.i] > 1e-6 && (its->t == 1e-6 || roots[nw.i] < its->t))
			its->t = roots[nw.i];
	}
	return (its->t > 1e-6);
}
