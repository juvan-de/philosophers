/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: julesvanderhoek <julesvanderhoek@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/06 18:29:08 by julesvander   #+#    #+#                 */
/*   Updated: 2021/09/07 13:58:00 by juvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	prework_atoi(const char *str, int *negative_check)
{
	int	i;

	*negative_check = 1;
	i = 0;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9) || (str[i] == '+'
			&& str[i + 1] >= '0' && str[i + 1] <= '9'))
		i++;
	if (str[i] == '-')
	{
		i++;
		*negative_check = -1;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			negative_check;
	long int	res;
	long int	checker;

	res = 0;
	negative_check = 1;
	i = prework_atoi(str, &negative_check);
	while (str[i] >= '0' && str[i] <= '9')
	{
		checker = res;
		res = res * 10;
		res += (str[i] - '0');
		if (res >= checker)
			i++;
		else
		{
			if (negative_check == -1)
				return (0);
			else
				return (-1);
		}
	}
	res = (int)res * negative_check;
	return (res);
}

size_t	time_passed_in_ms(size_t pre_time)
{
	struct timeval	time;
	size_t			current;

	gettimeofday(&time, NULL);
	current = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current - pre_time);
}
