/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_warning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 11:05:48 by dkliukin          #+#    #+#             */
/*   Updated: 2018/11/17 11:05:49 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/warning.h"

void		no_object_warning(int warning_code)
{
	if (warning_code == NO_TPL_OBJECT)
	{
		ft_putstr("There is no template objects with such tag.\n");
	}
}

void		not_numeric_warning(char *str, char *coord)
{
	set_warning_message("Not numeric value '");
	set_warning_message(str);
	set_warning_message("' please check your input.\n");
	set_warning_message("\tDefault value will be used for '");
	set_warning_message(coord);
	set_warning_message("'");
	if (!ft_strcmp(coord, "x") || !ft_strcmp(coord, "y") ||
	!ft_strcmp(coord, "z"))
		set_warning_message(" coordinate.");
	warning(NO_WARNINGS);
}

void		no_closing_tag_warning(int warning_code)
{
	if (warning_code == TAG_NOT_CLOSED)
	{
		ft_putstr("No closing tag has occurred.\n");
	}
}

void		not_correct_input(int warning_code)
{
	if (warning_code == INPUT_NOT_CORRECT)
	{
		ft_putstr("Input validation issues. Check your input.\n");
	}
}

void		warning_tag_not_closed(char *tag)
{
	set_warning_message("Tag </");
	set_warning_message(tag);
	set_warning_message("> do not exist.\n");
}
