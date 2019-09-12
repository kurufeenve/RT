/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 15:38:17 by akulaiev          #+#    #+#             */
/*   Updated: 2018/11/30 15:38:18 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			shading_part_two(t_thread *data, int i,
t_intersection *its, t_shd *s)
{
	t_object		*fig;

	fig = data->scene->figs;
	if (s->i.j == data->scene->num_figs)
	{
		s->half_vect = vector_add(s->light.direction, s->view_vect);
		normalize(&s->half_vect);
		s->n_mult_l = fmax(0, vector_scalar(its->normal, s->light.direction));
		s->h_mult_l = fmax(0,
		pow(vector_scalar(its->normal, s->half_vect), fig[i].shininess));
		s->col.color = add_cols(s->col.color,
		add_cols(mult_cols(fig[i].color.color,
		s->light_intens * s->n_mult_l),
		mult_cols(0x838383, s->light_intens * s->h_mult_l)));
	}
}

static void			shading_part_one(t_thread *data, int i,
t_intersection *its, t_shd *s)
{
	t_object		*fig;
	t_intersection	its1;

	fig = data->scene->figs;
	s->light.direction = vector_subtract(data->scene->lights[s->i.i].coords,
	s->light.origin);
	s->light_intens = data->scene->lights[s->i.i].intensity;
	s->light_len = sqrt(vector_scalar(s->light.direction, s->light.direction));
	s->light.direction = vector_divide(s->light.direction, s->light_len);
	s->i.j = 0;
	while (s->i.j < data->scene->num_figs)
	{
		if (!fig[s->i.j].f(&fig[s->i.j], s->light, &its1) ||
		s->light_len < its1.t
		|| its1.t < 0.00001)
			s->i.j++;
		else
			break ;
	}
	shading_part_two(data, i, its, s);
}

static void			shading_part_zero(t_thread *data,
t_intersection *its, t_shd *s)
{
	t_object		*fig;

	fig = data->scene->figs;
	s->light.origin = its->its_point;
	s->view_vect = vector_subtract(data->scene->camera.origin,
	its->its_point);
	s->i.i = -1;
	normalize(&s->view_vect);
}

t_color				blinn_phong_shading(int rec, t_thread *data, t_ray ray,
t_intersection *its)
{
	t_shd			s;
	int				i;

	s.fig = data->scene->figs;
	s.col.color = 0;
	if (data->scene->sky_check)
		s.col.color = skybox_map(data->sdl_data, ray.direction.x,
		ray.direction.y, ray.direction.z);
	i = -1;
	while (++i < data->scene->num_figs)
	{
		if (s.fig[i].f(&s.fig[i], ray, its) && its->t < its->closest_t)
		{
			its->closest_t = its->t;
			get_its_params(s.fig[i], ray, its);
			shading_part_zero(data, its, &s);
			s.col.color = tex_c(its, *data->scene, &s.fig[i]);
			while (++s.i.i < data->scene->num_lights)
				shading_part_one(data, i, its, &s);
			s.rd = init_refdata(s.fig[i], data, ray, its);
			if (rec < 4 && (s.fig[i].mirror || s.fig[i].refract.ior))
				reflection_refraction(rec, s.rd, &s);
		}
	}
	return (s.col);
}
