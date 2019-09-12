/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_warning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 11:05:40 by dkliukin          #+#    #+#             */
/*   Updated: 2018/11/17 11:05:42 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/warning.h"

void		light_tag_warning(int warning_code)
{
	if (warning_code == LIGHT_DO_NOT_EXIST)
		ft_putstr("Light open tag <light> and close tag \
</light> do not exist.\n");
}
