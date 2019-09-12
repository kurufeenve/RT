/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 11:09:30 by dkliukin          #+#    #+#             */
/*   Updated: 2018/11/17 11:09:30 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/warning.h"

void		set_warning_message(char *param)
{
	char	*tmp;

	if (g_warning.message == NULL)
	{
		g_warning.message = ft_strnew(ft_strlen(param));
		g_warning.message = ft_strcpy(g_warning.message, param);
	}
	else
	{
		tmp = ft_strjoin(g_warning.message, param);
		ft_strdel(&g_warning.message);
		g_warning.message = tmp;
	}
}

void		set_warning_line(int line)
{
	g_warning.line = line;
}

int			get_warning_line(void)
{
	return (g_warning.line);
}

void		no_warning(int warning_code)
{
	if (warning_code == NO_WARNINGS)
		ft_putstr("\n");
}

void		warning(int warning_code)
{
	ft_putstr("\033[;33m ./");
	ft_putstr(get_warning_file());
	if (get_warning_line())
	{
		ft_putstr(" Line: ");
		ft_putnbr(get_warning_line());
		ft_putstr(".");
	}
	ft_putstr(" Warning: \n\t");
	if (g_warning.message)
	{
		ft_putstr(g_warning.message);
		ft_strdel(&g_warning.message);
		ft_putstr("\t");
	}
	no_object_warning(warning_code);
	no_closing_tag_warning(warning_code);
	not_correct_input(warning_code);
	warning_rgb_field_type(warning_code);
	warning_rotation_field_type(warning_code);
	warning_transparency_field_type(warning_code);
	no_warning(warning_code);
	ft_putstr("\033[0m");
}
