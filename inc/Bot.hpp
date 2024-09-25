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

#include <string>
#include <arpa/inet.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../inc/tools.hpp"
#include <ctime>
#include "../inc/Reminder.hpp"
#include "../inc/Poll.hpp"

class Reminder {
private:
  std::string _title;
  std::string _message;
  std::string _time;

  std::string _user;
  std::string channel;
  // either user or channel
public:
  Reminder();
  Reminder(const Reminder &other);
  ~Reminder();

  Reminder(const std::string &message, const std::string &time,
           const std::string &user, const std::string &channel);

  // GETTERS & SETTERS

  std::string getMessage() const;
  std::string getTime() const;
  std::string getUser() const;
  std::string getChannel() const;

  // reminder specific methodes
  void setReminder();
  // void displayReminder(const std::string &user);
  // {
  //
  // };
  //
  // void displayReminder(const std::string &user)
  // {
  //
  // };
};

class Bot {
private:
  int _clientFdSocket;
  int _port;

  std::string _botName;
  std::string _username;
  std::string _nickname;
  bool      _debug;
  unsigned int _botId;

  // std::vector<std::string> _channels;
  std::string _channelName;
  bool _autoJoinChannel;
  std::string _serverAddress;
  std::string domainName;
  std::string _password;

  unsigned int _uptime;

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

  //core
  int   coreLoop(int ac , char **av);
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
  void messageChannel(const std::string &channelName, const std::string &message);
  void messageUser(const std::string &user, const std::string &message);

  void pingUser(const std::string &user);
  void pingServer();

  // Parse & config

  void parseConfigFile(const std::string &filename);
  void parseArgs(int argc, char **argv);

  void translateServerResponse(const std::string &response);

  void processCommand(const std::string &command);

  void Uptime();
};

// class BotManager {
// private:
//   Bot *_bot;
// };

#endif
