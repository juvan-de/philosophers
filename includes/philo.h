/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: julesvanderhoek <julesvanderhoek@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/06 18:29:41 by julesvander   #+#    #+#                 */
/*   Updated: 2021/07/08 15:28:08 by julesvander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct		s_data
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	struct timeval	start_sim;
	pthread_mutex_t	*mutex;
	int				full_philos;
	bool			philo_is_ded;
}					t_data;

typedef struct	s_philo
{
	int				id;
	t_data			*data;
	struct timeval	last_dinner;
	int				times_eaten;
	bool			is_alive;
	bool			is_full;
}				t_philo;

/*
	init
*/

void	data_init(char **argv, t_data *data);
void	create_threads(pthread_t *threads, t_philo *philos, t_data *data);

/*
	philo
*/

void	philo_actions(t_philo *philo);


/*
	utils
*/

int				ft_atoi(const char *str);
size_t			time_passed_in_ms(struct timeval pre_time, struct timeval post_time);

#endif