/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:26:39 by mel-atti          #+#    #+#             */
/*   Updated: 2024/12/22 18:02:09 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_philo
{
	struct s_rules	*rules;
	int				id;
	int				meals_count;
	long long		last_meal;
	long long		start_time;
	bool			eating;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	ph_lock;
	pthread_mutex_t	last_meal_lock;
	pthread_t		tr;
}	t_philo;

typedef struct s_rules
{
	int				philo_count;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				max_meals;
	int				finished_count;
	int				stop_simulation;
	pthread_mutex_t	*forks;
	pthread_mutex_t	output_lock;
	pthread_mutex_t	finished_lock;
	pthread_t		*threads;
	t_philo			*philos;
}	t_rules;

// routines and actions
void		*monitor_routine(void *arg);
int			check_death(t_rules *general);
void		handle_death(t_rules *general, int i);
int			philo_eating(t_philo *philo);
void		*start_dinner(void *arg);
int			small_dinner_check(t_rules *general, t_philo *philo);
int			check_simulation_ending(t_rules *general);
int			ft_eating(t_philo *philo, t_rules *general);
int			handle_single_philo(t_philo *philo, t_rules *general);
int			handle_zero_meals(t_philo *philo, t_rules *general);
void		pick_the_forks(t_philo *philo, t_rules *general);
void		change_eating_status(t_philo *philo);
int			increment_check(t_philo *philo, t_rules *general);

// initialize
int			input_checker(int ac, char **av);
int			final_check(int ac, char **av);
int			initialize_data(t_rules *general, char **av);
int			init_rules(t_rules *general, char **av);
void		init_philosophers(t_rules *general);

// utils
void		message_log(t_rules *general,
				t_philo *philo, int id, const char *message);
void		safe_usleep(long long time_in_ms);
void		clean_everything(t_rules *general);
long long	get_timestamp(void);
int			error_msg(char *str);

// helper funcs
int			ft_isspace(int c);
long long	ft_atol(char *nptr);
int			ft_isdegit(int c);
int			ft_issign(int c);

#endif
