/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: julesvanderhoek <julesvanderhoek@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/08 14:25:26 by julesvander   #+#    #+#                 */
/*   Updated: 2021/07/08 15:20:00 by julesvander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	struct timeval	current_time;
	struct timeval	time_passed;

	gettimeofday(&current_time, NULL);
	gettimeofday(&time_passed, NULL);
	printf("[%zu ms] philosopher %d is eating\n", time_passed_in_ms(philo->data->start_sim, time_passed), philo->id);
	philo->last_dinner = current_time;
	philo->times_eaten++;
	while (time_passed_in_ms(current_time, time_passed) <= philo->data->time_to_eat)
		gettimeofday(&time_passed, NULL);
	pthread_mutex_unlock(&(philo->data->mutex[philo->id - 1]));
	if (philo->id == philo->data->philo_num)
		pthread_mutex_unlock(&(philo->data->mutex[0]));
	else
		pthread_mutex_unlock(&(philo->data->mutex[philo->id]));
}

void	philo_think(t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(&(philo->data->mutex[philo->id - 1]));
	gettimeofday(&time, NULL);
	printf("[%zu ms] philosopher %d has taken a fork1\n", time_passed_in_ms(philo->data->start_sim, time), philo->id);
	if (philo->id == philo->data->philo_num)
		pthread_mutex_lock(&(philo->data->mutex[0]));
	else
		pthread_mutex_lock(&(philo->data->mutex[philo->id]));
	gettimeofday(&time, NULL);
	printf("[%zu ms] philosopher %d has taken a fork2\n", time_passed_in_ms(philo->data->start_sim, time), philo->id);
}

void	philo_sleep(t_philo *philo)
{
	struct timeval	time_passed;
	struct timeval	current_time;

	gettimeofday(&time_passed, NULL);
	gettimeofday(&current_time, NULL);
	printf("[%zu ms] philosopher %d is sleeping\n", time_passed_in_ms(philo->data->start_sim, current_time), philo->id);
	while (time_passed_in_ms(current_time, time_passed) <= philo->data->time_to_sleep)
		gettimeofday(&time_passed, NULL);
	printf("[%zu ms] philosopher %d is thinking\n", time_passed_in_ms(philo->data->start_sim, time_passed), philo->id);
}

void	philo_actions(t_philo *philo)
{
	struct timeval current_time;
	struct timeval time_passed;

	while (philo->is_alive == true && philo->is_full == false)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	philo->data->full_philos++;
}