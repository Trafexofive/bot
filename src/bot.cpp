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
#include "../inc/tools.hpp"
#include <algorithm>

Bot::Bot()
    : _clientFdSocket(-1), _botName("bot"), _channelName(""),
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
    if (_debug) {
      std::cout << "Server closed the connection" << std::endl;
    }
    disconnectFromServer();
  } else {
    if (_debug) {
      std::cerr << "Error reading from server" << std::endl;
    }
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

  if (isCommand(response)) {
    processCommand(response);
  } else if (response.find("PING") != std::string::npos) {
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

// starts a thread that increments the uptime every second and updates _uptime
void Bot::initUptime() {
  std::thread t([this]() {
    while (true) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      _uptime++;
      checkReminders();
    }
  });
  t.detach();
}

time_t Bot::getUptime() {

  if (_debug) {
    std::cout << _uptime << std::endl;
  }
  return _uptime;
}

void Bot::addReminderChannel(const std::string &title,
                             const std::string &message, time_t reminderTime) {
  time_t startTime = getUptime();
  time_t endTime = startTime + reminderTime;
  Reminder reminder(title, _channelName, message, endTime);
  _reminders.push_back(reminder);
}

void Bot::addReminderUser(const std::string &title, const std::string &message,
                          time_t reminderTime) {
  time_t startTime = getUptime();
  time_t endTime = startTime + reminderTime;
  Reminder reminder(title, _nickname, message, endTime);
  _reminders.push_back(reminder);
}

void Bot::SendReminder(Reminder &reminder) {
  if (reminder.getChannel().empty()) {
    messageUser(reminder.getUser(), "Reminder for user: " + reminder.getUser());
    messageUser(reminder.getUser(), "Title: " + reminder.getTitle());
    messageUser(reminder.getUser(), "Message: " + reminder.getMessage());
  } else {
    messageChannel(reminder.getChannel(),
                   "Reminder for channel: " + reminder.getChannel());
    messageChannel(reminder.getChannel(), "Title: " + reminder.getTitle());
    messageChannel(reminder.getChannel(), "Message: " + reminder.getMessage());
  }
}

void Bot::checkReminders() {
  time_t currentTime = getUptime();
  for (auto &reminder : _reminders) {
    if (reminder.getTime() == currentTime) {
      SendReminder(reminder);
    }
  }
}

void Bot::DisplayUptime() {
  std::cout << "Bot" << _nickname << " has been up for " << getUptime()
            << " seconds" << std::endl;
}
