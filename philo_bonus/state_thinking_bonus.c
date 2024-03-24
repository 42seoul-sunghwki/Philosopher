/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_thinking_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:50:47 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/24 18:51:04 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	thinking_philo(t_philo *ph)
{
	long	now_usec;

	now_usec = ft_usec_now();
	print_msg(ph, now_usec - ph->info->start_time, THINK);
	return (FUN_SUC);
}
