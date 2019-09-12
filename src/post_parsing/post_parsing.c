/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:26:10 by vordynsk          #+#    #+#             */
/*   Updated: 2019/03/30 15:26:14 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "warning.h"

void		read_cam(t_scene *sc, t_cam *cam)
{
	sc->camera.exist = 1;
	sc->camera.basis = cam->basis;
	sc->camera.origin = cam->origin;
	sc->camera.basis = get_basis(sc->camera.basis.direction_vect);
}

int			fig_check(t_list *lst)
{
	if (ft_strcmp(((t_object*)(((t_obj_wrapper*)(lst->content))->obj))\
->object, "cylinder") == 0 && ((t_object*)((t_obj_wrapper*)(lst->content))\
->obj)->height > 0.00001)
		return (CUT_CYLINDER);
	else if (ft_strcmp(((t_object*)(((t_obj_wrapper*)(lst->content))->obj))\
->object, "cone") == 0 && ((t_object*)((t_obj_wrapper*)(lst->content))->obj)\
->height > 0.00001)
		return (CUT_CONE);
	else if (ft_strcmp(((t_object*)(((t_obj_wrapper*)(lst->content))->obj))\
->object, "sphere") == 0)
		return (SPHERE);
	else if (ft_strcmp(((t_object*)(((t_obj_wrapper*)(lst->content))->obj))\
->object, "cone") == 0 && ((t_object*)((t_obj_wrapper*)(lst->content))\
->obj)->height < 0.00001)
		return (CONE);
	else if (ft_strcmp(((t_object*)(((t_obj_wrapper*)(lst->content))->obj))\
->object, "cylinder") == 0 && ((t_object*)((t_obj_wrapper*)(lst->content))\
->obj)->height < 0.00001)
		return (CYLINDER);
	else
		return (-1);
}

int			fig_check2(t_list *lst)
{
	if (ft_strcmp(((t_object*)(((t_obj_wrapper*)(lst->content))->obj))\
->object, "ellipsoid") == 0)
		return (ELLIPSOID);
	else if (ft_strcmp(((t_object*)(((t_obj_wrapper*)(lst->content))->obj))\
->object, "elliptic_paraboloid") == 0)
		return (ELLIPTIC_PARABOLOID);
	else if (ft_strcmp(((t_object*)(((t_obj_wrapper*)(lst->content))->obj))\
->object, "hyperbolic_paraboloid") == 0)
		return (HYPERBOLIC_PARABOLOID);
	else if (ft_strcmp(((t_object*)(((t_obj_wrapper*)(lst->content))->obj))\
->object, "plane") == 0)
		return (PLANE);
	else if (ft_strcmp(((t_object*)(((t_obj_wrapper*)(lst->content))->obj))\
->object, "torus") == 0)
		return (TORUS);
	else if (ft_strcmp(((t_object*)(((t_obj_wrapper*)(lst->content))->obj))\
->object, "cube") == 0)
		return (CUBE);
	else
		return (-1);
}

void		light_write(t_scene *sc)
{
	t_list	*lst;
	int		i;

	i = 0;
	lst = sc->lst_obj;
	while (1)
	{
		if (((t_obj_wrapper*)(lst->content))->type == LIGHT &&
		i < sc->num_lights)
		{
			sc->lights[i] = *((t_light*)((t_obj_wrapper*)(lst->content))->obj);
			i++;
		}
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
}

void		fig_write(t_scene *sc)
{
	t_list	*lst;
	int		i;

	i = 0;
	lst = sc->lst_obj;
	while (1)
	{
		if (((t_obj_wrapper*)(lst->content))->type == FIGURE &&
		i < sc->num_figs)
		{
			i += write_params(sc, lst, i);
			i += write_params2(sc, lst, i);
			i += write_params3(sc, lst, i);
			i += write_params4(sc, lst, i);
		}
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
}
