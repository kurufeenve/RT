/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_return.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:42:29 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/30 18:42:31 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/parsing.h"

t_obj_wrapper		*return_camera(void)
{
	t_cam			*cam;
	t_obj_wrapper	*wrapper;

	wrapper = (t_obj_wrapper*)ft_memalloc(sizeof(t_obj_wrapper));
	cam = (t_cam*)ft_memalloc(sizeof(t_cam));
	wrapper->type = CAMERA;
	wrapper->obj = (void*)cam;
	return (wrapper);
}

t_obj_wrapper		*return_light(void)
{
	t_obj_wrapper	*wrapper;
	t_light			*light;

	wrapper = (t_obj_wrapper*)ft_memalloc(sizeof(t_obj_wrapper));
	light = (t_light*)ft_memalloc(sizeof(t_light));
	wrapper->type = LIGHT;
	wrapper->obj = (void*)light;
	return (wrapper);
}

t_obj_wrapper		*return_figure(t_tags tag)
{
	t_object		*object;
	t_obj_wrapper	*wrapper;

	wrapper = (t_obj_wrapper*)ft_memalloc(sizeof(t_obj_wrapper));
	object = (t_object*)ft_memalloc(sizeof(t_object));
	object->object = ft_strdup(tag.name);
	wrapper->type = FIGURE;
	wrapper->obj = (void*)object;
	return (wrapper);
}
