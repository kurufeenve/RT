/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_cols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 18:10:57 by akulaiev          #+#    #+#             */
/*   Updated: 2019/03/29 18:10:58 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				add_cols(int first, int second)
{
	t_color		new_col;
	t_color		first_col;
	t_color		second_col;

	first_col.color = first;
	second_col.color = second;
	new_col.rgb.r = fmin(first_col.rgb.r + second_col.rgb.r, 0xFF);
	new_col.rgb.g = fmin(first_col.rgb.g + second_col.rgb.g, 0xFF);
	new_col.rgb.b = fmin(first_col.rgb.b + second_col.rgb.b, 0xFF);
	return (new_col.color);
}

int				mult_cols(int col, double mult)
{
	t_color		new_col;
	t_color		first_col;

	first_col.color = col;
	new_col.rgb.r = fmin(first_col.rgb.r * mult, 0xFF);
	new_col.rgb.g = fmin(first_col.rgb.g * mult, 0xFF);
	new_col.rgb.b = fmin(first_col.rgb.b * mult, 0xFF);
	return (new_col.color);
}
