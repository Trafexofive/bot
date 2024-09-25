/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:35:34 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/24 19:35:34 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bot.hpp"

void Bot::parseArgs(int argc, char **argv) {
  if (argc <= 3) {
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
      std::cout
          << " -v, --version               output version information and "
             "exit";
      std::cout << " -h, --help                  display this help and exit"
                << std::endl;

      exit(0);
    } else if (arg == "-v" || arg == "--version") {
      std::cout << "Bot version 1.1" << std::endl;
      exit(0);
    } else if (arg == "-d" || arg == "--debug") {
      _debug = true;
    } else if (arg == "-D" || arg == "--default") {
      _serverAddress = "localhost";
      _port = 6667;
      _password = "";
      _botName = "MyCoolBot";
      _channelName = "#testchannel";
      _username = "MyCoolBot";
      _nickname = "MyCoolBot";
    } else if (arg == "-i" || arg == "--interactive") {
      std::cout << "Interactive mode" << std::endl;
    } else if (arg == "-C" || arg == "--config-file") {
      this->parseConfigFile(argv[2]);
    } else {
      std::cerr << "Unknown option" << std::endl;
      exit(1);
    }
  }
}

void Bot::parseConfigFile(const std::string &filename) {
  std::ifstream file(filename);
  std::string line;
  while (std::getline(file, line)) {
    if (line.find("server_address") != std::string::npos) {
      _serverAddress = line.substr(line.find("=") + 2);
      std::string _tmpaddr = _serverAddress;
      _serverAddress = resolveIP(_tmpaddr);
      if (_serverAddress.empty()) {
        std::cerr << "Error: Unable to resolve address" << std::endl;
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
    } else if (line.find("debug") != std::string::npos) {
      _debug = line.substr(line.find("=") + 2) == "true" ? true : false;
    }
  }
}
