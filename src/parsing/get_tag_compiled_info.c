/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tag_compiled_info.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 19:02:45 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/30 19:02:47 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/parsing.h"
#include "./../include/warning.h"

void				set_texture(t_tags param_tag, t_obj_wrapper *object)
{
	if (object->type == FIGURE)
	{
		((t_object*)(object->obj))->texture.filename =
		ft_strdup(param_tag.in_tag);
	}
}

static void			process_tag(t_tags *param_tag, int i, char *object)
{
	param_tag->open = match_tag(object, param_tag->name, i, OPEN_TAG);
	param_tag->close = match_tag(object, param_tag->name,
	param_tag->open, CLOSE_TAG);
	param_tag->in_tag = ft_strsub(object, param_tag->open +
	ft_strlen(param_tag->name) + 2,
	param_tag->close - (param_tag->open +
	ft_strlen(param_tag->name) + 2));
}

void				get_figure_inner_info(
	char *object,
	t_scene **scene,
	t_tags tag
)
{
	int				i;
	t_tags			param_tag;
	t_obj_wrapper	*wrapper;

	i = 0;
	wrapper = (void*)create_scene_object(tag);
	while (object[i] != '\0')
	{
		if (object[i] == '<')
		{
			param_tag.name = ft_strsub(object, i + 1,
			(int)(ft_strstr(&object[i], ">") - (&object[i] + 1)));
			if (!ft_strstr(param_tag.name, "/"))
			{
				process_tag(&param_tag, i, object);
				scene_object(param_tag, wrapper);
				ft_strdel(&param_tag.in_tag);
				i = param_tag.close;
			}
			ft_strdel(&param_tag.name);
		}
		i++;
	}
	scene_setup(scene, &wrapper);
}

static void			open_close_position(t_tags *tag, char *scene_txt, int i)
{
	tag->open = match_tag(scene_txt, tag->name, i, OPEN_TAG);
	tag->close = match_tag(scene_txt, tag->name, tag->open, CLOSE_TAG);
	if (tag->close == -1)
	{
		warning_tag_not_closed(tag->name);
		warning(TAG_NOT_CLOSED);
	}
}

void				get_tag_inner_info(char *scene_txt, t_scene **scene, int *i)
{
	t_tags			tag;

	tag.name = ft_strsub(scene_txt, *i + 1,
			(int)(ft_strstr(&scene_txt[*i], ">") - (&scene_txt[*i] + 1)));
	if (!ft_strstr(tag.name, "/"))
	{
		open_close_position(&tag, scene_txt, *i);
		if (tag.close && ft_strcmp(tag.name, "scene") &&
		ft_strcmp(tag.name, "object"))
			tag.in_tag = ft_strsub(scene_txt, tag.open +
			ft_strlen(tag.name) + 2,
			tag.close - (tag.open + ft_strlen(tag.name) + 2));
		if (tag.close && tag.in_tag && ft_strcmp(tag.name, "scene") &&
		ft_strcmp(tag.name, "object"))
		{
			get_figure_inner_info(tag.in_tag, scene, tag);
			ft_strdel(&tag.in_tag);
			*i = tag.close;
		}
	}
	ft_strdel(&tag.name);
}
