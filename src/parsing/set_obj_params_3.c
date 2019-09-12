/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_obj_params_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:19:41 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/30 18:19:42 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/parsing.h"
#include "./../include/warning.h"

void		set_mirror(t_tags param_tag, t_obj_wrapper *object)
{
	double	mirror;

	mirror = ft_atod(param_tag.in_tag) / 100.0;
	mirror = mirror > 1 ? 1 : mirror;
	mirror = mirror < 0 ? 0 : mirror;
	if (object->type == FIGURE)
	{
		((t_object*)(object->obj))->mirror = mirror;
	}
}

void		set_refraction(t_tags param_tag, t_obj_wrapper *object)
{
	double	refraction;

	refraction = ft_atod(param_tag.in_tag) / 100.0;
	refraction = refraction > 2.0 ? 2.0 : refraction;
	refraction = refraction < 1.0 && refraction != 0 ? 1.0 : refraction;
	refraction = refraction == 0 ? 0 : refraction;
	if (object->type == FIGURE)
	{
		((t_object*)(object->obj))->refract.ior = refraction;
	}
}

void		set_cone_angle(t_tags param_tag, t_obj_wrapper *object)
{
	double	ang;

	ang = ft_atod(param_tag.in_tag);
	ang = ang <= 0 || ang >= 180 ? 30 : ang;
	if (object->type == FIGURE)
	{
		((t_object*)(object->obj))->cone_angle =
		(ft_atod(param_tag.in_tag) * M_PI) / 180.0;
	}
}

void		set_position2(t_tags param_tag, t_obj_wrapper *object)
{
	char **params;

	params = ft_strsplit(param_tag.in_tag, ',');
	if (object->type == FIGURE)
	{
		((t_object*)(object->obj))->pos2.x = ft_atod(params[0]);
		((t_object*)(object->obj))->pos2.y = ft_atod(params[1]);
		((t_object*)(object->obj))->pos2.z = ft_atod(params[2]);
	}
	del_double_arr(&params);
}

void		set_ligth_type(t_tags param_tag, t_obj_wrapper *object)
{
	if (object->type == LIGHT)
	{
		if (!ft_strcmp(param_tag.in_tag, "point"))
			((t_light*)(object->obj))->type = POINT;
		if (!ft_strcmp(param_tag.in_tag, "ambient"))
			((t_light*)(object->obj))->type = AMBIENT;
	}
}
