/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:51:28 by mel-atti          #+#    #+#             */
/*   Updated: 2024/12/22 18:03:57 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor_routine(void *arg)
{
	t_rules	*general;

	general = (t_rules *)arg;
	while (1)
	{
		usleep(100);
		if (check_simulation_ending(general) == 1)
			break ;
		if (check_death(general) == 1)
			break ;
		if (general->max_meals != -1)
		{
			pthread_mutex_lock(&general->finished_lock);
			if ((general->finished_count >= general->philo_count))
			{
				general->stop_simulation = 1;
				pthread_mutex_unlock(&general->finished_lock);
				printf("finished!! \n");
				break ;
			}
			pthread_mutex_unlock(&general->finished_lock);
		}
	}
	return (NULL);
}

int	check_death(t_rules *general)
{
	int			i;
	long long	last_meal;
	long long	now;

	i = -1;
	while (++i < general->philo_count)
	{
		if (!philo_eating(&general->philos[i]))
		{
			now = get_timestamp();
			pthread_mutex_lock(&general->philos[i].last_meal_lock);
			last_meal = general->philos[i].last_meal;
			pthread_mutex_unlock(&general->philos[i].last_meal_lock);
			if (now - last_meal > general->time_to_die + 1)
			{
				handle_death(general, i);
				return (1);
			}
		}
	}
	return (0);
}

int	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->ph_lock);
	if (philo->eating == 1)
	{
		pthread_mutex_unlock(&philo->ph_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->ph_lock);
	return (0);
}

int	check_simulation_ending(t_rules *general)
{
	pthread_mutex_lock(&general->output_lock);
	pthread_mutex_lock(&general->finished_lock);
	if (general->stop_simulation)
	{
		pthread_mutex_unlock(&general->output_lock);
		pthread_mutex_unlock(&general->finished_lock);
		return (1);
	}
	pthread_mutex_unlock(&general->output_lock);
	pthread_mutex_unlock(&general->finished_lock);
	return (0);
}

void	handle_death(t_rules *general, int i)
{
	long long	elapsed;

	pthread_mutex_lock(&general->finished_lock);
	general->stop_simulation = 1;
	pthread_mutex_unlock(&general->finished_lock);
	elapsed = get_timestamp() - general->philos[i].start_time;
	pthread_mutex_lock(&general->output_lock);
	printf("%06lld %d died\n", elapsed, general->philos[i].id);
	pthread_mutex_unlock(&general->output_lock);
}
