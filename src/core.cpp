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
  initUptime();
  addReminderChannel("#clever", "Hello from my bot", 10);

  // make reminder.init() and reminder.run() functions
  // reminders will be relative to bot uptime


  if (!connectToServer()) {
    std::cerr << "Failed to connect to server" << std::endl;
    return 1;
  }
  registerBot();
  // listChannels();
  while (1) {
    processServerResponse();
    sleep(1);
  }
  return 0;
}
