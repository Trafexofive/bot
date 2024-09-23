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

#include "inc/Bot.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>

int main(int ac, char **av) {
    Bot myBot;
    myBot.setBotName("ali");
    myBot.parseConfigFile("config.txt", myBot.getBotName());
    myBot.parseArgs(ac, av);


    if (!myBot.connectToServer()) {
        std::cerr << "Failed to connect to server" << std::endl;
        return 1;
    }
    myBot.initBot();
    // myBot.joinChannel();

    myBot.DisplayBanner();

    for (int i = 0; i < 100; ++i) {
        myBot.processServerResponse();
        // myBot.pingUser("MyCoolBot");
        sleep(1);
    }

    myBot.leaveChannel("#testchannel");

    myBot.disconnectFromServer();

    return 0;
}
