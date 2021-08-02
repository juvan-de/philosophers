/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: julesvanderhoek <julesvanderhoek@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/08 14:25:26 by julesvander   #+#    #+#                 */
/*   Updated: 2021/08/02 18:01:07 by juvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	struct timeval	time_passed;

	gettimeofday(&time_passed, NULL);
	printf("[%zu ms] philosopher %d is eating\n", time_passed_in_ms(philo->data->start_sim), philo->id);
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
	printf("[%zu ms] philosopher %d has taken a fork1\n", time_passed_in_ms(philo->data->start_sim), philo->id);
	if (philo->id == philo->data->philo_num)
		pthread_mutex_lock(&(philo->data->mutex[0]));
	else
		pthread_mutex_lock(&(philo->data->mutex[philo->id]));
	printf("[%zu ms] philosopher %d has taken a fork2\n", time_passed_in_ms(philo->data->start_sim), philo->id);
}

void	philo_sleep(t_philo *philo)
{
	struct timeval current;
	size_t convertable;

	gettimeofday(&current, NULL);
	convertable = current.tv_sec * 1000 + current.tv_usec / 1000;
	printf("[%zu ms] philosopher %d is sleeping\n", time_passed_in_ms(philo->data->start_sim), philo->id);
	while (time_passed_in_ms(convertable) <= philo->data->time_to_eat)
		usleep(100);
	printf("[%zu ms] philosopher %d is thinking\n", time_passed_in_ms(philo->data->start_sim), philo->id);
}

void	philo_actions(t_philo *philo)
{
	while (philo->is_alive == true && philo->is_full == false)
	{
		philo_think(philo);
		philo_eat(philo);
		if (philo->times_eaten == philo->data->must_eat)
			philo->is_full = true;
		philo_sleep(philo);
	}
	if (philo->times_eaten == philo->data->must_eat)
		printf("philosopher %d has had enough food\n", philo->id);
	philo->data->full_philos++;
}