/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:03:12 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/06 10:33:25 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_real	clamp_real(t_real v, t_real min, t_real max)
{
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}
