/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_mapping.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:26:17 by akulaiev          #+#    #+#             */
/*   Updated: 2019/03/30 18:26:19 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		tex_c(t_intersection *its, t_scene scene, t_object *fig)
{
	int			i;
	double		intens;
	int			channel_val;
	t_color		ambient;

	i = -1;
	while (++i < scene.num_lights)
	{
		if (scene.lights[i].type == AMBIENT)
			intens = scene.lights[i].intensity;
	}
	channel_val = intens * 255;
	ambient.rgb.r = channel_val;
	ambient.rgb.g = channel_val;
	ambient.rgb.b = channel_val;
	ambient.rgb.a = 0;
	if (!ft_strcmp(fig->object, "sphere") && fig->texture.tex_check)
		return (sphere_mapping(its->its_point, fig));
	return (ambient.color);
}

int		sphere_mapping(t_position point, t_object *fig)
{
	int				i;
	int				x;
	int				y;
	t_position		d;

	d = vector_subtract(point, fig->pos);
	normalize(&d);
	fig->texture.u = 0.5 + (atan2(d.z, d.x) / 2 * M_PI);
	fig->texture.v = 0.5 - asin(d.y) / M_PI;
	x = fig->texture.u * fig->texture.wid;
	y = fig->texture.v * fig->texture.hei;
	i = fmin(fig->texture.wid * fig->texture.hei - 1,
	y * fig->texture.wid + x);
	return (fig->texture.texture[i].color);
}
