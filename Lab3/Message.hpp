#pragma once

#include <Arduino.h>

enum class MessageID : uint8_t {
  RED = 0,
  GREEN = 1,
  OFF = 2,
  PING = 3,
  ACK = 4,
  STATUS = 5,
};

class Message
{
public:
  virtual void send() = 0;
  virtual void onReceive() = 0;
  virtual void respond() = 0;
  virtual void receive() = 0;
};


class MessageRED : public Message
{
public: // Implement Message
  void send() = 0;
  void onReceive() = 0;
  void respond() = 0;
  void receive() = 0;
};

class MessageGREEN : public Message
{
public: // Implement Message
  void send() = 0;
  void onReceive() = 0;
  void respond() = 0;
  void receive() = 0;
};

class MessageOFF : public Message
{
public: // Implement Message
  void send() = 0;
  void onReceive() = 0;
  void respond() = 0;
  void receive() = 0;
};

class MessagePING : public Message
{
public: // Implement Message
  void send() = 0;
  void onReceive() = 0;
  void respond() = 0;
  void receive() = 0;
};

class MessageSTATUS : public Message
{
public: // Implement Message
  void send() = 0;
  void onReceive() = 0;
  void respond() = 0;
  void receive() = 0;
};

class MessageACK : public Message
{
public: // Implement Message
  void send() = 0;
  void onReceive() = 0;
  void respond() = 0;
  void receive() = 0;
};