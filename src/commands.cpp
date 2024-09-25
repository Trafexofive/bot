/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 02:03:57 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/25 02:03:57 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bot.hpp"

// void Bot::getCommand(const std::string &line)
// {
//
// }

bool Bot::isCommand(const std::string &response) {
  if (response.find("/cmd") != std::string::npos)
    return true;
  return false;
}

void Bot::processCommand(const std::string &response) {
  std::vector<std::string> args = getCommandArgs(response);
  std::string command = args[0];
  int argCount = commandArgsCount(command) - 1;

  std::vector<std::string> availableCmds;
  // commands = {whisper, note, announce, remind, startpoll, endpoll, vote,
  // listpoll, help, quit, unsub, sub}
  // put commands in a vector in then check if command is in vector then call appropriate methode
}

std::vector<std::string> Bot::getCommandArgs(const std::string &response) {
  // find /cmd then add first word after /cmd to vector

  std::vector<std::string> args;
}

int Bot::commandArgsCount(const std::string &command) {

  // count the number of arguments in the command
  int count = 0;

  return count;
}
