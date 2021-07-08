/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: julesvanderhoek <julesvanderhoek@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/07 16:37:36 by julesvander   #+#    #+#                 */
/*   Updated: 2021/07/08 15:51:11 by julesvander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_init(char **argv, t_data *data)
{
	pthread_mutex_t	*mutex;
	struct timeval	start;
	int				i;

	i = 0;
	gettimeofday(&start, NULL);
	data->start_sim = start;
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	mutex = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	while (i < data->philo_num)
	{
		pthread_mutex_init(&(mutex[i]), NULL);
		i++;
	}
	data->mutex = mutex;
	data->philo_is_ded = false;
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
}

void	init_philo(t_philo *philo, int num, t_data *data)
{
	struct timeval time;

	philo->id = num + 1;
	gettimeofday(&time, NULL);
	philo->last_dinner = time;
	philo->data = data;
	philo->is_alive = true;
	philo->is_full = false;
	philo->times_eaten = 0;
	printf("philosopher %d was created\n", philo->id);
}

void	create_threads(pthread_t *threads, t_philo *philos, t_data *data)
{
	int i;
	struct timeval	current_time;

	i = 0;
	while (i < data->philo_num)
	{
		init_philo((&philos[i]), i, data);
		pthread_create((&threads[i]), NULL, (void*)philo_actions, (&philos[i]));
		i++;
	}
	i = 0;
	while (data->full_philos < data->philo_num)
	{
		if (i == data->philo_num)
			i = 0;
		gettimeofday(&current_time, NULL);
		if (time_passed_in_ms(philos[i].last_dinner, current_time) > data->time_to_die)
		{
			printf("[%zu ms] philosopher %d has died\n", time_passed_in_ms(data->start_sim, current_time), i + 1);
			philos[i].is_alive = false;
			data->philo_is_ded = true;
			return ;
		}
		if (philos[i].times_eaten == data->must_eat && philos[i].is_full == false)
		{
			printf("philosopher %d has had enough food\n", i + 1);
			philos[i].is_full = true;
		}
		i++;
	}
}
