/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 17:36:15 by akulaiev          #+#    #+#             */
/*   Updated: 2018/11/28 17:36:16 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	calculate_ray(t_iterators iter, t_ray *ray, t_thread *data)
{
	iter.x_screen = (((iter.x + 0.5) / data->scene->window_width) * 2 - 1)
	* data->scene->window_width / data->scene->window_height;
	iter.y_screen = ((iter.y + 0.5) / data->scene->window_height) * 2 - 1;
	ray->direction = vector_add(data->scene->camera.basis.direction_vect,
	vector_add(vector_mult(data->scene->camera.basis.up_vect, iter.y_screen),
	vector_mult(data->scene->camera.basis.right_vect, iter.x_screen)));
	normalize(&ray->direction);
	ray->origin = data->scene->camera.origin;
}

void		*create_ray(void *data)
{
	t_iterators		iter;
	t_ray			ray;
	t_intersection	its;
	t_thread		*t_data;

	t_data = (t_thread*)data;
	iter.y = t_data->current_y;
	while (++iter.y < t_data->scene->window_height)
	{
		iter.x = -1;
		while (++iter.x < t_data->scene->window_width)
		{
			its.x = iter.x;
			its.y = iter.y;
			calculate_ray(iter, &ray, t_data);
			t_data->sdl_data->img_ptr[t_data->scene->window_width
			* iter.y + iter.x] =
			get_closest_shape(t_data, ray, &its);
		}
	}
	pthread_exit(NULL);
}
