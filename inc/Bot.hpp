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
#include <vector>

class Bot {
private:
  int _clientFdSocket;
  int _port;

  std::string _botName;
  std::string _username;
  std::string _nickname;
  unsigned int _botId;

  std::vector<std::string> _channels;
  std::string _channelName;
  std::string _serverAddress;
  std::string _ip;
  std::string _password;

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
  void initBot();
  void sendMessage(const std::string &message);
  void processServerResponse();
  void joinChannel(const std::string &channelName);
  void joinChannel();
  void leaveChannel(const std::string &channelName);
  int getClientFdSocket() const;
  // auth
  void auth(const std::string &password);
  // command handler
  void handleCommand(const std::string &command);
  void handleCommand(const std::string &command, const std::string &arg);
  // Display
  void DisplayBanner();
  void DisplayWelcome();
  void DisplayHelp();
  void DisplayTime();
  void DisplayDate();
  void DisplayUptime();
  void DisplayConfig();
  // channels
  void listChannels();
  void addChannel(const std::string &channel);  

  void pingUser(const std::string &user);
    
  // Parse & config
  void parseConfigFile(const std::string &filename, const std::string &botName);
  void parseArgs(int argc, char **argv);

  void getDebugInfo();
  void processCommand(const std::string &command);
};

class BotManager {
private:
  Bot *_bot;
};

#endif
