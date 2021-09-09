/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: julesvanderhoek <julesvanderhoek@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/06 18:29:08 by julesvander   #+#    #+#                 */
/*   Updated: 2021/09/09 18:19:04 by juvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_atos(const char *str)
{
	int		i;
	size_t	res;
	size_t	checker;

	res = 0;
	i = 0;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9) || (str[i] == '+'
			&& str[i + 1] >= '0' && str[i + 1] <= '9'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		checker = res;
		res = res * 10;
		res += (str[i] - '0');
		if (res >= checker)
			i++;
		else
			return (0);
	}
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

void	philo_print(char *message, t_philo *philo, bool ded)
{
	if (ded)
	{
		printf("[%zu ms] philosopher %d %s\n",
			time_passed_in_ms(philo->data->start_sim), philo->id, message);
		return ;
	}
	pthread_mutex_lock(&(philo->data->write));
	pthread_mutex_lock(&(philo->data->death_check));
	if (philo->data->philo_is_ded == false)
		printf("[%zu ms] philosopher %d %s\n",
			time_passed_in_ms(philo->data->start_sim), philo->id, message);
	pthread_mutex_unlock(&(philo->data->death_check));
	pthread_mutex_unlock(&(philo->data->write));
}
