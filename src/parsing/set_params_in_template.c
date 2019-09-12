/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_params_in_template.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 13:45:27 by dkliukin          #+#    #+#             */
/*   Updated: 2018/12/22 13:45:29 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void		validate_coord(char *inp_val,
char **value_rel_param, char *coord, int n)
{
	char	*tmp;

	tmp = NULL;
	if (is_numeric(inp_val))
	{
		tmp = value_rel_param[n];
		value_rel_param[n] = ft_strdup(inp_val);
	}
	else
		not_numeric_warning(inp_val, coord);
	if (tmp)
		ft_strdel(&tmp);
}

int			compile_related_cord(char *inp_val,
char **value_rel_param, char *coord)
{
	int		i;

	i = 0;
	if (!ft_strcmp(coord, "x"))
		validate_coord(inp_val, value_rel_param, coord, 0);
	else if (!ft_strcmp(coord, "y"))
		validate_coord(inp_val, value_rel_param, coord, 1);
	else if (!ft_strcmp(coord, "z"))
		validate_coord(inp_val, value_rel_param, coord, 2);
	else
	{
		set_warning_message("Unrecognized coordinate '");
		set_warning_message(coord);
		set_warning_message("' please check your input");
		warning(NO_WARNINGS);
		while (i < 3)
			ft_strdel(&value_rel_param[i++]);
		free(value_rel_param);
		return (FALSE);
	}
	return (TRUE);
}

void		coord_related_build(char **values, char *inp_val, char *coord)
{
	char	**value_rel_param;
	char	*tmp;
	int		i;

	i = 0;
	value_rel_param = ft_strsplit(*values, ',');
	if (!compile_related_cord(inp_val, value_rel_param, coord))
		return ;
	ft_strdel(values);
	i = 0;
	*values = ft_strdup("");
	while (i < 3)
	{
		if (i < 2)
			tmp = ft_strjoin(value_rel_param[i], ",");
		else
		{
			tmp = ft_strjoin(value_rel_param[i], "");
		}
		*values = ft_strjoin_mod(*values, tmp);
		ft_strdel(&tmp);
		ft_strdel(&value_rel_param[i]);
		i++;
	}
	free(value_rel_param);
}

void		rebuild_object(char **obj, t_tags position,
t_param_val param, char *coord)
{
	char	*obj_1;
	char	*obj_2;
	char	*values;

	obj_1 = ft_strsub(*obj, 0, position.open + ft_strlen(param.name) + 2);
	obj_2 = ft_strsub(*obj, position.close, ft_strlen(*obj) - position.close);
	values = ft_strsub(*obj, position.open + ft_strlen(param.name) + 2,
	position.close - (position.open + ft_strlen(param.name) + 2));
	if (coord)
	{
		coord_related_build(&values, param.val, coord);
		obj_1 = ft_strjoin_mod(obj_1, values);
	}
	else
	{
		if (check_value(param.val, param.name) && check_coord_rel(param.name))
			obj_1 = ft_strjoin_mod(obj_1, param.val);
		else
			obj_1 = ft_strjoin_mod(obj_1, values);
	}
	ft_strdel(obj);
	ft_strdel(&values);
	*obj = ft_strconcat(obj_1, obj_2);
}

void		set_param_in_tpl(t_param_val param, char **obj)
{
	t_tags	param_tag;
	char	*name;
	char	**tmp;
	char	*coord;

	name = ft_strtrim(param.name);
	ft_strdel(&param.name);
	tmp = ft_strsplit(name, '-');
	coord = (array_length(tmp) == 2) ? tmp[1] : NULL;
	ft_strdel(&name);
	param.name = tmp[0];
	param_tag.open = match_tag(*obj, param.name, 0, OPEN_TAG);
	if (param_tag.open == -1)
		parametr_not_found_warning(param.name);
	else
	{
		param_tag.close = match_tag(*obj, param.name,
		param_tag.open, CLOSE_TAG);
		rebuild_object(obj, param_tag, param, coord);
	}
	if (coord)
		ft_strdel(&coord);
	free(tmp);
	ft_strdel(&param.name);
	ft_strdel(&param.val);
}
