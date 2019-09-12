/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 23:10:20 by vordynsk          #+#    #+#             */
/*   Updated: 2019/03/30 23:10:22 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object	add_cone_cap(t_object fig)
{
	t_object	cap;

	cap = fig;
	cap.object = ft_strdup("plane");
	cap.radius = tan(fig.cone_angle) * fig.height;
	cap.direction = rotate_figure(fig);
	cap.height = 0;
	cap.pos = vector_add(fig.pos, vector_mult(cap.direction, fig.height));
	cap.angle.rot_x = 0;
	cap.angle.rot_y = 0;
	cap.angle.rot_z = 0;
	cap.f = &plane_intersection;
	return (cap);
}

t_object	add_cylinder_cap(t_object fig, int cap_num)
{
	t_object	cap;

	cap = fig;
	cap.object = ft_strdup("plane");
	cap.height = 0;
	cap.f = &plane_intersection;
	if (cap_num == 0)
	{
		cap.direction = rotate_figure(fig);
		cap.pos = vector_add(fig.pos, vector_mult(cap.direction, fig.height));
		cap.angle.rot_x = 0;
		cap.angle.rot_y = 0;
		cap.angle.rot_z = 0;
	}
	if (cap_num == 1)
		cap.direction = vector_mult(fig.direction, -1);
	return (cap);
}

int			write_params(t_scene *sc, t_list *lst, int i)
{
	if (fig_check(lst) == CUT_CONE)
	{
		sc->figs[i] = *((t_object*)(((t_obj_wrapper*)(lst->content))->obj));
		sc->figs[i].f = &cone_intersection;
		sc->figs[i + 1] = add_cone_cap(sc->figs[i]);
		return (2);
	}
	if (fig_check(lst) == CUT_CYLINDER)
	{
		sc->figs[i] = *((t_object*)(((t_obj_wrapper*)(lst->content))->obj));
		sc->figs[i].f = &cylinder_intersection;
		sc->figs[i + 1] = add_cylinder_cap(sc->figs[i], 0);
		sc->figs[i + 2] = add_cylinder_cap(sc->figs[i], 1);
		return (3);
	}
	else
		return (0);
}

int			write_params2(t_scene *sc, t_list *lst, int i)
{
	if (fig_check(lst) == SPHERE)
	{
		sc->figs[i] = *((t_object*)(((t_obj_wrapper*)(lst->content))->obj));
		sc->figs[i].f = &sphere_intersection;
	}
	else if (fig_check(lst) == CONE)
	{
		sc->figs[i] = *((t_object*)(((t_obj_wrapper*)(lst->content))->obj));
		sc->figs[i].f = &cone_intersection;
	}
	else if (fig_check(lst) == CYLINDER)
	{
		sc->figs[i] = *((t_object*)(((t_obj_wrapper*)(lst->content))->obj));
		sc->figs[i].f = &cylinder_intersection;
	}
	else if (fig_check2(lst) == ELLIPSOID)
	{
		sc->figs[i] = *((t_object*)(((t_obj_wrapper*)(lst->content))->obj));
		sc->figs[i].f = &ellipsoid_intersection;
	}
	else
		return (0);
	return (1);
}

int			write_params3(t_scene *sc, t_list *lst, int i)
{
	if (fig_check2(lst) == ELLIPTIC_PARABOLOID)
	{
		sc->figs[i] = *((t_object*)(((t_obj_wrapper*)(lst->content))->obj));
		sc->figs[i].f = &elliptic_paraboloid_intersection;
	}
	else if (fig_check2(lst) == HYPERBOLIC_PARABOLOID)
	{
		sc->figs[i] = *((t_object*)(((t_obj_wrapper*)(lst->content))->obj));
		sc->figs[i].f = &hyperbolic_paraboloid_intersection;
	}
	else if (fig_check2(lst) == PLANE)
	{
		sc->figs[i] = *((t_object*)(((t_obj_wrapper*)(lst->content))->obj));
		sc->figs[i].f = &plane_intersection;
	}
	else if (fig_check2(lst) == TORUS)
	{
		sc->figs[i] = *((t_object*)(((t_obj_wrapper*)(lst->content))->obj));
		sc->figs[i].f = &torus_intersection;
	}
	else
		return (0);
	return (1);
}
