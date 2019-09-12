/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:36:44 by akulaiev          #+#    #+#             */
/*   Updated: 2018/11/27 17:36:46 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/rt.h"

double		vector_scalar(t_position first, t_position second)
{
	double	res;

	res = first.x * second.x + first.y * second.y + first.z * second.z;
	return (res);
}

t_position	vector_cross(t_position first, t_position second)
{
	t_position	res;

	res.x = first.y * second.z - first.z * second.y;
	res.y = first.z * second.x - first.x * second.z;
	res.z = first.x * second.y - first.y * second.x;
	return (res);
}

void		normalize(t_position *ray)
{
	double	ray_len;

	ray_len = sqrt(ray->x * ray->x + ray->y * ray->y + ray->z * ray->z);
	ray->x /= ray_len;
	ray->y /= ray_len;
	ray->z /= ray_len;
}

t_base		get_basis(t_position vect)
{
	t_position	tmp;
	t_base		res;

	tmp.x = vect.x;
	tmp.y = vect.y + 0.0001;
	tmp.z = vect.z + 0.0002;
	res.right_vect = vector_cross(vect, tmp);
	normalize(&res.right_vect);
	res.up_vect = vector_cross(vect, res.right_vect);
	normalize(&res.up_vect);
	res.right_vect = vector_cross(vect, res.up_vect);
	normalize(&res.right_vect);
	res.direction_vect = vect;
	return (res);
}

double		vector_len(t_position vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}
