/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:48:42 by mel-atti          #+#    #+#             */
/*   Updated: 2024/12/22 17:39:00 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	clean_everything(t_rules *general)
{
	int	i;

	i = -1;
	if ((general->forks))
	{
		while (++i < general->philo_count)
		{
			pthread_mutex_destroy(&general->forks[i]);
			pthread_mutex_destroy(&(general->philos[i].ph_lock));
			pthread_mutex_destroy(&(general->philos[i].last_meal_lock));
		}
		free((general->forks));
	}
	if (general->threads)
		free((general->threads));
	if (general->philos)
		free((general->philos));
	pthread_mutex_destroy(&general->output_lock);
	pthread_mutex_destroy(&general->finished_lock);
}

long long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0));
}

void	message_log(t_rules *general,
		t_philo *philo, int id, const char *message)
{
	long long	now;

	pthread_mutex_lock(&general->output_lock);
	now = get_timestamp() - philo->start_time;
	if (!general->stop_simulation)
		printf("%06lld %d %s\n", now, id, message);
	pthread_mutex_unlock(&general->output_lock);
}

void	safe_usleep(long long time_in_ms)
{
	long long	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < time_in_ms)
		usleep(100);
}

int	error_msg(char *str)
{
	if (str)
		printf("Error: %s\n", str);
	return (1);
}
