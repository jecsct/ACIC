#include <Wire.h>
#include "Slave.hpp"
#include "Server.hpp"

const int entity = 1;
void setup() {
  Slave::initialize();
  Server::initialize(entity);
}

void loop() {
  Slave::loop();
}