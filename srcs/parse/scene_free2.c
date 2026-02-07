/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_free2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 12:45:17 by amonteag          #+#    #+#             */
/*   Updated: 2026/02/07 12:55:23 by amonteag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_cones(t_cone_list *cnl)
{
	t_cone_list	*next;

	while (cnl)
	{
		next = cnl->next;
		free(cnl);
		cnl = next;
	}
}