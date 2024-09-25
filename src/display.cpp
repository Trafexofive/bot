/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:08:24 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/24 23:08:24 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bot.hpp"

void Bot::DisplayBotInfo() {
  std::cout << "#############  BotInfo   #####################" << std::endl;
  std::cout << "Server address: " << _serverAddress << std::endl;
  std::cout << "Port: " << _port << std::endl;
  std::cout << "Password: " << _password << std::endl;
  std::cout << "Bot name: " << _botName << std::endl;
  std::cout << "Channel name: " << _channelName << std::endl;
  std::cout << "##############################################" << std::endl;
}

// void Bot::DisplayBanner(std::vector<std::string> banner) {
// }

// std::vector<std::string> Bot::getBanner(const std::string &bannerFileName) {
//
//
// }

void Bot::DisplayHelp() {
  std::cout << "#############  Help   #####################" << std::endl;
  std::cout << "Commands: " << std::endl;
  std::cout << "help: Display this help message" << std::endl;
  std::cout << "info: Display bot info" << std::endl;
  std::cout << "banner: Display banner" << std::endl;
  std::cout << "join: Join a channel" << std::endl;
  std::cout << "leave: Leave a channel" << std::endl;
  std::cout << "list: List all channels" << std::endl;
  std::cout << "ping: Ping a user" << std::endl;
  std::cout << "pingserver: Ping the server" << std::endl;
  std::cout << "msg: Send a message to a user" << std::endl;
  std::cout << "msgchannel: Send a message to a channel" << std::endl;
  std::cout << "quit: Quit the bot" << std::endl;
  std::cout << "cmd <command>: for bot specific commands: refer to cmd -h for more" << std::endl;
  std::cout << "##############################################" << std::endl;
}

