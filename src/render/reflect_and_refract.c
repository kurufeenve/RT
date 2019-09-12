/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect_and_refract.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 12:29:51 by akulaiev          #+#    #+#             */
/*   Updated: 2019/03/15 12:29:52 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_refdata		init_refdata(t_object fig, t_thread *data, t_ray ray,
t_intersection *its)
{
	t_refdata		rd;

	rd.fig = fig;
	rd.data = data;
	rd.ray = ray;
	rd.its = its;
	return (rd);
}

static void		fresnel(t_refract *r, t_object fig, t_intersection *its,
t_ray ray)
{
	double	sint;
	double	cost;
	double	rs;
	double	rp;

	r->ior_air = 1;
	r->ior_fig = fig.refract.ior;
	r->cos_ray_norm = vector_scalar(its->normal, ray.direction);
	if (r->cos_ray_norm > 0 && (r->ior_air = r->ior_fig))
		r->ior_fig = 1;
	r->refr_coeff = r->ior_air / r->ior_fig;
	sint = r->refr_coeff * sqrt(fmax(0, 1 - r->cos_ray_norm * r->cos_ray_norm));
	if (sint >= 1)
		r->fresnel = 1;
	else
	{
		cost = sqrt(fmax(0, 1 - sint * sint));
		r->cos_ray_norm = fabs(r->cos_ray_norm);
		rs = ((r->ior_fig * r->cos_ray_norm) - (r->ior_air * cost)) /
		((r->ior_fig * r->cos_ray_norm) + (r->ior_air * cost));
		rp = ((r->ior_air * r->cos_ray_norm) - (r->ior_fig * cost)) /
		((r->ior_air * r->cos_ray_norm) + (r->ior_fig * cost));
		r->fresnel = (rs * rs + rp * rp) / 2;
	}
}

static void		refraction_ray_direction(t_refract *r, t_intersection *its,
t_ray ray)
{
	t_position		n;
	double			cosi;

	n = its->normal;
	r->refr.origin = its->its_point;
	if (vector_scalar(ray.direction, its->normal) < -1)
		cosi = -1;
	else if (vector_scalar(ray.direction, its->normal) > 1)
		cosi = 1;
	else
		cosi = vector_scalar(ray.direction, its->normal);
	if (cosi < 0)
		cosi = -cosi;
	else
		n = vector_mult(its->normal, -1);
	r->cos_refl_ray = 1 - r->refr_coeff * r->refr_coeff * (1 - cosi * cosi);
	if (r->cos_refl_ray >= 0)
	{
		r->refr.direction = vector_add(vector_mult(ray.direction,
		r->refr_coeff),
		vector_mult(n, r->refr_coeff * cosi - sqrtf(r->cos_refl_ray)));
		normalize(&r->refr.direction);
	}
}

void			reflection_refraction(int rec, t_refdata rd, t_shd *s)
{
	t_refract		r;
	t_intersection	its1;

	r.refraction.color = 0;
	r.reflection.color = 0;
	r.refl.origin = rd.its->its_point;
	r.refl.direction = vector_subtract(rd.ray.direction, vector_mult(
	rd.its->normal, 2 * vector_scalar(rd.ray.direction, rd.its->normal)));
	normalize(&r.refl.direction);
	if (rd.fig.mirror && (its1.closest_t = INFINITY))
		s->col.color = add_cols(mult_cols(s->col.color, rd.fig.mirror),
		blinn_phong_shading(++rec, rd.data, r.refl, &its1).color);
	if (rd.fig.refract.ior && (its1.closest_t = INFINITY))
	{
		fresnel(&r, rd.fig, rd.its, rd.ray);
		refraction_ray_direction(&r, rd.its, rd.ray);
		if (r.fresnel < 1 && r.cos_refl_ray >= 0 && (its1.closest_t = INFINITY))
			r.refraction.color = add_cols(mult_cols(r.refraction.color,
			1 - rd.fig.refract.transparency),
			blinn_phong_shading(++rec, rd.data, r.refr, &its1).color);
		r.reflection.color = add_cols(mult_cols(r.reflection.color, 0.1),
		blinn_phong_shading(++rec, rd.data, r.refl, &its1).color);
		s->col.color = add_cols(mult_cols(r.reflection.color, r.fresnel),
		mult_cols(r.refraction.color, 1 - r.fresnel));
	}
}
