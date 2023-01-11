#include <Wire.h>
#include "Slave.hpp"
#include "Server.hpp"

void setup() {
  Slave::initialize();
  Server::initialize();
}

void loop() {
  Slave::loop();
}