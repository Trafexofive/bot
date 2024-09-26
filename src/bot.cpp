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
#include "../inc/Reminder.hpp"

Bot::Bot()
    : _clientFdSocket(-1), _port(6667), _botName(""), _username(""),
      _nickname(""), _password(""), _channelName(""), _autoJoinChannel(false),
      _serverAddress(""), _domainName(""), _uptime(0), _masters(""),
      _debug(false) {}

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

bool Bot::processServerResponse() {
  char buffer[1024];
  int bytesRead = recv(_clientFdSocket, buffer, sizeof(buffer) - 1, 0);

  if (bytesRead > 0) {
    buffer[bytesRead] = '\0';
    translateServerResponse(buffer);

  } else if (bytesRead == 0) {
    if (_debug) {
      std::cout << "Server closed the connection: exiting ..." << std::endl;
      disconnectFromServer();
      return false;
    }
  } else {
    if (_debug) {
      std::cerr << "Error reading from server: exiting ..." << std::endl;
      disconnectFromServer();
      return false;
    }
  }
  return true;
}

void Bot::translateServerResponse(const std::string &response) {

  std::string user = response.substr(1, response.find("!") - 1);
  user = user.substr(0, user.find("@"));
  std::string channel = response.substr(response.find(":") + 1);
  channel = channel.substr(0, channel.find(" "));

  if (_debug) {
    std::cout << "User: " << user << " Channel: " << channel << std::endl;
  }

  if (isCommand(response)) {
    processUserCommand(response);
  } else if (response.find("PING") != std::string::npos) {
    std::string pong = "PONG " + response.substr(5) + "\r\n";
    sendMessageToServer(pong);
  } else if (response.find("JOIN") != std::string::npos && isChannel(channel)) {
    if (_debug) {
      std::cout << "User: " << user << " joined channel: " << channel
                << std::endl;
    }
  } else if (response.find("PRIVMSG") != std::string::npos) {
    handlePrivmsg(response);
  } else {
    if (_debug) {
      std::cout << response << std::endl;
    }
  }
}
