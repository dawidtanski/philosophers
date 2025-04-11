/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:18:46 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/11 18:14:15 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	sleeping(t_philo	*philo)
{
	print_output(SLEEPING, philo);
	go_sleep(philo->table->time_to_sleep);
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
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	go_sleep(t_think * 0.42);
}

void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	print_output(GRAB_1ST_FORK, philo);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	print_output(GRAB_2ND_FORK, philo);
	print_output(EATING, philo);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILLISECOND));
	increase_long(&philo->philo_mtx, &philo->meals_counter);
	if (philo->meals_counter == philo->table->meals_limit)
		set_bool(&philo->philo_mtx, &philo->full, true);
	go_sleep(philo->table->time_to_eat);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}
