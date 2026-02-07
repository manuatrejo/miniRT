/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 20:26:07 by cress             #+#    #+#             */
/*   Updated: 2026/02/07 15:17:42 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	parse_digits_color(char **c_split)
{
	int	i;
	int	j;

	i = 0;
	while (c_split[i])
	{
		j = 0;
		if (c_split[i][j] == '\0')
			return (false);
		while (c_split[i][j])
		{
			if (ft_isdigit(c_split[i][j]) == 0)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	parse_float_body(const char *s, int j)
{
	int	seen_digit;
	int	seen_dot;

	seen_digit = 0;
	seen_dot = 0;
	while (s[j])
	{
		if (ft_isdigit((unsigned char)s[j]))
			seen_digit = 1;
		else if (s[j] == '.')
		{
			if (seen_dot)
				return (false);
			if (!seen_digit)
				return (false);
			if (s[j + 1] == '\0' || ft_isdigit((unsigned char)s[j + 1]) == 0)
				return (false);
			seen_dot = 1;
		}
		else
			return (false);
		j++;
	}
	return (seen_digit);
}

bool	parse_float_token(const char *s)
{
	int	j;

	j = 0;
	if (!s || s[0] == '\0')
		return (false);
	if (s[j] == '+' || s[j] == '-')
		j++;
	if (s[j] == '\0')
		return (false);
	return (parse_float_body(s, j));
}

bool	parse_digits(char **c_split)
{
	int	i;

	if (!c_split)
		return (false);
	i = 0;
	while (c_split[i])
	{
		if (!parse_float_token(c_split[i]))
			return (false);
		i++;
	}
	return (true);
}
