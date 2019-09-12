/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_obj_params_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:20:46 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/30 18:20:47 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/parsing.h"
#include "./../include/warning.h"

void		set_radius(t_tags param_tag, t_obj_wrapper *object)
{
	double	radius;

	radius = ft_atod(param_tag.in_tag);
	radius = radius < 0 ? 0 : radius;
	if (object->type == FIGURE)
	{
		((t_object*)(object->obj))->radius = radius;
	}
}

void		set_transparency(t_tags param_tag, t_obj_wrapper *object)
{
	double	transparency;

	transparency = ft_atod(param_tag.in_tag) / 100.0;
	transparency = transparency > 1.0 ? 1.0 : transparency;
	transparency = transparency < 0 ? 0 : transparency;
	if (object->type == FIGURE)
	{
		((t_object*)(object->obj))->refract.transparency =
		transparency;
	}
}

void		set_height(t_tags param_tag, t_obj_wrapper *object)
{
	double	heigth;

	heigth = ft_atod(param_tag.in_tag);
	heigth = heigth < 0 ? 0 : heigth;
	if (object->type == FIGURE)
	{
		((t_object*)(object->obj))->height = heigth;
	}
}

void		set_rotation(t_tags param_tag, t_obj_wrapper *object)
{
	char	**params;

	params = ft_strsplit(param_tag.in_tag, ',');
	if (object->type == FIGURE)
	{
		((t_object*)(object->obj))->angle.rot_x = ft_atoi(params[0]);
		((t_object*)(object->obj))->angle.rot_y = ft_atoi(params[1]);
		((t_object*)(object->obj))->angle.rot_z = ft_atoi(params[2]);
	}
	del_double_arr(&params);
}

void		set_shininess(t_tags param_tag, t_obj_wrapper *object)
{
	int		shininess;

	shininess = ft_atoi(param_tag.in_tag);
	shininess = shininess > 1000 ? 1000 : shininess;
	shininess = shininess < 0 ? 0 : shininess;
	if (object->type == FIGURE)
	{
		((t_object*)(object->obj))->shininess = shininess;
	}
}
