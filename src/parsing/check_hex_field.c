/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hex_field.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 20:39:55 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/02 20:51:23 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/warning.h"

static void	wrong_hex_synb_warning(char **trimmed_val)
{
	set_warning_message("Wrong symbol in hexadecimal string '");
	set_warning_message(*trimmed_val);
	set_warning_message("', check your input.");
	warning(NO_WARNINGS);
	ft_strdel(trimmed_val);
}

int			check_hexadecimal_color(char *value)
{
	char	*trimmed_val;
	size_t	i;

	trimmed_val = ft_strtrim(value);
	if (ft_strlen(trimmed_val) > 6 || ft_strlen(trimmed_val) < 1)
	{
		set_warning_message("Unsupported format of hexadecimal value!");
		warning(NO_WARNINGS);
		ft_strdel(&trimmed_val);
		return (FALSE);
	}
	i = 0;
	while (i < ft_strlen(trimmed_val))
	{
		if (!ft_isdigit(trimmed_val[i]) &&
		(trimmed_val[i] < 'A' || trimmed_val[i] > 'F') &&
		(trimmed_val[i] < 'a' || trimmed_val[i] > 'f'))
		{
			wrong_hex_synb_warning(&trimmed_val);
			return (FALSE);
		}
		i++;
	}
	ft_strdel(&trimmed_val);
	return (TRUE);
}
