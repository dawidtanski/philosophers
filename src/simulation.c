/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:55:34 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/09 12:36:17 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*one_philo_simulation(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	wait_all_threads(philo->table);
	increase_long(&philo->table->table_mtx, &philo->table->threads_running_nbr);
	print_output(GRAB_1ST_FORK, philo);
	go_sleep(philo->table->time_to_die);
	print_output(DIED, philo);
	set_bool(&philo->table->table_mtx, &philo->table->sim_end, true);
	return (NULL);
}

static void	*dinner(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	increase_long(&philo->table->table_mtx, &philo->table->threads_running_nbr);
	set_long(&philo->philo_mtx, &philo->last_meal_time, philo->table->start_t);
	while (!get_bool(&philo->table->table_mtx, &philo->table->sim_end))
	{
		if (get_bool(&philo->philo_mtx, &philo->full))
			break ;
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

static void	set_start(t_table *table)
{
	set_long(&table->table_mtx, &table->start_t, get_time(MILLISECOND));
	set_bool(&table->table_mtx, &table->all_threads_ready, true);
}

void	simulation(t_table *table)
{
	int	i;

	i = -1;
	if (table->meals_limit == 0)
		return ;
	if (table->num_of_philos == 1)
	{
		set_long(&table->table_mtx, &table->start_t, get_time(MILLISECOND));
		thread_handle(&table->philos_arr[0].thread_id,
			one_philo_simulation, &table->philos_arr[0], CREATE);
	}
	else
	{
		while (++i < table->num_of_philos)
			thread_handle(&table->philos_arr[i].thread_id,
				dinner, &table->philos_arr[i], CREATE);
		thread_handle(&table->waiter, monitor, table, CREATE);
	}
	set_start(table);
	i = -1;
	while (++i < table->num_of_philos)
		thread_handle(&table->philos_arr[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mtx, &table->sim_end, true);
	if (table->num_of_philos > 1)
		thread_handle(&table->waiter, NULL, NULL, JOIN);
}
