/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:55:34 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/06 16:12:34 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	sleeping(t_philo	*philo)
{
	print_output(SLEEPING, philo);
	go_sleep(philo->table->time_to_sleep);
}

static void	think(t_philo *philo)
{
	print_output(THINKING, philo);
	// go_sleep()
}

static void eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	print_output(GRAB_1ST_FORK, philo);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	print_output(GRAB_2ND_FORK, philo);
	print_output(EATING, philo);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILLISECOND));
	// printf("Last meal time : %ld", philo->last_meal_time);
	increase_long(&philo->philo_mtx, &philo->meals_counter);
	if (philo->meals_counter == philo->table->meals_limit)
		set_bool(&philo->philo_mtx, &philo->full, true);
	go_sleep(philo->table->time_to_eat);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

static void	*one_philo_simulation(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	print_output(GRAB_1ST_FORK, philo);
	go_sleep(philo->table->time_to_die);
	set_bool(&philo->table->table_mtx, &philo->table->simulation_finished, true);
	print_output(DIED, philo);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);

	return (NULL);
}

static void	*dinner(void	*arg)
{
	 t_philo	*philo;

	 philo = (t_philo *)arg;
	 wait_all_threads(philo->table);
	 while (!get_bool(&philo->table->table_mtx, &philo->table->simulation_finished))
	 {
		if (philo->full)
			break;
		eat(philo);
		sleeping(philo);
		think(philo);
	 }
	 return (NULL);
}

void	simulation(t_table *table)
{
	int	i;
	
	i = 0;
	if (table->meals_limit == 0)
	return ;
	if (table->num_of_philos == 1)
	safe_thread_handle(&table->philos_arr[0].thread_id, one_philo_simulation, &table->philos_arr[0], CREATE);
	else
	{
		while (i < table->num_of_philos)
		{
			safe_thread_handle(&table->philos_arr[i].thread_id, dinner, &table->philos_arr[i], CREATE);
			i++;
		}
		safe_thread_handle(&table->waiter, monitor, table, CREATE);
	}
	// table->start_simulation_time = get_time(MILLISECOND);
	set_long(&table->table_mtx, &table->start_simulation_time ,get_time(MILLISECOND));
	set_bool(&table->table_mtx, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->num_of_philos)
		safe_thread_handle(&table->philos_arr[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mtx, &table->simulation_finished, true);
	printf(Y "\n %d \n",table->simulation_finished);
	if (table->num_of_philos > 1)
		safe_thread_handle(&table->waiter, NULL, NULL, JOIN);
}