/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:18:46 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/13 21:26:35 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	sleeping(t_philo	*philo)
{
	long	t_to_sleep;

	t_to_sleep = get_long(&philo->table->table_mtx, &philo->table->time_to_sleep);
	print_output(SLEEPING, philo);
	precise_usleep(t_to_sleep, philo->table);
}

void	think(t_philo *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	print_output(THINKING, philo);
	if (philo->table->num_of_philos % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep + 30;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think, philo->table);
}

void	eat(t_philo *philo)
{
	long	t_to_eat;

	t_to_eat = get_long(&philo->table->table_mtx, &philo->table->time_to_eat);
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	print_output(GRAB_1ST_FORK, philo);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	print_output(GRAB_2ND_FORK, philo);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILLISECOND));
	print_output(EATING, philo);
	increase_long(&philo->philo_mtx, &philo->meals_counter);
	if (philo->meals_counter == philo->table->meals_limit)
	set_bool(&philo->philo_mtx, &philo->full, true);
	precise_usleep(t_to_eat, philo->table);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}
