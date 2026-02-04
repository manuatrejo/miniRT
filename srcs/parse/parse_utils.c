/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:40:13 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/04 06:47:05 by maanguit         ###   ########.fr       */
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

bool	parse_range_double(const char *s, t_real min, t_real max, t_real *out)
{
	t_real	v;

	if (!s || !out)
		return (false);
	v = ft_atof(s);
	if (v < min || v > max)
		return (false);
	*out = v;
	return (true);
}

bool	parse_positive_double(const char *s, t_real *out)
{
	t_real	v;

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
	t_real	len;
	const t_real	eps = (t_real)1e-6;

	if (!dir)
		return (false);
	if (!parse_coord(&v, str))
		return (false);
	len = vec_length(v);
	if (len < eps)
		return (false);
	*dir = vec_div(v, len);
	return (true);
}
