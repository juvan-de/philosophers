/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: julesvanderhoek <julesvanderhoek@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/06 17:33:08 by julesvander   #+#    #+#                 */
/*   Updated: 2021/07/08 14:59:16 by julesvander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	goto_exit(int i)
{
	//free alle shit en return
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
	i = 1;
	data_init(argv, &data);
	threads = malloc(sizeof(pthread_t) * data.philo_num);
	philos = malloc(sizeof(t_philo) * data.philo_num);
	if (threads && philos)
		create_threads(threads, philos, &data);
	return (0);
}
