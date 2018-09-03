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
  t_i       ti;

//  read_map(&ti, argv[1], -1);
  if (argc != 2)
    return (0);
  printf("validation result: %i",read_map(&ti, argv[1], -1));
  ti.mlx_ptr = mlx_init();
	ti.win_ptr = mlx_new_window(ti.mlx_ptr, 500, 500, "fdf");
	mlx_loop(ti.mlx_ptr);
  //while (1);
	return (0);
}
