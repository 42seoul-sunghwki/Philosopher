/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:09:37 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/27 11:15:25 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_philo(t_thread *ph, long *start_eating)
{
	while (1)
	{
		*start_eating = ft_usec_now();
		if (*start_eating >= ph->start_time)
			return ;
		usleep(10);
	}
}

void	*philo(void *input)
{
	t_thread	ph;
	long		start_eating;

	ph = *(t_thread *)input;
	start_philo(&ph, &start_eating);
	while (TRUE)
	{
		if (eating_philo(&ph, &start_eating) == FUN_FAIL)
			return (NULL);
		if (sleeping_philo(&ph, start_eating) == FUN_FAIL)
			return (NULL);
		if (thinking_philo(&ph, start_eating) == FUN_FAIL)
			return (NULL);
	}
}
