/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_information_parsing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:38:22 by dkliukin          #+#    #+#             */
/*   Updated: 2018/12/05 17:38:23 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static void		compile_params(char *to_split_param, char **obj, int nl)
{
	char		**tmp;
	t_param_val	param;
	int			i;

	set_warning_line(get_warning_line() + nl);
	tmp = ft_strsplit(to_split_param, ':');
	if (array_length(tmp) != 2)
	{
		compile_params_warning(tmp[0]);
	}
	else
	{
		param.name = ft_strjoin(tmp[0], "");
		param.val = ft_strjoin(tmp[1], "");
		set_param_in_tpl(param, obj);
	}
	i = 0;
	while (tmp[i] != NULL)
	{
		ft_strdel(&tmp[i]);
		i++;
	}
	free(tmp);
	set_warning_line(get_warning_line() - nl);
}

static void		parse_object_param(char **params, int i, int nl, char **obj)
{
	int			j;
	int			tmp_nl;

	j = 0;
	tmp_nl = 0;
	while (params[i][j] != '\0')
	{
		if (ft_isalnum(params[i][j]))
			break ;
		if (params[i][j] == '\n')
			tmp_nl++;
		j++;
	}
	compile_params(params[i], obj, nl + tmp_nl);
	j = -1;
	while (params[i][++j] != '\0')
		if (params[i][j] == '\n')
			nl++;
	ft_strdel(&(params[i]));
}

static void		parse_object(char **src, char *objname, char **obj, int com_fd)
{
	int			i;
	char		**params;
	int			nl;
	char		*last;

	nl = 0;
	if (!((int)(last = NULL)) && !ft_strcmp(objname, "scene"))
		return ;
	params = ft_strsplit(*src, ';');
	if (empty(*src))
		ft_strdel(&(params[0]));
	if (array_length(params) > 0)
		last = ft_strtrim(params[array_length(params) - 1]);
	if ((last == NULL || ft_strlen(last) == 0) && array_length(params) > 0)
		ft_strdel(&params[array_length(params) - 1]);
	array_length(params) > 0 ? ft_strdel(&last) : NULL;
	i = 0;
	while (params[i])
	{
		parse_object_param(params, i, nl, obj);
		nl++;
		i++;
	}
	ft_putendl_fd(*obj, com_fd);
	free(params);
}

static void		tag_info_parse(char *scene, t_tags *tag, int i, int com_fd)
{
	tag->name = ft_strsub(scene, i + 1, (ft_strstr(&scene[i], ">") - (&scene[i]
	+ 1)) > 0 ? (ft_strstr(&scene[i], ">") -
	(&scene[i] + 1)) : ft_strlen(scene));
	if (!ft_strstr(tag->name, "/"))
	{
		tag->open = match_tag(scene, tag->name, i, OPEN_TAG);
		tag->close = match_tag(scene, tag->name, tag->open, CLOSE_TAG);
		if (tag->close == -1)
			close_warning(tag->name);
		if (tag->close && ft_strcmp(tag->name, "scene"))
			tag->in_tag = ft_strsub(scene, tag->open + ft_strlen(tag->name) + 2,
			tag->close - (tag->open + ft_strlen(tag->name) + 2));
		if (ft_strcmp(tag->name, "scene"))
			tag->obj_tpl = get_tpl_obj(tag->name);
		if (tag->close && tag->in_tag && ft_strcmp(tag->name, "scene"))
		{
			parse_object(&tag->in_tag, tag->name, &tag->obj_tpl, com_fd);
			ft_strdel(&tag->in_tag);
		}
		if (ft_strcmp(tag->name, "scene") && tag->obj_tpl != NULL)
			ft_strdel(&tag->obj_tpl);
	}
	ft_strdel(&tag->name);
}

void			cut_params(char *scene, int com_fd)
{
	int			i;
	t_tags		tag;

	i = 0;
	set_warning_line(1);
	while (scene[i] != '\0')
	{
		if (scene[i] == '\n')
			set_warning_line(get_warning_line() + 1);
		if (scene[i] == '<')
		{
			tag_info_parse(scene, &tag, i, com_fd);
		}
		i++;
	}
	set_warning_line(0);
}
