/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 20:00:08 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/02 20:00:10 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/parsing.h"
#include "./../../include/warning.h"
#include "./../../include/globals.h"

t_obj_wrapper		*create_scene_object(t_tags tag)
{
	if (!ft_strcmp(tag.name, "camera"))
		return (return_camera());
	else if (!ft_strcmp(tag.name, "light"))
		return (return_light());
	else
		return (return_figure(tag));
}

void				scene_setup(t_scene **scene, t_obj_wrapper **wrapper)
{
	if ((*scene)->lst_obj == NULL)
	{
		(*scene)->lst_obj = ft_lstnew((void*)(*wrapper),
		sizeof(t_obj_wrapper));
	}
	else
	{
		ft_lstadd(&(*scene)->lst_obj, ft_lstnew((void*)(*wrapper),
		sizeof(t_obj_wrapper)));
	}
	free(*wrapper);
}

void				scene_object(
	t_tags param_tag,
	t_obj_wrapper *object
)
{
	int				i;

	i = 0;
	while (g_params[i])
	{
		if (!ft_strcmp(param_tag.name, g_params[i]))
		{
			g_set_params[i](param_tag, object);
		}
		i++;
	}
}

void				processing_objects(char *scene_txt, t_scene **scene)
{
	int				i;

	i = 0;
	while (scene_txt[i] != '\0')
	{
		if (scene_txt[i] == '<')
		{
			get_tag_inner_info(scene_txt, scene, &i);
		}
		i++;
	}
}

void				processing_scene(t_scene *scene)
{
	int				scene_fd;
	char			*line;
	char			*scene_txt;

	line = NULL;
	scene_txt = ft_strnew(0);
	scene_fd = open("src/scenes/render.scene.obj", O_RDONLY);
	while (get_next_line(scene_fd, &line) > 0)
	{
		line = ft_strjoin_mod(line, "\n");
		scene_txt = ft_strconcat(scene_txt, line);
	}
	processing_objects(scene_txt, &scene);
	ft_strdel(&line);
	ft_strdel(&scene_txt);
	close(scene_fd);
}
