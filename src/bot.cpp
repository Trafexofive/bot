/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:26:20 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/19 20:26:20 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bot.hpp"
#include "../inc/tools.hpp"
#include <algorithm>

Bot::Bot() : _clientFdSocket(-1), _botName("bot"), _channelName(""),
             _nickname("botNick"), _password(""), _uptime(0) {} 

Bot::Bot(const Bot &other) { *this = other; }

Bot &Bot::operator=(const Bot &other) {
  if (this != &other) {
    _clientFdSocket = other._clientFdSocket;
    _botName = other._botName;
    _channelName = other._channelName;
    _nickname = other._nickname;
    _password = other._password;
    _uptime = other._uptime;
  }
  return *this;
}

Bot::~Bot() { disconnectFromServer(); }

// ################################## GETTERS AND SETTERS

std::string Bot::getBotName() const { return _botName; }

void Bot::setBotName(const std::string &name) { _botName = name; }


// ################################## CORE

void Bot::processServerResponse() {
  char buffer[1024];
  int bytesRead = recv(_clientFdSocket, buffer, sizeof(buffer) - 1, 0);

  if (bytesRead > 0) {
    buffer[bytesRead] = '\0';

    translateServerResponse(buffer);
  } else if (bytesRead == 0) {
    std::cout << "Server closed the connection" << std::endl;
    disconnectFromServer();
  } else {
    std::cerr << "Error reading from server" << std::endl;
  }
}


// void Bot::configFileSyntaxCheck(const std::string &filename)
// {
//
//     return;
// }

void Bot::translateServerResponse(const std::string &response) {

  std::string user = response.substr(1, response.find("!") - 1);
  std::string channel = response.substr(response.find(":") + 1);


  if (response.find("PING") != std::string::npos) {
    std::string pong = "PONG " + response.substr(5) + "\r\n";
    sendMessageToServer(pong);
  } else if (response.find("JOIN") != std::string::npos) {
    std::cout << "User: " << user << " joined channel: " << channel
              << std::endl;
  } else if (response.find("PRIVMSG") != std::string::npos) {
    handlePrivmsg(response);
  } else {
      if (_debug) {
        std::cout << response << std::endl;
      }
  }
}


// void Bot:: Uptime() {
//   sendMessage("PRIVMSG " + _channelName + " :Uptime: " + uptime + "\r\n");
// }
