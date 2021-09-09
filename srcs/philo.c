/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: julesvanderhoek <julesvanderhoek@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/08 14:25:26 by julesvander   #+#    #+#                 */
/*   Updated: 2021/09/09 14:05:34 by juvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	struct timeval	time_passed;

	gettimeofday(&time_passed, NULL);
	philo_print("is eating", philo, false);
	pthread_mutex_lock(&philo->data->death_check);
	philo->last_dinner = time_passed.tv_sec * 1000 + time_passed.tv_usec / 1000;
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->data->death_check);
	while (time_passed_in_ms(philo->last_dinner) <= philo->data->time_to_eat)
		usleep(100);
	pthread_mutex_unlock(&(philo->data->mutex[philo->id - 1]));
	gettimeofday(&time_passed, NULL);
	if (philo->id == philo->data->philo_num)
		pthread_mutex_unlock(&(philo->data->mutex[0]));
	else
		pthread_mutex_unlock(&(philo->data->mutex[philo->id]));
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex[philo->id - 1]));
	philo_print("has taken a fork", philo, false);
	if (philo->id == philo->data->philo_num)
		pthread_mutex_lock(&(philo->data->mutex[0]));
	else
		pthread_mutex_lock(&(philo->data->mutex[philo->id]));
	philo_print("has taken a fork", philo, false);
}

void	philo_sleep(t_philo *philo)
{
	struct timeval	current;
	size_t			convertable;

	gettimeofday(&current, NULL);
	convertable = current.tv_sec * 1000 + current.tv_usec / 1000;
	philo_print("is sleeping", philo, false);
	while (time_passed_in_ms(convertable) <= philo->data->time_to_sleep)
		usleep(100);
	philo_print("is thinking", philo, false);
}

void	philo_actions(t_philo *philo)
{
	
	while (philo->is_full == false && philo->data->philo_is_ded == false)
	{
		philo_think(philo);
		philo_eat(philo);
		if (philo->times_eaten == philo->data->must_eat)
			philo->is_full = true;
		philo_sleep(philo);
	}
	if (philo->times_eaten == philo->data->must_eat)
	{
		printf("philosopher %d has had enough food\n", philo->id);
		philo->data->full_philos++;
	}
}
