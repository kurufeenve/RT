/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_obj_params_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:20:51 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/30 18:20:52 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/parsing.h"
#include "./../include/warning.h"
#include "./../include/rt.h"

void		set_position(t_tags param_tag, t_obj_wrapper *object)
{
	char	**params;

	params = ft_strsplit(param_tag.in_tag, ',');
	if (object->type == CAMERA)
	{
		((t_cam*)(object->obj))->origin.x = ft_atod(params[0]);
		((t_cam*)(object->obj))->origin.y = ft_atod(params[1]);
		((t_cam*)(object->obj))->origin.z = ft_atod(params[2]);
	}
	if (object->type == LIGHT)
	{
		((t_light*)(object->obj))->coords.x = ft_atod(params[0]);
		((t_light*)(object->obj))->coords.y = ft_atod(params[1]);
		((t_light*)(object->obj))->coords.z = ft_atod(params[2]);
	}
	if (object->type == FIGURE)
	{
		((t_object*)(object->obj))->pos.x = ft_atod(params[0]);
		((t_object*)(object->obj))->pos.y = ft_atod(params[1]);
		((t_object*)(object->obj))->pos.z = ft_atod(params[2]);
	}
	del_double_arr(&params);
}

void		set_normale(t_tags param_tag, t_obj_wrapper *object)
{
	char	**params;
	double	x;
	double	y;
	double	z;

	params = ft_strsplit(param_tag.in_tag, ',');
	x = ft_atod(params[0]);
	y = ft_atod(params[1]);
	z = ft_atod(params[2]);
	manage_normales(&x, &y, &z);
	if (object->type == CAMERA)
	{
		((t_cam*)(object->obj))->basis.direction_vect.x = x;
		((t_cam*)(object->obj))->basis.direction_vect.y = y;
		((t_cam*)(object->obj))->basis.direction_vect.z = z;
	}
	if (object->type == FIGURE)
	{
		((t_object*)(object->obj))->direction.x = x;
		((t_object*)(object->obj))->direction.y = y;
		((t_object*)(object->obj))->direction.z = z;
	}
	del_double_arr(&params);
}

void		set_color_rgb(t_tags param_tag, t_obj_wrapper *object)
{
	char	**params;

	params = ft_strsplit(param_tag.in_tag, ',');
	if (object->type == FIGURE)
	{
		((t_object*)(object->obj))->color.rgb.r =
		(unsigned char)ft_atoi(params[0]);
		((t_object*)(object->obj))->color.rgb.g =
		(unsigned char)ft_atoi(params[1]);
		((t_object*)(object->obj))->color.rgb.b =
		(unsigned char)ft_atoi(params[2]);
	}
	del_double_arr(&params);
}

void		set_color_hex(t_tags param_tag, t_obj_wrapper *object)
{
	if (object->type == FIGURE)
	{
		((t_object*)(object->obj))->color.color =
		ft_atoi_base(param_tag.in_tag, 16);
	}
}

void		set_intensity(t_tags param_tag, t_obj_wrapper *object)
{
	double	intensity;

	intensity = ft_atod(param_tag.in_tag) / 100.0;
	intensity = intensity > 1 ? 1 : intensity;
	intensity = intensity < 0 ? 0 : intensity;
	if (object->type == LIGHT)
	{
		((t_light*)(object->obj))->intensity = intensity;
	}
}
