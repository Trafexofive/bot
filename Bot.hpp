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

class Bot {
private:
    int _clientFdSocket;
    std::string _botName;
    std::string _ip;
    std::string _channelName;

public:
    Bot();
    Bot(const Bot& other);
    Bot& operator=(const Bot& other);
    ~Bot();

    // Getters
    std::string getBotName() const;
    std::string getIP() const;

    // Setters
    void setBotName(const std::string& name);

    // Bot-specific methods
    bool connectToServer(const std::string& address, int port, const std::string& password);
    void disconnectFromServer();
    void sendMessage(const std::string& message);
    void processServerResponse();
    void joinChannel(const std::string& channelName);
    void leaveChannel(const std::string& channelName);
    int getClientFdSocket() const;
    // auth
    void auth(const std::string& password);
    // command handler
    void handleCommand(const std::string& command);
    void handleCommand(const std::string& command, const std::string& arg);
    // Display
    void DisplayBanner();
    void DisplayWelcome();
    void DisplayHelp();
    void DisplayTime();
    void DisplayDate();
    void DisplayUptime();

    void pingUser(const std::string& user);


};

#endif 
