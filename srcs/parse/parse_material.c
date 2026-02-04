/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 06:23:38 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/04 10:58:01 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	count_tokens(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}

bool	p_material(t_real *r, t_real *m, t_color *albedo, char **split)
{
	int	n;
	int	base;

	*m = (t_real)0.0;
	*r = (t_real)0.6;
	n = count_tokens(split);
	base = 0;
	if (split[0] && ft_strcmp(split[0], "sp") == 0)
		base = 4;
	else if (split[0] && ft_strcmp(split[0], "pl") == 0)
		base = 4;
	else if (split[0] && ft_strcmp(split[0], "cy") == 0)
		base = 6;
	if (base != 0 && n == base)
		return (true);
	if (base != 0 && n != base + 3)
		return (false);
	if (base == 0)
		return (true);
	if (!parse_color(albedo, split[n - 3]))
		return (false);
	if (!parse_range_double(split[n - 2], 0.0, 1.0, m))
		return (false);
	if (!parse_range_double(split[n - 1], 0.0, 1.0, r))
		return (false);
	if (*r < (t_real)0.04)
		*r = (t_real)0.04;
	return (true);
}

