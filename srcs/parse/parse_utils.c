/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:13 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/02 03:12:25 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	line_is_blank(const char *s)
{
	if (!s)
		return (true);
	while (*s)
	{
		if (!ft_isspace(*s))
			return (false);
		s++;
	}
	return (true);
}

bool	ensure_token_count(char **tokens, int expected)
{
	int	i;

	if (!tokens)
		return (false);
	i = 0;
	while (tokens[i])
		i++;
	return (i == expected);
}

bool	parse_range_double(const char *s, double min, double max, double *out)
{
	double	v;

	if (!s || !out)
		return (false);
	v = ft_atof(s);
	if (v < min || v > max)
		return (false);
	*out = v;
	return (true);
}

bool	parse_positive_double(const char *s, double *out)
{
	double	v;

	if (!s || !out)
		return (false);
	v = ft_atof(s);
	if (v <= 0.0)
		return (false);
	*out = v;
	return (true);
}

bool	parse_dir_normalized(t_dir *dir, char *str)
{
	t_dir	v;
	double	len;
	double	diff;

	if (!dir)
		return (false);
	if (!parse_coord(&v, str))
		return (false);
	len = vec_length(v);
	diff = len - 1.0;
	if (diff < 0)
		diff = -diff;
	if (diff > 1e-3)
		return (false);
	*dir = vec_normalize(v);
	return (true);
}
