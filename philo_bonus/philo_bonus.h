/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:04:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/20 16:55:40 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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

# define FORK		"fork"
# define PRINT		"print"
# define COUNT		"count"

# define NOT_CHECK	0
# define SLEEP		1
# define EAT		2
# define THINK		3
# define DIE		4
# define TAKE		5
# define UNTAKE		6

# define SLEEP_MSG	"is sleeping"
# define EAT_MSG	"is eating"
# define THINK_MSG	"is thinking"
# define TAKE_MSG	"has taken a fork"
# define UNTAKE_MSG	"drop a fork"
# define DIE_MSG	"died"

typedef struct s_info {
	long	philo_num;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_must_eat;
	long	start_time;
}	t_info;

/******	t_sem	*****
fork : fork value semaphore
print : print binary semaphore
count : count value semaphore
die   : die binary semaphore
*/
typedef struct s_sem {
	sem_t	*fork;
	sem_t	*print;
	sem_t	*count;
	sem_t	*die;
}		t_sem;

/***** t_philo *****
*/
typedef struct s_philo {
	int		*flag;
	t_info	*info;
	t_sem	*sem;
}	t_philo;

/* ft_lib_bonus.c */
size_t		ft_strlen(const char *s);
int			ft_isdigit(int c);
int			ft_isspace(char s1);
long		ft_atol(const char *str);
long		ft_usec_now(void);

/* init_bonus.c */
int			check_atol(const char *input, long *output);
int			ft_init_info(t_info *info, int argc, char **argv);
t_sem		*ft_init_sem(t_info *info);
void		ft_unlink_sem(t_sem **sem);

/* philo_bonus.c */
int			philo(t_info *info, t_sem *sem);

/* thread_bonus.c */
void		print_msg(t_philo *ph, long usec, int flag);
void		*th_eating(void *in);
void		*th_sleeping(void *in);
void		*th_thinking(void *in);

#endif
