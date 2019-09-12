/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_template_object.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:17:30 by dkliukin          #+#    #+#             */
/*   Updated: 2018/12/05 17:17:32 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	object_exists(char *obj, int fd)
{
	if (!ft_strcmp(obj, "scene"))
		return (1);
	if (fd <= 0)
	{
		set_warning_message("Object <");
		set_warning_message(obj);
		set_warning_message(">");
		set_warning_message(" undefined\n");
		return (0);
	}
	return (1);
}

char		*get_tpl_obj(char *obj)
{
	int		fig_obj_fd;
	char	*obj_tpl;
	char	*line;
	char	*path;

	obj_tpl = ft_strnew(0);
	path = ft_strjoin(obj, OBJ_TPL_EXTENTION);
	path = ft_strjoin_mod_rew(OBJ_TPL_PATH, path);
	fig_obj_fd = open(path, O_RDONLY);
	if (!object_exists(obj, fig_obj_fd))
		warning(NO_TPL_OBJECT);
	if (fig_obj_fd > 0)
	{
		while (get_next_line(fig_obj_fd, &line) > 0)
		{
			line = ft_strjoin_mod(line, "\n");
			obj_tpl = ft_strconcat(obj_tpl, line);
		}
		close(fig_obj_fd);
		ft_strdel(&line);
	}
	ft_strdel(&path);
	return (obj_tpl);
}
