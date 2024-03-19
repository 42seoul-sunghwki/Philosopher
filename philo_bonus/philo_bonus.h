/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:04:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/19 22:06:42 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>

# define INT_MAX	2147483647
# define INT_MIN	-2147483648
# define THOUSAND	1000

# define TRUE		1
# define FALSE		0

# define FUN_SUC	0
# define FUN_FAIL	1

# define NOT_CHECK	0
# define SLEEP		1
# define EAT		2
# define THINK		3
# define DIE		4

# define SLEEP_MSG	"is sleeping"
# define EAT_MSG	"is eating"
# define THINK_MSG	"is thinking"
# define TAKE_MSG	"has taken a fork"
# define UNTAKE_MSG	"drop a fork"
# define DIE_MSG	"died"

typedef struct s_info {
	long	num_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_must_eat;
}	t_info;

#endif
