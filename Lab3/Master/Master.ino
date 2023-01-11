#include "Controller.hpp"
#include "Server.hpp"
#include "Slave.hpp"

//Slave adresses (roundabout entries) 
const int slave_addresses[] = {0/*, 1, 2, 3*/};
const int num_entries = 1;

void setup() {
  Serial.begin(9600);
  Controller::initialize(slave_addresses, num_entries);
  Server::initialize();
  Slave::initialize();
}

void loop() {
  Controller::loop();
  Slave::loop();
}