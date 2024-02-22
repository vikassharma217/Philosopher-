/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:12:29 by vsharma           #+#    #+#             */
/*   Updated: 2024/02/19 11:34:56 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				last_meal;
	int				is_eating;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				num_of_meals;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	int				start_timer;
	int				is_dead;
	int				done_eating;
	int				kill_switch;
	int				simulation_running;
	pthread_mutex_t	*table_mutex;
	pthread_mutex_t	*fork_mutex;
	t_philo			*philo;
}					t_table;

// input_validation
int					validate_input(int argc, char **argv);

// error_handeling
void				handel_input_error(void);
void				handel_resource_init_error(void);

// utils
int					ft_atoi(char *str);
int					get_time(void);
void				display_message(char *str, t_philo *philo);
void				ft_sleep(int time, t_philo *philo);
void				free_all(t_table *philo);
int					check_dead_2(t_philo *philos);

// init_data
int					init_resources(t_table *table, char **argv);
int					init_mutex(t_table *table);
int					init_philo(t_table *table);

// start_simulation
int					run_simulation(t_table *table);
void				join_thread(t_table *table);
void				*routine(void *args);

// monitoring
void				*init_monitoring(void *args);
int					check_dead(t_philo *philo);
int					check_dead_status(t_table *table);
int					check_full_status(t_table *table);

// eating
int					pickup_forks(t_philo *philo);
int					start_eating(t_philo *philo);

// sleeping
void				start_sleeping(t_philo *philo);

// thinking
void				start_thinking(t_philo *philo);

#endif
