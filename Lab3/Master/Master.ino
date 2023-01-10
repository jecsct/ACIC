#include "Controller.hpp"
#include "C:\Users\Joao\Desktop\Tecnico\1Ano\P2\ACIC\Git\Lab3\Server.hpp"
#include "../Slave.hpp"

void setup() {
  Controller::initialize();
  Server::initialize();
  Slave::initialize();
}

void loop() {
  Controller::loop();
  Slave::loop();

}