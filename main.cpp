/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:52:49 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/19 20:52:49 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>

int main() {
    Bot myBot;
    myBot.setBotName("MyCoolBot");
    std::string password = "ali";
    std::string address = "172.29.9.241";
    int port = 3344;

    if (!myBot.connectToServer(address, port, password)) {
        std::cerr << "Failed to connect to server" << std::endl;
        return 1;
    }

    myBot.sendMessage("NICK MyCoolBot\r\n");
    myBot.sendMessage("USER ali 0 * :MyCool IRC Bot\r\n");

    myBot.joinChannel("#testchannel");
    myBot.DisplayBanner();

    for (int i = 0; i < 100; ++i) {  // Run for 10 iterations (you can adjust this)
        myBot.sendMessage("ali\r\n");
        myBot.processServerResponse();
        // myBot.pingUser("MyCoolBot");
        sleep(1);  // Wait for 1 second between each check
    }

    myBot.leaveChannel("#testchannel");

    myBot.disconnectFromServer();

    return 0;
}
