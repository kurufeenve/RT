/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 20:56:18 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/02 20:56:20 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/warning.h"
#include "../../include/parsing.h"

int			warning_handler_rgb(char *color, int color_num)
{
	int		temp_color;

	temp_color = ft_atoi(color);
	if (temp_color < 0 || temp_color > 255 || !is_numeric(color))
	{
		set_warning_message("Value for ");
		if (color_num == 0)
			set_warning_message("'Red'");
		if (color_num == 1)
			set_warning_message("'Green'");
		if (color_num == 2)
			set_warning_message("'Blue'");
		set_warning_message(" color is not numerical or value out of range.\n\
	Value: '");
		set_warning_message(color);
		set_warning_message("'.\n");
		warning(WARNING_RGB_VALUE);
		return (FALSE);
	}
	return (TRUE);
}

static void	rgb_value_warning(char *value, char *param_name)
{
	set_warning_message("One or more values were missing for '");
	set_warning_message(param_name);
	set_warning_message("'\n\tValues: ");
	set_warning_message(value);
	set_warning_message(".\n");
	warning(WARNING_RGB_TYPE_UNSUPPORTED);
}

int			check_rgb_color(char *value, char *param_name)
{
	char	**rgb_color;
	int		is_rgb_rdy;
	int		i;
	int		rgb_len;

	i = 0;
	rgb_len = 0;
	is_rgb_rdy = TRUE;
	rgb_color = ft_strsplit(value, ',');
	rgb_len = array_length(rgb_color);
	if (rgb_len != 3)
	{
		rgb_value_warning(value, param_name);
		is_rgb_rdy = FALSE;
	}
	while (i < rgb_len)
	{
		if (warning_handler_rgb(rgb_color[i], i) == FALSE)
			is_rgb_rdy = FALSE;
		ft_strdel(&rgb_color[i]);
		i++;
	}
	free(rgb_color);
	return (is_rgb_rdy);
}
