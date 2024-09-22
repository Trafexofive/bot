/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:58:49 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/22 18:58:49 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/tools.hpp"

std::string resolveIP(const std::string& hostname) {
    struct hostent* host_info = gethostbyname(hostname.c_str());
    if (host_info == NULL) {
        return "";
    }
    return inet_ntoa(*(struct in_addr*)host_info->h_addr_list[0]);
}
