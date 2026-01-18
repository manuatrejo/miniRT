/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:17:09 by maanguit          #+#    #+#             */
/*   Updated: 2026/01/18 22:32:40 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *s)
{
	double	integer;
	double	decimal;
	int		sign;
	int		div;

	sign = 1;
	if (*s == '+' || *s == '-')
		if (*(s++) == '-')
			sign = -1;
	integer = 0.0;
	decimal = 0.0;
	if (!ft_isdigit(*s) && *s != '.')
		return (0.0);
	while (ft_isdigit(*s))
		integer = integer * 10 + (*(s++) - '0');
	div = 1;
	if (*s == '.')
	{
		while (ft_isdigit(*(++s)))
		{
			decimal = decimal * 10 + (*s - '0');
			div *= 10;
		}
	}
	return ((integer + decimal / div) * sign);
}
