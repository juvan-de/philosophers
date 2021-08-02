/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: julesvanderhoek <julesvanderhoek@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/06 17:33:08 by julesvander   #+#    #+#                 */
/*   Updated: 2021/08/02 15:30:57 by juvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	goto_exit(t_philo *philo, pthread_t *threads)
{
	free(philo->data->mutex);
	free(threads);
	free(philo);
	return ;
}

int		main(int argc, char **argv)
{
	int	i;
	t_data data;
	pthread_t *threads;
	t_philo *philos;

	if (argc < 5 || argc > 6)
	{
		printf("Incorrect arguments\n");
		return (0);
	}
	i = data_init(argv, &data);
	if (i == 1)
		return (0);
	threads = malloc(sizeof(pthread_t) * data.philo_num);
	philos = malloc(sizeof(t_philo) * data.philo_num);
	if (threads && philos)
		create_threads(threads, philos, &data);
	return (0);
}
