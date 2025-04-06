/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:15:35 by dtanski           #+#    #+#             */
/*   Updated: 2025/04/06 15:16:47 by dtanski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void wait_all_threads(t_table *table)
{
    while (!get_bool(&table->table_mtx, &table->all_threads_ready))
        usleep(100);
}