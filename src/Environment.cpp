/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Environment.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:46:37 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/10/03 10:46:37 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/env.hpp"
#include <unistd.h>

void Env::getSysUsername() {
  char *username = getlogin();
  if (username == NULL) {
    _username = "unknown";
  }
}

Env::Env() {
  _domainName = "localhost";
  _port = 6667;
  _clientFdSocket = 0;
  getSysUsername();
  _botName = "botname";
  _nickname = "botnick";
}


// class implementation

void Env::handleServerAddr(const std::string &line) {
  _serverAddress = line.substr(line.find(":") + 1);
}

void Env::handlePort(const std::string &line) {
  _port = std::stoi(line.substr(line.find(":") + 1));
}

void Env::handleBotName(const std::string &line) {
  _botName = line.substr(line.find(":") + 1);
}

// getters and setters

std::string Env::getServerAddress() const { return _serverAddress; }

void Env::setServerAddress(const std::string &serverAddress) {
  _serverAddress = serverAddress;
}

std::string Env::getDomainName() const { return _domainName; }

void Env::setDomainName(const std::string &domainName) {
  _domainName = domainName;
}

int Env::getPort() const { return _port; }

void Env::setPort(int port) { _port = port; }

int Env::getClientFdSocket() const { return _clientFdSocket; }

void Env::setClientFdSocket(int clientFdSocket) {
  _clientFdSocket = clientFdSocket;
}

std::string Env::getUsername() const { return _username; }

void Env::setUsername(const std::string &username) { _username = username; }

std::string Env::getBotName() const { return _botName; }

void Env::setBotName(const std::string &botName) { _botName = botName; }

std::string Env::getNickname() const { return _nickname; }

void Env::setNickname(const std::string &nickname) { _nickname = nickname; }

std::string Env::getPassword() const { return _password; }

void Env::setPassword(const std::string &password) { _password = password; }

std::string Env::getChannelName() const { return _channelName; }

void Env::setChannelName(const std::string &channelName) {
  _channelName = channelName;
}

bool Env::isAutoJoinChannel() const { return _autoJoinChannel; }

void Env::setAutoJoinChannel(bool autoJoinChannel) {
  _autoJoinChannel = autoJoinChannel;
}

std::vector<std::string> Env::getChannels() const { return _channels; }

bool Env::isDebug() const { return _debug; }

void Env::setDebug(bool debug) { _debug = debug; }

bool Env::isUseRuntime() const { return _useRuntime; }

void Env::setUseRuntime(bool useRuntime) { _useRuntime = useRuntime; }


void Env::addChannel(const std::string &channel) { _channels.push_back(channel); }

void    Env::removeChannel(const std::string &channel) {
    _channels.erase(std::remove(_channels.begin(), _channels.end(), channel), _channels.end());
}
