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
#include <arpa/inet.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../inc/tools.hpp"

Bot::Bot() : _clientFdSocket(-1), _botName(""), _ip(""), _channelName("") {}

Bot::Bot(const Bot &other) { *this = other; }

Bot &Bot::operator=(const Bot &other) {
  if (this != &other) {
    _clientFdSocket = other._clientFdSocket;
    _botName = other._botName;
    _ip = other._ip;
    _channelName = other._channelName;
  }
  return *this;
}

Bot::~Bot() { disconnectFromServer(); }

// ################################## GETTERS AND SETTERS
int Bot::getClientFdSocket() const { return _clientFdSocket; }

std::string Bot::getBotName() const { return _botName; }

void Bot::setBotName(const std::string &name) { _botName = name; }

std::string Bot::getIP() const { return _ip; }

// ################################## CONNECTIONS

bool Bot::connectToServer() {
  _clientFdSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (_clientFdSocket < 0) {
    std::cerr << "Error creating socket" << std::endl;
    return false;
  }

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = htons(_port);
  if (inet_pton(AF_INET, _serverAddress.c_str(), &server.sin_addr) <= 0) {
    std::cerr << "Invalid address" << std::endl;
    close(_clientFdSocket);
    return false;
  }

  if (connect(_clientFdSocket, (struct sockaddr *)&server, sizeof(server)) <
      0) {
    std::cerr << "Connection failed" << std::endl;
    close(_clientFdSocket);
    return false;
  }

  return true;
}

void Bot::disconnectFromServer() {
  if (_clientFdSocket != -1) {
    close(_clientFdSocket);
    _clientFdSocket = -1;
  }
}

// ##################################
void Bot::initBot() {
  sendMessage("USER " + _username + " 0 * :" + _botName + " IRC Bot\r\n");
  sendMessage("NICK " + _nickname + "\r\n");
  if (!_channelName.empty()) {
    joinChannel(_channelName);
  } else {
  }
  if (!_password.empty()) {
    sendMessage("PASS " + _password + "\r\n");
  }
}

// ##################################

void Bot::sendMessage(const std::string &message) {
  if (_clientFdSocket != -1) {
    send(_clientFdSocket, message.c_str(), message.length(), 0);
    std::cout << "Sent: " << message << std::endl;
  }
}
void Bot::processCommand(const std::string &command) {
  if (command.find("PING") != std::string::npos) {
    std::string pong = "PONG " + command.substr(5) + "\r\n";
    sendMessage(pong);
  } else if (command.find("PRIVMSG") != std::string::npos) {
    std::string user = command.substr(1, command.find("!") - 1);
    std::string message = command.substr(command.find(":", 1) + 1);
    std::cout << "User: " << user << " Message: " << message << std::endl;
  }
}

// ################################## CORE

void Bot::processServerResponse() {
  char buffer[1024];
  int bytesRead = recv(_clientFdSocket, buffer, sizeof(buffer) - 1, 0);

  if (bytesRead > 0) {
    buffer[bytesRead] = '\0';
    std::cout << "Received: " << buffer << std::endl;

    processCommand(buffer);
  } else if (bytesRead == 0) {
    std::cout << "Server closed the connection" << std::endl;
    disconnectFromServer();
  } else {
    std::cerr << "Error reading from server" << std::endl;
  }
}

// ################################## CHANNELS
void Bot::joinChannel(const std::string &channelName) {
  sendMessage("JOIN " + channelName + "\r\n");
  _channelName = channelName;
}

void Bot::leaveChannel(const std::string &channelName) {
  sendMessage("PART " + channelName + "\r\n");
}

// ################################## QUALITY OF LIFE

void Bot::pingUser(const std::string &user) {}

void Bot::DisplayBanner() {
  sendMessage("PRIVMSG " + _channelName + " :Welcome to the bot!\r\n");
}

// ################################## PARSING & CONFIG
void Bot::parseConfigFile(const std::string &filename,
                          const std::string &botName) {
  std::ifstream file(filename);
  std::string line;
  while (std::getline(file, line)) {
    if (line.find("server_address") != std::string::npos) {
      _serverAddress = line.substr(line.find("=") + 2);
      if (_serverAddress == "localhost") {
        _serverAddress.clear();
        _serverAddress = resolveIP("localhost");
        if (_serverAddress.empty()) {
          std::cerr << "Error: Unable to resolve localhost" << std::endl;
        }
      }
    } else if (line.find("port") != std::string::npos) {
      _port = std::stoi(line.substr(line.find("=") + 2));
    } else if (line.find("password") != std::string::npos) {
      _password = line.substr(line.find("=") + 2);
    } else if (line.find("channel") != std::string::npos) {
      _channelName = line.substr(line.find("=") + 2);
    } else if (line.find("bot_name") != std::string::npos) {
      _botName = line.substr(line.find("=") + 2);
    } else if (line.find("bot_username") != std::string::npos) {
      _username = line.substr(line.find("=") + 2);
    } else if (line.find("bot_nick") != std::string::npos) {
      _nickname = line.substr(line.find("=") + 2);
    } else if (line.find("auto_join") != std::string::npos) {
      _channelName = line.substr(line.find("=") + 2);
    }
  }
}

void Bot::joinChannel() { sendMessage("JOIN " + _channelName + "\r\n"); }

void Bot::getDebugInfo() {
  std::cout << "#############  BotInfo   #####################" << std::endl;
  std::cout << "Server address: " << _serverAddress << std::endl;
  std::cout << "Port: " << _port << std::endl;
  std::cout << "Password: " << _password << std::endl;
  std::cout << "Bot name: " << _botName << std::endl;
  std::cout << "Channel name: " << _channelName << std::endl;
  std::cout << "##############################################" << std::endl;
}

void Bot::parseArgs(int argc, char **argv) {
  if (argc == 2) {
    std::string arg = argv[1];
    if (arg == "-h" || arg == "--help") {
      std::cout << "tldr : ./bot start" << std::endl;
      std::cout << "Usage: bot [OPTION...]" << std::endl;
      std::cout
          << " -C, --config-file=FILE     use this user configuration file"
          << std::endl;
      std::cout << " -d, --debug                 emit debugging messages"
                << std::endl;
      std::cout << " -D, --default               reset all options to their "
                   "default values"
                << std::endl;

      exit(0);
    } else if (arg == "-v" || arg == "--version") {
      std::cout << "Bot version 1.0" << std::endl;
      exit(0);
    } else if (arg == "-d" || arg == "--debug") {
      getDebugInfo();
    }
  }
}
