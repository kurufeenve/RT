/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warning_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:12:00 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/02 17:12:01 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/warning.h"

void	set_warning_file(char *file)
{
	if (g_warning.file != NULL)
		ft_strdel(&g_warning.file);
	g_warning.file = ft_strnew(ft_strlen(file));
	g_warning.file = ft_strcpy(g_warning.file, file);
}

char	*get_warning_file(void)
{
	return (g_warning.file);
}

void	delete_warning_file(void)
{
	ft_strdel(&g_warning.file);
}
