#include "MonitoringSystem.h"

#include <iostream>

#include "KeyboardHardware.h"
#include "ScreenHardware.h"
#include "SwitchHardware.h"
using namespace std;

const int MAIN_MENU_OPTIONS = 2;
const int ADMIN_MENU_OPTIONS = 12;
const int EMPLOYEE_MENU_OPTIONS = 7;
const int GUEST_MENU_OPTIONS = 4;

MonitoringSystem::MonitoringSystem(ScreenHardware *screen,
                                   KeyboardHardware *keyboard,
                                   SwitchHardware *sw)
    : screen(screen), keyboard(keyboard), sw(sw) {}

MonitoringSystem::~MonitoringSystem() {
  delete screen;
  delete keyboard;
  delete sw;
}

int MonitoringSystem::getSelection() { return selection_; }

void MonitoringSystem::selectUser() {
  nameSelectedUser_ = askName();
  passwordSelectedUser_ = askPassword();
  nifSelectedUser_ = askNIF();
  privilegesSelectedUser_ = askPrivileges();
  emailSelectedUser_ = askEmail();
}

void MonitoringSystem::shortSelectUser() {
  nameSelectedUser_ = askName();
  passwordSelectedUser_ = askPassword();
  nifSelectedUser_ = askNIF();
}

void MonitoringSystem::askMainUser() {
  name_ = askName();
  password_ = askPassword();
  nif_ = askNIF();
}

std::string MonitoringSystem::getTypeAlarm() { return typeAlarm_; }

int MonitoringSystem::getIdAlarm() { return idAlarm_; }

int MonitoringSystem::getIdSelectedAlarm() { return idSelectedAlarm_; }

std::string MonitoringSystem::getName() { return name_; }

std::string MonitoringSystem::getNIF() { return nif_; }

std::string MonitoringSystem::getPassword() { return password_; }

std::string MonitoringSystem::getNameSelectedUser() {
  return nameSelectedUser_;
}

std::string MonitoringSystem::getNIFSelectedUser() { return nifSelectedUser_; }

std::string MonitoringSystem::getPasswordSelectedUser() {
  return passwordSelectedUser_;
}

std::string MonitoringSystem::getPrivilegesSelectedUser() {
  return privilegesSelectedUser_;
}

std::string MonitoringSystem::getEmailSelectedUser() {
  return emailSelectedUser_;
}

bool MonitoringSystem::inputCorrect(int input, int max) {
  bool correct = input >= 1 && input <= max;
  if (!correct) {
    cout << "Invalid input. Please enter an integer that corresponds to one of "
            "the options"
         << endl;
  }
  // Input debe de estar entre 1 y max
  return correct;
}

int MonitoringSystem::askInputInt(int max) {
  int input;

  do {
    input = keyboard->askInput();
  } while (!inputCorrect(input, max));

  return input;
}

void MonitoringSystem::initialScreen() {
  system("clear");
  int options = MAIN_MENU_OPTIONS;
  // Muestro de screen la initialWindow, luego pido con el keyboard un input
  // hasta que este entre los valores correctos
  screen->initialWindow();
  selection_ = askInputInt(options);
}

void MonitoringSystem::exitScreen() {
  // Borrar terminal y mostrar el exitWindow
  system("clear");
  screen->exitWindow();
}

std::string MonitoringSystem::askName() {
  std::cout << "(NAME) ";
  return keyboard->stringInput();
}

std::string MonitoringSystem::askPassword() {
  std::cout << "(PASSWORD) ";
  return keyboard->stringInput();
}

std::string MonitoringSystem::askNIF() {
  std::cout << "(NIF) ";
  return keyboard->stringInput();
}

std::string MonitoringSystem::askPrivileges() {
  std::cout << "(PRIVILEGES) ";
  return keyboard->stringInput();
}

std::string MonitoringSystem::askEmail() {
  std::cout << "(EMAIL) ";
  return keyboard->stringInput();
}

void MonitoringSystem::loginScreen() {
  // Muestro de screen la loginWindow, luego pido con el keyboard un input hasta
  // que este entre los valores correctos
  system("clear");
  screen->loginWindow();
  askMainUser();
  // std::cout << name_ << " " << password_ << " " << nif_ << endl;
}

void MonitoringSystem::mainWindowAdmin() {
  // Muestro de screen la mainWindowAdmin, luego pido con el keyboard un input
  // hasta que este entre los valores correctos
  system("clear");
  int options = ADMIN_MENU_OPTIONS;
  screen->mainWindowAdmin();
  selection_ = askInputInt(options);
}

void MonitoringSystem::mainWindowEmployee() {
  // Muestro de screen la mainWindowEmployee, luego pido con el keyboard un
  // input hasta que este entre los valores correctos
  system("clear");
  int options = EMPLOYEE_MENU_OPTIONS;
  screen->mainWindowEmployee();
  selection_ = askInputInt(options);
}

void MonitoringSystem::mainWindowGuest() {
  // Muestro de screen la mainWindowGuest, luego pido con el keyboard un input
  // hasta que este entre los valores correctos
  system("clear");
  int options = GUEST_MENU_OPTIONS;
  screen->mainWindowGuest();
  selection_ = askInputInt(options);
}

// Opciones del menu

void MonitoringSystem::createUserScreen() {
  // Muestro de screen la createUserWindow, luego pido con el keyboard un input
  // hasta que este entre los valores correctos
  system("clear");
  screen->createUserWindow();
  selectUser();
}

void MonitoringSystem::deleteUserScreen() {
  // Muestro de screen la deleteUserWindow, luego pido con el keyboard un input
  // hasta que este entre los valores correctos
  system("clear");
  screen->deleteUserWindow();
  shortSelectUser();
}

void MonitoringSystem::updateUserScreen() {
  // Muestro de screen la updateUserWindow, luego pido con el keyboard un input
  // hasta que este entre los valores correctos
  system("clear");
  screen->updateUserWindow();
  selectUser();
}

void MonitoringSystem::displayUsersScreen() {
  // Muestro de screen la displayUsersWindow
  system("clear");
  screen->displayUsersWindow();
  // keyboard->stringInput();
}

void MonitoringSystem::displaySensorsScreen() {
  // Muestro de screen la displaySensorsWindow
  system("clear");
  screen->displaySensorsWindow();
  // keyboard->stringInput();
}

void MonitoringSystem::displayAlarmsScreen() {
  // Muestro de screen la displayAlarmsWindow
  system("clear");
  screen->displayAlarmsWindow();
  // keyboard->stringInput();
}

void MonitoringSystem::turnOnOffSystemScreen() {
  // Muestro de screen la turnOnOffSystemWindow
  system("clear");
  int options = 2;
  screen->turnOnOffSystemWindow();
  selection_ = askInputInt(options);
}

void MonitoringSystem::displayErrorScreen() {
  // Muestro de screen la displayErrorWindow
  system("clear");
  screen->displayErrorWindow();
  keyboard->stringInput();
  exitScreen();
}

std::string MonitoringSystem::askTypeAlarm() {
  std::cout << "(TYPE ALARM) ";
  return keyboard->stringInput();
}

int MonitoringSystem::askIdAlarm() {
  std::cout << "(ID ALARM) ";
  return keyboard->askInput();
}

void MonitoringSystem::createAlarmScreen() {
  // Muestro de screen la createAlarmWindow
  system("clear");
  screen->createAlarmWindow();
  typeAlarm_ = askTypeAlarm();
  idAlarm_ = askIdAlarm();
}

void MonitoringSystem::deleteAlarmScreen() {
  // Muestro de screen la deleteAlarmWindow
  system("clear");
  screen->deleteAlarmWindow();
  idSelectedAlarm_ = askIdAlarm();
}

void MonitoringSystem::saveAlarmScreen() {
  // Muestro de screen la saveAlarmWindow
  system("clear");
  screen->saveAlarmWindow();
}