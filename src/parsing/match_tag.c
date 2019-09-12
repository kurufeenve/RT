/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_tag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:10:05 by dkliukin          #+#    #+#             */
/*   Updated: 2018/12/05 17:10:08 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int			match_tag(char *scene, char *tag, int start_from, int mod)
{
	char	*to_find;
	int		position;

	if (mod == CLOSE_TAG)
	{
		to_find = ft_strjoin_mod_rew("</", ft_strjoin(tag, ">"));
	}
	if (mod == OPEN_TAG)
	{
		to_find = ft_strjoin_mod_rew("<", ft_strjoin(tag, ">"));
	}
	position = find_tag_position(scene, &to_find, start_from);
	ft_strdel(&to_find);
	return (position);
}
