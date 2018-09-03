/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akotilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 11:23:08 by akotilie          #+#    #+#             */
/*   Updated: 2018/08/19 11:25:25 by akotilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <unistd.h>
# include <stdio.h>

typedef	struct		s_i // image
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				xs; // size x
	int				ys; // size y
	int				cp; // count of points
    char			*d; // data
	int				*x;
	int				*y;
	int				*z;
	unsigned int	*c; //points
}					t_i;

int     read_map(t_i *ti, char *f, int i);

void    print_state(t_i *ti); // temp

#endif