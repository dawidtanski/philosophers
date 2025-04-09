/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 06:53:23 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/09 11:47:02 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	clean(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	safe_mutex_handle(&table->table_mtx, DESTROY);
	safe_mutex_handle(&table->write_mtx, DESTROY);
	while (i < table->num_of_philos)
	{
		philo = table->philos_arr + i;
		safe_mutex_handle(&philo->philo_mtx, DESTROY);
		i++;
	}
	free(table->forks_arr);
	free(table->philos_arr);
}
