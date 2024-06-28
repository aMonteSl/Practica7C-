#include "GreenHouse.h"

#include <fstream>
#include <iostream>
#include <string>

#include "AlarmSensors.h"
#include "KeyboardHardware.h"
#include "MonitoringSystem.h"
#include "ScreenHardware.h"
#include "SwitchHardware.h"
#include "UsersServer.h"

using namespace std;

GreenHouse::GreenHouse()
    : alarm_(new AlarmSensors()),

      ms_(new MonitoringSystem(new ScreenHardware(true),
                               new KeyboardHardware(true),
                               new SwitchHardware(true))),
      us_(new UsersServer()) {
  // Constructor ahora inicializa todos los atributos privados correctamente.
}

GreenHouse::~GreenHouse() {
  // Destructor ahora elimina todos los atributos privados correctamente.
  delete alarm_;
  delete ms_;
  delete us_;
}

void GreenHouse::startSystem() {
  // Mensaje de bienvenida del invernadero
  ms_->initialScreen();
}

bool GreenHouse::searchUser(std::string name, std::string password,
                            std::string nif) {
  return us_->findUserLogin(name, password, nif);
}

void GreenHouse::manageDeleteUser() {
  ms_->deleteUserScreen();
  if (searchUser(ms_->getNameSelectedUser(), ms_->getPasswordSelectedUser(),
                 ms_->getNIFSelectedUser())) {
    us_->deleteUser(ms_->getNIFSelectedUser());
  } else {
    printf("Usuario no encontrado\n");
  }
}

void GreenHouse::manageCreateUser() {
  ms_->createUserScreen();
  us_->createUser(ms_->getNameSelectedUser(), ms_->getNIFSelectedUser(),
                  ms_->getPasswordSelectedUser(),
                  ms_->getPrivilegesSelectedUser(),
                  ms_->getEmailSelectedUser());
}

void GreenHouse::manageUpdateUser() {
  ms_->updateUserScreen();
  if (searchUser(ms_->getNameSelectedUser(), ms_->getPasswordSelectedUser(),
                 ms_->getNIFSelectedUser())) {
    us_->updateUser(ms_->getEmailSelectedUser(), ms_->getNIFSelectedUser(),
                    ms_->getPasswordSelectedUser(),
                    ms_->getPrivilegesSelectedUser(),
                    ms_->getEmailSelectedUser());
  } else {
    printf("Usuario no encontrado\n");
  }
}

void GreenHouse::sleep() { system("sleep 5"); }

void GreenHouse::save() {
  us_->saveUsersToFile();
  alarm_->saveSensorsData();
}

void GreenHouse::manageAdmin() {
  bool exit = false;
  // Mostramos la ventana de admin
  do {
    // Poner unos sefgundos de espera para que se vea el mensaje
    sleep();
    ms_->mainWindowAdmin();
    switch (ms_->getSelection()) {
    case 1:
      manageCreateUser();
      // us_->saveUsersToFile();
      break;
    case 2:
      manageDeleteUser();
      // us_->saveUsersToFile();
      break;
    case 3:
      manageUpdateUser();
      // us_->saveUsersToFile();
      break;
    case 4:
      ms_->displayUsersScreen();
      us_->printUsersServer();
      break;
    case 5:
      ms_->createAlarmScreen();
      alarm_->addSensor(ms_->getIdAlarm(), ms_->getTypeAlarm());
      break;
    case 6:
      ms_->deleteAlarmScreen();
      alarm_->deleteSensor(ms_->getIdSelectedAlarm());
      break;
    case 7:
      ms_->displaySensorsScreen();
      alarm_->displayAllSensorsData();
      break;
    case 8:
      ms_->displayAlarmsScreen();
      alarm_->displayAlarmStatus();
      break;
    case 9:
      ms_->turnOnOffSystemScreen();
      alarm_->turnOnOffSystem(ms_->getSelection());
      break;
    case 10:
      us_->saveUsersToFile();
      break;
    case 11:
      ms_->saveAlarmScreen();
      alarm_->saveSensorsData();
      sleep();
      break;
    case 12:
      save();
      sleep();
      ms_->exitScreen();
      exit = true;
      break;
    default:
      ms_->displayErrorScreen();
      break;
    }
  } while (!exit);
}

void GreenHouse::manageEmployee() {
  bool exit = false;
  // Mostramos la ventana de employee
  do {
    sleep();
    ms_->mainWindowEmployee();
    switch (ms_->getSelection()) {
    case 1:
      ms_->createAlarmScreen();
      alarm_->addSensor(ms_->getIdAlarm(), ms_->getTypeAlarm());
      break;
    case 2:
      ms_->deleteAlarmScreen();
      alarm_->deleteSensor(ms_->getIdSelectedAlarm());
      break;
    case 3:
      ms_->displaySensorsScreen();
      alarm_->displayAllSensorsData();
      break;
    case 4:
      ms_->displayAlarmsScreen();
      alarm_->displayAlarmStatus();
      break;
    case 5:
      ms_->turnOnOffSystemScreen();
      alarm_->turnOnOffSystem(ms_->getSelection());
      break;
    case 6:
      ms_->saveAlarmScreen();
      alarm_->saveSensorsData();
      break;
    case 7:
      ms_->exitScreen();
      ms_->saveAlarmScreen();
      alarm_->saveSensorsData();
      exit = true;
      break;
    default:
      ms_->displayErrorScreen();
      break;
    }
  } while (!exit);
}

void GreenHouse::manageGuest() {
  bool exit = false;
  // Mostramos la ventana de guest
  do {
    sleep();
    ms_->mainWindowGuest();
    switch (ms_->getSelection()) {
    case 1:
      ms_->displaySensorsScreen();
      alarm_->displayAllSensorsData();
      break;
    case 2:
      ms_->displayAlarmsScreen();
      alarm_->displayAlarmStatus();
      break;
    case 3:
      ms_->saveAlarmScreen();
      alarm_->saveSensorsData();
      break;
    case 4:
      ms_->exitScreen();
      ms_->saveAlarmScreen();
      alarm_->saveSensorsData();
      exit = true;
      break;
    default:
      ms_->displayErrorScreen();
      break;
    }
  } while (!exit);
}

void GreenHouse::manageLogin() {

  // Cargamos los usuarios del archivo
  us_->loadUsersFromFile();
  // Cargamos los sensores del archivo
  alarm_->loadSensorsData();
  // Comprobamos si el usuario y la contraseña son correctos
  if (us_->findUserLogin(ms_->getName(), ms_->getPassword(), ms_->getNIF())) {
    printf("Usuario correcto\n");
    // ahora tengo qeu ver que tipo de usuario es
    // si es admin, employee o guest
    // si es admin
    if (us_->getPrivileges(ms_->getNIF()) == "ADMIN") {
      manageAdmin();

    } else if (us_->getPrivileges(ms_->getNIF()) == "EMPLOYEE") {
      manageEmployee();

    } else {
      manageGuest();
    }

  } else {
    printf("Usuario incorrecto\n");
    sleep();
    ms_->exitScreen();
  }
}

void GreenHouse::mainSystem() {
  // SI la seleccion en startSystem() es 1, entonces se ejecuta el loginScreen()
  // Hacemos mejor un switch para que sea más fácil de leer
  switch (ms_->getSelection()) {
  case 1:
    ms_->loginScreen();
    manageLogin();
    break;
  case 2:
    ms_->exitScreen();
    break;
  default:
    ms_->displayErrorScreen();
    break;
  }
  /* if (ms_->getSelection() == 1)
  {
      us_->loadUsersFromFile();
      ms_->loginScreen();

  } else if (ms_->getSelection() == 2)
  {
      ms_->exitScreen();
  } else {
      ms_->displayErrorScreen();
  }
  */
}