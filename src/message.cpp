/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:09:51 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/24 23:09:51 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bot.hpp"

// #################################### GETTERS AND SETTERS


// #################################### MESSAGE SPECIFIC METHODS

void Bot::messageChannel(const std::string &channelName,
                         const std::string &message) {
  sendMessageToServer("PRIVMSG " + channelName + " :" + message + "\r\n");
}

void Bot::messageChannel(const std::string &message) {
  sendMessageToServer("PRIVMSG " + _channelName + " :" + message + "\r\n");
}

void Bot::messageUser(const std::string &user, const std::string &message) {
  sendMessageToServer("PRIVMSG " + user + " :" + message + "\r\n");
}


void Bot::handlePrivmsg(const std::string &response) {
  std::string user = response.substr(1, response.find("!") - 1);
  std::string message = response.substr(response.find(":", 1) + 1);
  std::string channel = response.substr(
      response.find("#"), response.find(" :") - response.find("#"));

  // if its a channel in channelvector message display it
}

void Bot::pingUser(const std::string &user) {
  sendMessageToServer("PING " + user + "\r\n");
}
void Bot::pingServer() { sendMessageToServer("PING " + _serverAddress + "\r\n"); }

void Bot::sendMessageToServer(const std::string &message) {
  if (_clientFdSocket != -1) {
    send(_clientFdSocket, message.c_str(), message.length(), 0);
    std::cout << "Sending to server: " << message << std::endl;
  }
}
