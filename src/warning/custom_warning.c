/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_warning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 18:38:49 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/02 18:38:51 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/warning.h"

void		compile_params_warning(char *param)
{
	char		*warning_param;

	warning_param = ft_strtrim(param);
	set_warning_message("Check your parameter \"");
	set_warning_message(warning_param);
	set_warning_message("...\" for correct input\n");
	warning(INPUT_NOT_CORRECT);
	ft_strdel(&warning_param);
}

void		parametr_not_found_warning(char *name)
{
	set_warning_message("This parameter \"");
	set_warning_message(name);
	set_warning_message("\" can't be found\n");
	warning(NO_WARNINGS);
}
