#include "fdf.h"

unsigned int		atoi_hex(char *str)
{
	unsigned long long	nbr;
	int					i;
    int                 r;

	i = -1;
	nbr = 0;
    r = -1;
	while (str[++i])
	{
        (str[i] == 'a' || str[i] == 'A') ? r = 10 : 0;
        (str[i] == 'b' || str[i] == 'B') ? r = 11 : 0;
        (str[i] == 'c' || str[i] == 'C') ? r = 12 : 0;
        (str[i] == 'd' || str[i] == 'D') ? r = 13 : 0;
        (str[i] == 'e' || str[i] == 'E') ? r = 14 : 0;
        (str[i] == 'F' || str[i] == 'F') ? r = 15 : 0;
        (ft_isdigit(str[i])) ? r = str[i] - '0' : 0;
        if (r < 0)
            return (-1);
		nbr = nbr * 16 + r;
		if (nbr > 9223372036854775807)
			return (-1);
	}
	return (nbr);
}

int     count(char *s)
{
    int     j;
    int     t;
    char    **row;

    j = 0;
    row = ft_strsplit(s, ' ');
    while (row[j])
        j++;
    t = -1;
    while (++t < j)
        free(row[t]);
    return (j);
}

int     fill_z_c(t_i **ti, char *s, int i)
{
    
}

int     validate_row(t_i **ti, char *s, int y, int i) // n - norma , j = -1, i = -1
{
    char    **row;

    row = ft_strsplit(s, ' ');
    while (row[++i])
    {
        (*ti)->y[(*ti)->cp] = y;
        (*ti)->x[(*ti)->cp] = i;
        if (ft_strstr(s, ','))
        {
            (ft_strstr(s, 'x')) ? (*ti)->c[(*ti)->cp] = atoi_hex(ft_strchr(s, 'x') + 1) : 0;
            (ft_strstr(s, 'X')) ? (*ti)->c[(*ti)->cp] = atoi_hex(ft_strchr(s, 'X') + 1) : 0;
        }
        if ((*ti)->c[(*ti)->cp] < 0)
            return (-1);
    }
    if (i != (*ti)->xs)
        return (-1);
   return (1);
}


int     read_map(t_i **ti, char *f, int i) // i = -1 ; f - file name
{
    char *temp;
    int fd;

    (*ti)->cp = -1;
    (*ti)->ys = 0;
    fd = open(f, O_RDONLY);
    while (get_next_line(fd, &temp) > 0)
        (*ti)->ys++;
    close(fd);
    fd = open(f, O_RDONLY);
    if (get_next_line(fd, &temp) > 0)
    {
        (*ti)->xs = count(temp);
        (*ti)->x = (int*)ft_memalloc(sizeof(int) * (*ti)->xs * (*ti)->ys);
        (*ti)->x = (int*)ft_memalloc(sizeof(int) * (*ti)->xs * (*ti)->ys);
        (*ti)->z = (int*)ft_memalloc(sizeof(int) * (*ti)->xs * (*ti)->ys);
        (*ti)->c = (int*)ft_memalloc(sizeof(int) * (*ti)->xs * (*ti)->ys);
        if (validate_row(ti, temp, ++i) < 0)
            return (-1);
        free(temp);
        while (get_next_line(fd, &temp) > 0)
        {
            validate_row(ti, temp, ++i);
            free(temp);
        }
    }
    print_state(ti);
    free((*ti)->lm);
    return (1);
}

void    print_state(t_i **ti)
{
    printf(" TI->LM %s\n", (*ti)->lm);
    printf(" X =  %i\n", (*ti)->x);
}

