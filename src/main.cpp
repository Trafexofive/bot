/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:52:49 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/19 20:52:49 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bot.hpp"
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include "../inc/Reminder.hpp"

int main(int ac, char **av) {

  {
    Bot bot;
    bot.coreLoop(ac, av);
  }

  return 0;
}
