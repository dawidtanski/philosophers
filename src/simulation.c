/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:55:34 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/05 09:09:10 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	sleep(t_philo	*philo)
{
	print_output(SLEEPING, philo);
	go_sleep(philo->table->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_output(THINKING, philo);
	// go_sleep()
}

void eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork, LOCK);
	print_output(GRAB_1ST_FORK, philo);
	safe_mutex_handle(&philo->second_fork, LOCK);
	print_output(GRAB_2ND_FORK, philo);
	print_output(EATING, philo);
	set_long(philo->philo_mtx, philo->last_meal_time, get_time(MILLISECOND));
	increase_long(philo->philo_mtx, philo->meals_counter);
	if (philo->meals_counter == philo->table->meals_limit)
		set_bool(philo->philo_mtx, philo->full, true);
	go_sleep(philo->table->time_to_eat);
	safe_mutex_handle(&philo->first_fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork, UNLOCK);
}

void	*one_philo_simulation(t_table *table, void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	
	safe_mutex_handle(&philo->first_fork, LOCK);
	print_output(GRAB_1ST_FORK, philo);
	safe_mutex_handle(&philo->first_fork, UNLOCK);

	go_sleep(200, MILLISECOND);
	print_output(DIED, philo);
	return (NULL);
}

void	*dinner()
{
	
}

void	simulation(t_table *table)
{
	int	i;
	
	i = 0;
	table->start_simulation_time = get_time(MILLISECOND);
	if (table->meals_limit == 0)
	return ;
	if (table->num_of_philos == 1)
	safe_thread_handle(&table->philos_arr[0].thread_id, one_philo_simulation, &table->philos_arr[0], CREATE);
	else
	{
		while (i < table->num_of_philos)
		{
			safe_thread_handle(table->philos_arr[i].thread_id, dinner, table, CREATE);
			i++;
		}
		safe_thread_handle(table->waiter, monitor, table, CREATE);
	}
}