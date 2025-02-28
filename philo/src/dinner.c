/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 04:43:37 by mel-atti          #+#    #+#             */
/*   Updated: 2024/12/22 18:02:35 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*start_dinner(void *arg)
{
	t_philo	*philo;
	t_rules	*general;

	philo = (t_philo *)arg;
	general = philo->rules;
	if (small_dinner_check(general, philo) == 1)
		return (NULL);
	while (1)
	{
		if (check_simulation_ending(general) == 1)
			break ;
		if (ft_eating(philo, general) == 1)
			break ;
		message_log(general, philo, philo->id, "is sleeping");
		safe_usleep(general->time_to_sleep);
		message_log(general, philo, philo->id, "is thinking");
	}
	return (NULL);
}

int	ft_eating(t_philo *philo, t_rules *general)
{
	pick_the_forks(philo, general);
	change_eating_status(philo);
	message_log(general, philo, philo->id, "is eating");
	pthread_mutex_lock(&(philo->last_meal_lock));
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&(philo->last_meal_lock));
	safe_usleep(general->time_to_eat);
	change_eating_status(philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (general->max_meals != -1)
	{
		if (increment_check(philo, general) == 1)
			return (1);
	}
	return (0);
}

void	change_eating_status(t_philo *philo)
{
	pthread_mutex_lock(&(philo->ph_lock));
	if (philo->eating == 1)
		philo->eating = 0;
	else if (philo->eating == 0)
		philo->eating = 1;
	pthread_mutex_unlock(&(philo->ph_lock));
}

int	increment_check(t_philo *philo, t_rules *general)
{
	philo->meals_count++;
	pthread_mutex_lock(&general->finished_lock);
	if (philo->meals_count >= general->max_meals)
	{
		general->finished_count++;
		pthread_mutex_unlock(&general->finished_lock);
		return (1);
	}
	pthread_mutex_unlock(&general->finished_lock);
	return (0);
}

int	small_dinner_check(t_rules *general, t_philo *philo)
{
	if (general->philo_count == 1)
		return (handle_single_philo(philo, general));
	else if (general->max_meals == 0)
		return (handle_zero_meals(philo, general));
	return (0);
}
