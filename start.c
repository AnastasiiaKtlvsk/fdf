/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akotilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:35:25 by akotilie          #+#    #+#             */
/*   Updated: 2018/08/11 19:15:55 by akotilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
  t_i *ti;

  ti = (t_i*)ft_memalloc(sizeof(t_i));
//  read_map(&ti, argv[1], -1);
  printf("validation result: %i",read_map(&ti, argv[1], -1));
 // while (1);
	return (0);
}
