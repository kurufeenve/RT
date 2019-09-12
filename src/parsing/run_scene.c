/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 14:32:34 by dkliukin          #+#    #+#             */
/*   Updated: 2018/11/17 14:32:35 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static void		close_descr(int com_fd, int fd)
{
	ft_putendl_fd("</scene>", com_fd);
	close(fd);
	close(com_fd);
}

static void		run_scene_cut(char **txt_scene,
char **comp_fn, char **line, int com_fd)
{
	cut_params(*txt_scene, com_fd);
	ft_strdel(txt_scene);
	ft_strdel(comp_fn);
	ft_strdel(line);
}

int				run_scene(char *file)
{
	int			fd;
	char		*line;
	char		*txt_scene;
	int			com_fd;
	char		*comp_fn;

	line = NULL;
	fd = open(file, O_RDWR);
	if (read(fd, NULL, 0) < 0)
	{
		error(NO_FILE);
		return (FALSE);
	}
	comp_fn = ft_strjoin("src/scenes/render.scene", ".obj");
	com_fd = open(comp_fn, O_CREAT | O_RDWR | O_TRUNC, 0755);
	ft_putendl_fd("<scene>", com_fd);
	txt_scene = ft_strnew(0);
	while (get_next_line(fd, &line) > 0)
	{
		line = ft_strjoin_mod(line, "\n");
		txt_scene = ft_strconcat(txt_scene, line);
	}
	run_scene_cut(&txt_scene, &comp_fn, &line, com_fd);
	close_descr(com_fd, fd);
	return (TRUE);
}
