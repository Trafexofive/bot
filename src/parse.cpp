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
      _botName = "defaultBot";
      _channelName = "#BornToCode";
      _username = "joey";
      _nickname = "joeyNick";
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

void Bot::handleServerAddr(const std::string &line) {
  _domainName = line.substr(line.find("=") + 2);
  _serverAddress = resolveIP(_domainName);
  if (_serverAddress.empty()) {
    if (_debug)
      std::cerr << "Error: Unable to resolve address" << std::endl;
  }
}

void Bot::parseConfigFile(const std::string &filename) {
  std::ifstream file(filename);
  std::string line;
  while (std::getline(file, line)) {
    if (line.find("#") == 0 || line.empty())
      continue;
    if (line.find("server_address") != std::string::npos) {
      handleServerAddr(line);
    } else if (line.find("port") != std::string::npos) {
      _port = std::stoi(line.substr(line.find("=") + 2));
    } else if (line.find("password") != std::string::npos) {
      _password = line.substr(line.find("=") + 2);
    } else if (line.find("channel") != std::string::npos) {
      _channelName = line.substr(line.find("=") + 2);
    } else if (line.find("bot_name") != std::string::npos) {
      _botName = line.substr(line.find("=") + 2);
    } else if (line.find("bot_user") != std::string::npos) {
      _username = line.substr(line.find("=") + 2);
    } else if (line.find("bot_nick") != std::string::npos) {
      _nickname = line.substr(line.find("=") + 2);
    } else if (line.find("debug") != std::string::npos) {
      _debug = line.substr(line.find("=") + 2) == "true" ? true : false;
    } else if (line.find("masters") != std::string::npos) {
      _masters = loadMasters(line);
    } else if (line.find("auto_join") != std::string::npos) {
      _autoJoinChannel =
          line.substr(line.find("=") + 2) == "true" ? true : false;
    } else if (line.find("runtime") != std::string::npos) {
      _runtime = std::stoi(line.substr(line.find("=") + 2));
    } else if (line.find("runtime_bool") != std::string::npos)
      _useRuntime = line.substr(line.find("=") + 2) == "true" ? true : false;
    else {
      std::cerr << "Warning: Unknown configuration option at line: " << line
                << std::endl;
    }
  }
}

std::string Bot::loadMasters(const std::string &line) {
  if (line.find("{ ") == std::string::npos ||
      line.find(" }") == std::string::npos) {
    return "";
  }
  std::string _masters = line.substr(line.find("{") + 1, line.find("}") - 1);
  _masters = _masters.substr(1, _masters.length() - 2);
  return _masters;
}

bool Bot::isMaster(const std::string &user) {
  if (_masters.find(user) != std::string::npos) {
    return true;
  }
  return false;
}
