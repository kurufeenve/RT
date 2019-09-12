/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 19:50:40 by dkliukin          #+#    #+#             */
/*   Updated: 2017/10/29 19:50:43 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	char	*trim;
	int		n;
	int		l;

	if (!s)
		return (NULL);
	i = 0;
	n = 0;
	l = ft_strlen(s) - 1;
	while (s[l] == ' ' || s[l] == '\t' || s[l] == '\n' || s[l] == '\r')
		l--;
	if (l + 1 != 0)
	{
		while (s[n] == ' ' || s[n] == '\t' || s[n] == '\n' || s[n] == '\r')
			n++;
	}
	trim = ft_strnew(l + 1 - n);
	while (n != l + 1 && trim)
	{
		trim[i] = s[n];
		n++;
		i++;
	}
	return (trim);
}
