/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: julesvanderhoek <julesvanderhoek@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/07 16:37:36 by julesvander   #+#    #+#                 */
/*   Updated: 2021/08/02 16:42:07 by juvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_init(char **argv, t_data *data)
{
	pthread_mutex_t	*mutex;
	struct timeval	start;
	int				i;

	i = 0;
	gettimeofday(&start, NULL);
	data->start_sim = start.tv_sec * 1000 + start.tv_usec / 1000;
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	mutex = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!mutex)
		return (1);
	while (i < data->philo_num)
	{
		pthread_mutex_init(&(mutex[i]), NULL);
		i++;
	}
	data->full_philos = 0;
	data->mutex = mutex;
	data->philo_is_ded = false;
	data->must_eat = -1;
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	return (0);
}

void	init_philo(t_philo *philo, int num, t_data *data)
{
	struct timeval	time;

	philo->id = num + 1;
	gettimeofday(&time, NULL);
	philo->last_dinner = time.tv_sec * 1000 + time.tv_usec / 1000;
	philo->data = data;
	philo->is_alive = true;
	philo->is_full = false;
	philo->times_eaten = 0;
	printf("philosopher %d was created\n", philo->id);
}

void	check_if_done(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (data->full_philos < data->philo_num)
	{
		if (i == data->philo_num)
			i = 0;
		pthread_mutex_lock(&philos->data->death_check);
		if (time_passed_in_ms(philos[i].last_dinner) > data->time_to_die && philos[i].is_full == false)
		{
			printf("[%zu ms] philosopher %d has died\n",
				time_passed_in_ms(data->start_sim), i + 1);
			philos[i].is_alive = false;
			data->philo_is_ded = true;
			return ;
		}
		pthread_mutex_unlock(&philos->data->death_check);
		i++;
	}
}

void	create_threads(pthread_t *threads, t_philo *philos, t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_num)
	{
		init_philo((&philos[i]), i, data);
		usleep(100);
		pthread_create((&threads[i]), NULL, (void*)philo_actions, (&philos[i]));
		i++;
	}
	i = 0;
	check_if_done(philos, data);
	goto_exit(philos, threads);
}
