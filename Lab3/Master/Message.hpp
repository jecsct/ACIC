#pragma once

#include <Arduino.h>

enum class MessageID : int
{
  RED,
  GREEN = 1,
  OFF = 2,
  PING = 3,
  ACK = 4,
  STATUS = 5,
};

class Message
{
public:
  virtual int *send(int sender, int target);
  virtual void onReceive();
  virtual int *respond(int sender, int target);
  virtual bool receive(int *message);
  int size = 4;
  int reqSize = 5;
};

class MessageRED : public Message
{
public: // Implement Message
  int *send(int sender, int target);
  void onReceive();
  int *respond(int sender, int target);
  bool receive(int *message);
  int size = 4;
  int reqSize = 4;
};

class MessageGREEN : public Message
{
public: // Implement Message
  int *send(int sender, int target);
  void onReceive();
  int *respond(int sender, int target);
  bool receive(int *message);
  int size = 4;
  int reqSize = 4;
};

class MessageOFF : public Message
{
public: // Implement Message
  int *send(int sender, int target);
  void onReceive();
  int *respond(int sender, int target);
  bool receive(int *message);
  int size = 4;
  int reqSize = 4;
};

class MessagePING : public Message
{
public: // Implement Message
  int *send(int sender, int target);
  void onReceive();
  int *respond(int sender, int target);
  bool receive(int *message);
  int size = 4;
  int reqSize = 5;
};

class MessageSTATUS : public Message
{
public: // Implement Message
  int *send(int sender, int target);
  void onReceive();
  int *respond(int sender, int target);
  bool receive(int *message);
  int size = 5;
  int reqSize = 4;
};

class MessageACK : public Message
{
public: // Implement Message
  int *send(int sender, int target);
  void onReceive();
  int *respond(int sender, int target);
  bool receive(int *message);
  int size = 4;
  int reqSize = 4;
};