/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:01:07 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/15 21:01:07 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include "../inc/Poll.hpp"
#include "../inc/Reminder.hpp"
#include "../inc/tools.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

class Bot {
private:
  // std::vector<Reminder> _reminders;
  // std::vector<Poll> _polls;
  // std::vector<std::string> _channels;
  int _clientFdSocket;
  int _port;

  std::string _botName;
  std::string _username;
  std::string _nickname;

  bool _debug;

  unsigned int _botId;

  std::string _channelName;
  bool _autoJoinChannel;
  std::string _serverAddress;
  std::string domainName;
  std::string _password;

  time_t _start_time;
  time_t _uptime;
  std::vector<Reminder> _reminders;
  time_t runTime;

public:
  Bot();
  Bot(const Bot &other);
  Bot &operator=(const Bot &other);
  ~Bot();

  // Getters
  std::string getBotName() const;
  std::string getIP() const;

  // Setters
  void setBotName(const std::string &name);

  // Bot-specific methods
  bool connectToServer();
  void disconnectFromServer();

  // core
  int coreLoop(int ac, char **av);
  void sendMessageToServer(const std::string &message);
  void processServerResponse();
  void joinChannel(const std::string &channelName);
  void joinChannel();
  void leaveChannel(const std::string &channelName);

  int getClientFdSocket() const;
  int getPort() const;
  void setClientFdSocket(int clientFdSocket);
  void setPort(int port);

  void setServerAddress(const std::string &serverAddress);
  std::string getServerAddress() const;
  // auth
  void registerBot();
  // command handler
  void getCommand(const std::string &line);
  void handleCommand(const std::string &line);
  void handlePrivmsg(const std::string &response);
  // Display
  void DisplayBanner();
  void DisplayWelcome();
  void DisplayHelp();
  void DisplayTime();
  void DisplayDate();
  void DisplayUptime();
  void DisplayConfig();
  void DisplayConfig(const std::string &filename);
  void DisplayBotInfo();
  // channels
  void listChannels();

  void setChannel(const std::string &channel);
  void setCurrentChannel(const std::string &channel);
  void addChannel(const std::string &channel);
  void removeChannel(const std::string &channel);
  void messageChannel(const std::string &message);
  void messageChannel(const std::string &channelName,
                      const std::string &message);
  void messageUser(const std::string &user, const std::string &message);

  void pingUser(const std::string &user);
  void pingServer();

  // Parse & config

  void parseConfigFile(const std::string &filename);
  void parseArgs(int argc, char **argv);

  void translateServerResponse(const std::string &response);

  void processCommand(const std::string &command);

  // REMINDER
  void initReminders();
  time_t getUptime();
  void initUptime();
  void addReminderChannel(const std::string &title, const std::string &message,
                          time_t reminderTime);
  void addReminderUser(const std::string &title, const std::string &message,
                       time_t reminderTime);
  void checkReminders();
};

// class BotManager {
// private:
//   Bot *_bot;
// };

#endif
