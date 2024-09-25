/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reminder.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:43:04 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/25 18:43:04 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Reminder.hpp"

// std::vector<Reminder> reminders;
// make reminder.init() and reminder.run() functions
// reminders will be relative to bot uptime

// canonical form

Reminder::Reminder()
    : _title(""), _message(""), _time(0), _user(""), _channel("") {}

Reminder::Reminder(const Reminder &other) { *this = other; }

Reminder::~Reminder() {}

Reminder &Reminder::operator=(const Reminder &other) {
  _title = other._title;
  _message = other._message;
  _time = other._time;
  _user = other._user;
  _channel = other._channel;
  return *this;
}

Reminder::Reminder(const std::string &title, const std::string &name,
                   const std::string &message, time_t time) {
  if (name[0] == '#') {
    _channel = name;
  } else {
    _user = name;
  }
  _title = title;
  _message = message;
  _time = time;
}

// getters and setters

std::string Reminder::getMessage() const { return _message; }

time_t Reminder::getTime() const { return _time; }

std::string Reminder::getUser() const { return _user; }

std::string Reminder::getChannel() const { return _channel; }

std::string Reminder::getTitle() const { return _title; }

// reminder specific methodes

