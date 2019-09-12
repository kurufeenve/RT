/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:13:50 by vordynsk          #+#    #+#             */
/*   Updated: 2019/03/31 16:13:52 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cam_exist(t_cam *cam)
{
	if (!cam->exist)
	{
		set_warning_message("Object <camera> don't exits. Default settings of \
camera will be applied.\n");
		warning(CAMERA_DO_NOT_EXIST);
		cam->exist = 1;
		cam->basis.direction_vect.x = 0;
		cam->basis.direction_vect.y = 0;
		cam->basis.direction_vect.z = 1;
		cam->origin.x = 0;
		cam->origin.z = 0;
		cam->origin.y = 0;
		cam->basis = get_basis(cam->basis.direction_vect);
	}
}

void		obj_count(t_scene *sc)
{
	t_list	*lst;

	lst = sc->lst_obj;
	while (1)
	{
		if (((t_obj_wrapper*)(lst->content))->type == CAMERA)
			read_cam(sc,
			((t_cam*)((t_obj_wrapper*)(lst->content))->obj));
		if (((t_obj_wrapper*)(lst->content))->type == LIGHT)
			sc->num_lights++;
		if (((t_obj_wrapper*)(lst->content))->type == FIGURE)
		{
			if (fig_check(lst) == CUT_CONE)
				sc->num_figs++;
			if (fig_check(lst) == CUT_CYLINDER)
				sc->num_figs = sc->num_figs + 2;
			sc->num_figs++;
		}
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	cam_exist(&sc->camera);
	sc->lights = (t_light*)malloc(sizeof(t_light) * sc->num_lights);
	sc->figs = (t_object*)malloc(sizeof(t_object) * sc->num_figs);
}

int			write_params4(t_scene *sc, t_list *lst, int i)
{
	if (fig_check2(lst) == CUBE)
	{
		sc->figs[i] = *((t_object*)(((t_obj_wrapper*)(lst->content))->obj));
		sc->figs[i].f = &box_intersection;
	}
	else
		return (0);
	return (1);
}
