/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:56:45 by vsharma           #+#    #+#             */
/*   Updated: 2024/02/19 11:37:25 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_table *philo)
{
	free(philo->table_mutex);
	free(philo->philo);
	free(philo->fork_mutex);
}

void	display_message(char *str, t_philo *philo)
{
	if (!check_dead_2(philo))
	{
		pthread_mutex_lock(philo->table->table_mutex);
		printf("%d %d %s\n", get_time() - philo->table->start_timer, philo->id,
			str);
		pthread_mutex_unlock(philo->table->table_mutex);
	}
}

int	ft_atoi(char *str)
{
	int		count;
	long	result;
	int		sign;

	count = 0;
	result = 0;
	sign = 1;
	while (str[count] == '\r' || str[count] == '\t' || str[count] == ' '
		|| str[count] == '\f' || str[count] == '\v' || str[count] == '\n')
		count++;
	if (str[count] == '-')
	{
		sign = -1;
		count++;
	}
	else if (str[count] == '+')
		count++;
	if (!(str[count] >= '0' && str[count] <= '9'))
		return (0);
	while (str[count] >= '0' && str[count] <= '9')
		result = result * 10 + (str[count++] - '0');
	return (result * sign);
}

int	get_time(void)
{
	static struct timeval	t;
	int						millisecond;

	gettimeofday(&t, NULL);
	millisecond = ((t.tv_sec * 1000) + (t.tv_usec / 1000));
	return (millisecond);
}

/*int	get_time_for_sleeping(void)
{
	static struct timeval	t;
	int						millisecond;

	gettimeofday(&t, NULL);
	millisecond = ((t.tv_sec * 1000) + (t.tv_usec / 1000));
	return (millisecond);
}*/

void	ft_sleep(int time, t_philo *philo)
{
	int	start;

	(void)philo;
	start = get_time();
	while ((get_time() - start) < time)
		usleep(50);
}
