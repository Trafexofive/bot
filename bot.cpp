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



#include "Bot.hpp"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

Bot::Bot() : _clientFdSocket(-1), _botName(""), _ip(""), _channelName(""){}

Bot::Bot(const Bot& other) {
    *this = other;
}

Bot& Bot::operator=(const Bot& other) {
    if (this != &other) {
        _clientFdSocket = other._clientFdSocket;
        _botName = other._botName;
        _ip = other._ip;
        _channelName = other._channelName;
    }
    return *this;
}

Bot::~Bot() {
    disconnectFromServer();
}

std::string Bot::getBotName() const {
    return _botName;
}

void Bot::setBotName(const std::string& name) {
    _botName = name;
}

std::string Bot::getIP() const {
    return _ip;
}


bool Bot::connectToServer(const std::string& address, int port, const std::string& password) {
    _clientFdSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_clientFdSocket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return false;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (inet_pton(AF_INET, address.c_str(), &server.sin_addr) <= 0) {
        std::cerr << "Invalid address" << std::endl;
        close(_clientFdSocket);
        return false;
    }

    if (connect(_clientFdSocket, (struct sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        close(_clientFdSocket);
        return false;
    }

    _ip = address;

    if (!password.empty()) {
        sendMessage("PASS " + password + "\r\n");
    }

    return true;
}

void Bot::disconnectFromServer() {
    if (_clientFdSocket != -1) {
        close(_clientFdSocket);
        _clientFdSocket = -1;
    }
}

void Bot::sendMessage(const std::string& message) {
    if (_clientFdSocket != -1) {
        send(_clientFdSocket, message.c_str(), message.length(), 0);
    }
}

void Bot::processServerResponse() {
    char buffer[1024];
    int bytesRead = recv(_clientFdSocket, buffer, sizeof(buffer) - 1, 0);
    
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "Received: " << buffer << std::endl;
        
        // Here you can add logic to parse and respond to server messages
    } else if (bytesRead == 0) {
        std::cout << "Server closed the connection" << std::endl;
        disconnectFromServer();
    } else {
        std::cerr << "Error reading from server" << std::endl;
    }
}

void Bot::joinChannel(const std::string& channelName) {
    sendMessage("JOIN " + channelName + "\r\n");
}

void Bot::leaveChannel(const std::string& channelName) {
    sendMessage("PART " + channelName + "\r\n");
}

int Bot::getClientFdSocket() const {
    return _clientFdSocket;
}

void Bot::pingUser(const std::string& user) {
    sendMessage("PING " + user + "\r\n");
}

void Bot::DisplayBanner() {
    sendMessage("PRIVMSG " + _channelName + " :Welcome to the bot!\r\n");
}
