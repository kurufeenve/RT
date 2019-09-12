/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:36:12 by akulaiev          #+#    #+#             */
/*   Updated: 2018/11/27 17:36:14 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_position	vector_add(t_position first, t_position second)
{
	t_position	res;

	res.x = first.x + second.x;
	res.y = first.y + second.y;
	res.z = first.z + second.z;
	return (res);
}

t_position	vector_mult(t_position first, double val)
{
	t_position	res;

	res.x = first.x * val;
	res.y = first.y * val;
	res.z = first.z * val;
	return (res);
}

t_position	vector_divide(t_position first, double val)
{
	t_position	res;

	res.x = first.x / val;
	res.y = first.y / val;
	res.z = first.z / val;
	return (res);
}

t_position	vector_subtract(t_position first, t_position second)
{
	t_position	res;

	res.x = first.x - second.x;
	res.y = first.y - second.y;
	res.z = first.z - second.z;
	return (res);
}
