/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: julesvanderhoek <julesvanderhoek@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/06 18:29:41 by julesvander   #+#    #+#                 */
/*   Updated: 2021/08/02 16:10:42 by juvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct		s_data
{
	int				philo_num;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				must_eat;
	size_t			start_sim;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	death_check;
	int				full_philos;
	bool			philo_is_ded;
}					t_data;

typedef struct		s_philo
{
	int				id;
	t_data			*data;
	size_t			last_dinner;
	int				times_eaten;
	bool			is_alive;
	bool			is_full;
}					t_philo;

/*
	init
*/

int					data_init(char **argv, t_data *data);
void				create_threads(pthread_t *threads, t_philo *philos,
												t_data *data);
void				goto_exit(t_philo *philo, pthread_t *threads);

/*
	philo
*/

void				philo_actions(t_philo *philo);

/*
	utils
*/

int					ft_atoi(const char *str);
size_t				time_passed_in_ms(size_t pre_time);

#endif