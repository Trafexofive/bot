/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 01:42:05 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/25 01:42:05 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bot.hpp"
#include "../inc/Reminder.hpp"

int     Bot::coreLoop(int ac, char **av) {
    
  parseArgs(ac, av);
  DisplayBotInfo();
  initUptime();

  if (!connectToServer()) {
    std::cerr << "Failed to connect to server" << std::endl;
    return 1;
  }
  registerBot();
  while (1) {
      if (!processServerResponse())
        break;
    sleep(1);
  }
  return 0;
}
