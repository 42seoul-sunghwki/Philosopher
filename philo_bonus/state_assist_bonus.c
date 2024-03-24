/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:57:27 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/24 18:51:06 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	stop_philo(t_philo *ph, long *start_usec, long cmp_time)
{
	long	now_usec;

	while (TRUE)
	{
		now_usec = ft_usec_now();
		if (now_usec - *start_usec >= ph->info->time_to_die)
		{
			print_msg(ph, now_usec - ph->info->start_time, DIED);
			return (FUN_FAIL);
		}
		else if (now_usec - *start_usec >= cmp_time)
			return (FUN_SUC);
		if (cmp_time - (now_usec - *start_usec) >= THOUSAND)
			usleep(500);
		else
			usleep(100);
	}
}
