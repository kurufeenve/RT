/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:54:28 by dkliukin          #+#    #+#             */
/*   Updated: 2018/12/05 16:54:29 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void		del_double_arr(char ***str)
{
	int		i;

	i = 0;
	if (str && *str && **str)
	{
		while ((*str)[i])
		{
			ft_strdel(&(*str)[i]);
			i++;
		}
		free(*str);
		*str = NULL;
	}
}

char		*ft_strjoin_mod(char *a, char *b)
{
	char	*str;

	str = ft_strjoin(a, b);
	ft_strdel(&a);
	return (str);
}

char		*ft_strjoin_mod_rew(char *a, char *b)
{
	char	*str;

	str = ft_strjoin(a, b);
	ft_strdel(&b);
	return (str);
}

int			array_length(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}

int			is_numeric(char *str_val)
{
	char	*str;
	char	*p1;

	str = ft_strtrim(str_val);
	p1 = str;
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
		{
			if (*str != '-' && *str != '+')
			{
				ft_strdel(&p1);
				return (FALSE);
			}
		}
		str++;
	}
	ft_strdel(&p1);
	return (TRUE);
}
