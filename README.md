# P7-Excep-GDB-Dox
## Autor: Adrián Montes Linares

## Introducción

El programa principal se encuentra en main.cpp donde podremos lanzar el sistema del invernadero y realizar todas las operaciones posibles. Como compilar el main.cpp y ejecutar el programa se enseñara más adelante.
De momento muestro todas las clases, una explicación breve de ellas y que SOURCES tiene que tener el MakeFile para probar cada clase

1. User.cpp = Define los métodos y atributos básicos de un usuario.
```make
SOURCES = User.cpp mainUser.cpp
```
2. UserAdmin.cpp = Clase de Usuario administrador
```make
SOURCES = User.cpp UserAdmin.cpp mainUserAdmin.cpp
```
3. UserEmployee.cpp = Clase de Usuario employee
```make
SOURCES = User.cpp UserEmployee.cpp mainUserEmployee.cpp
```
4. UserGuest.cpp = Clase de Usuario guest
```make
SOURCES = User.cpp UserGuest.cpp mainUserGuest.cpp
```
5. UserDatabase.cpp = Define los métodos y atributos básicos de una base de datos que almacena usuarios. (Maneja a cada usuario de manera individual de una base de datos)
```make
SOURCES = User.cpp UsersDatabase.cpp mainUsersDatabase.cpp UserAdmin.cpp UserEmployee.cpp UserGuest.cpp
```
6. UsersServer.cpp = Define los métodos y atributos básicos de un servidor que maneja una base de datos. (Maneja al conjunto de usuarios de una base de datos)
```make
SOURCES = User.cpp UsersDatabase.cpp mainUsersServer.cpp UsersServer.cpp UserAdmin.cpp UserEmployee.cpp UserGuest.cpp
```
7. Sensor.cpp = Define los métodos y atributos básicos de un sensor
```make
SOURCES = Sensor.cpp mainSensor.cpp
```
8. TemperatureSensor.cpp = Define los métodos y atributos de un sensor de temperatura
```make
SOURCES = Sensor.cpp TemperatureSensor.cpp mainTemperatureSensor.cpp
```
9. AirQualitySensor.cpp = Define los métodos y atributos de un sensor de aire
```make
SOURCES = Sensor.cpp AirQualitySensor.cpp mainAirQualitySensor.cpp
```
10. HydrometerSensor.cpp = Define los métodos y atributos de un hydrometro
```make
SOURCES = Sensor.cpp HydrometerSensor.cpp mainHydrometerSensor.cpp
```
11. PressureSensor.cpp = Define los métodos y atributos de un sensor de presión
```make
SOURCES = Sensor.cpp PressureSensor.cpp mainPressureSensor.cpp
```
12. LightSensor.cpp = Define los métodos y atributos de un sensor de luz
```make
SOURCES = Sensor.cpp LightSensor.cpp mainLightSensor.cpp
```
13. PhSensor.cpp = Define los métodos y atributos de un sensor de pH
```make
SOURCES = Sensor.cpp PhSensor.cpp mainPhSensor.cpp
```
14. Hardware.cpp = Define los métodos y atributos de un hardware generico (pantalla/teclado/interruptor)
```make
SOURCES = Hardware.cpp mainHardware.cpp 
```
15. ScreenHardware.cpp = Define los métodos y atributos necesarios de una pantalla
```make
SOURCES = Hardware.cpp mainScreenHardware.cpp ScreenHardware.cpp
```
16. KeyboardHardware.cpp = Define los métodos y atributos necesarios de un teclado
```make
SOURCES = Hardware.cpp mainKeyboardHardware.cpp KeyboardHardware.cpp
```
17. SwitchHardware.cpp = Define los métodos y atributos necesarios de un interruptor
```make
SOURCES = Hardware.cpp mainSwitchHardware.cpp SwitchHardware.cpp
```
18. AlarmSensors.cpp = Define los métodos y atributos necesarios para manejar todos los sensores y sus alarmas
```make
SOURCES = Sensor.cpp TemperatureSensor.cpp AirQualitySensor.cpp HydrometerSensor.cpp PressureSensor.cpp LightSensor.cpp PhSensor.cpp mainAlarmSensor.cpp AlarmSensor.cpp
```
19. MonitoringSystem.cpp = Define los métodos y atributos necesarios para manejar el sistema implementando un hardware de cada tipo
```make
SOURCES = Hardware.cpp MonitoringSystem.cpp mainMonitoringSystem.cpp KeyboardHardware.cpp ScreenHardware.cpp SwitchHardware.cpp
```
20. GreenHouse.cpp = Define los métodos y atributos necesarios para lanzar el sistema del invernadero, controlarlo, ver los sensores, usuarios y el resto de funciones según el rol que tengamos. Por defecto siempre hay tres usuarios, uno de cada tipo
* Nombre NIF Contraseña Privilegios Correo:
- admin 12345678X admin ADMIN admin@example.com
- employee 12345678Y employee EMPLOYEE employee@example.com
- guest 12345678Z guest GUEST guest@example.com

```make
SOURCES =  GreenHouse.cpp AlarmSensors.cpp UsersServer.cpp MonitoringSystem.cpp AirQualitySensor.cpp Hardware.cpp HydrometerSensor.cpp KeyboardHardware.cpp LightSensor.cpp TemperatureSensor.cpp User.cpp mainGreenHouse.cpp PhSensor.cpp PressureSensor.cpp ScreenHardware.cpp Sensor.cpp SwitchHardware.cpp UsersDatabase.cpp UserAdmin.cpp UserEmployee.cpp UserGuest.cpp
```
                                                                   
## Objetivos de la práctica
- El objetivo de la practica son tres objetivos, el primero el manejo de excepciones, el segundo el uso del depurador gdb y por último generar la documentación del sistema con Doxygen

### Manejo de excepciones
- Primero hemos creado un fichero nuevo llamado Exceptions.h, donde se han definido los distintos tipos de errores, estos pueden suceder manipulando ficheros para leer y escribir datos en ellos.
```cpp
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

/**
 * @file Exceptions.h
 * @brief This file contains the attributes and methods of the Exceptions class.
 * @author Adrián Montes Linares
 * @date 21/04/2024
 */

class FileOpenError : public std::runtime_error {
public:
  /**
   * @brief Construct a new File Open Error object
   *
   * @param filename
   */
  explicit FileOpenError(const std::string &filename)
      : std::runtime_error("Error opening file: " + filename) {}
};

class FileCloseError : public std::runtime_error {
public:
  /**
   * @brief Construct a new File Close Error object
   *
   * @param filename
   */
  explicit FileCloseError(const std::string &filename)
      : std::runtime_error("Error closing file: " + filename) {}
};

class FileReadError : public std::runtime_error {
public:
  /**
   * @brief Construct a new File Read Error object
   *
   * @param filename
   */
  explicit FileReadError(const std::string &filename)
      : std::runtime_error("Error reading file: " + filename) {}
};

class FileWriteError : public std::runtime_error {
public:
  /**
   * @brief Construct a new File Write Error object
   *
   * @param filename
   */
  explicit FileWriteError(const std::string &filename)
      : std::runtime_error("Error writing file: " + filename) {}
};

class FilePermissionError : public std::runtime_error {
public:
  /**
   * @brief Construct a new File Permission Error object
   *
   * @param filename
   */
  explicit FilePermissionError(const std::string &filename)
      : std::runtime_error("Permission denied: " + filename) {}
};

class FileNotFoundError : public std::runtime_error {
public:
  /**
   * @brief Construct a new File Not Found Error object
   *
   * @param filename
   */
  explicit FileNotFoundError(const std::string &filename)
      : std::runtime_error("File not found: " + filename) {}
};

class FileLockError : public std::runtime_error {
public:
  /**
   * @brief Construct a new File Lock Error object
   *
   * @param filename
   */
  explicit FileLockError(const std::string &filename)
      : std::runtime_error("File is locked: " + filename) {}
};

class FileCorruptError : public std::runtime_error {
public:
  /**
   * @brief Construct a new File Corrupt Error object
   *
   * @param filename
   */
  explicit FileCorruptError(const std::string &filename)
      : std::runtime_error("File is corrupt: " + filename) {}
};

#endif // EXCEPTIONS_H
```
- Y ahora gracias a tener la clase Exceptions.h, podemos implementar bloques try-catch, alguno de ellos serán simples, otros con varios catch, con relanzamiento de excepciónes gracias a throw y por último alguna excepción bad_alloc al usar new
1. Try_Catch en loadUsers
![Try_Catch en loadUsers](images/loadUsersTry_Catch.png)
2. Try_Catch en saveUsers
![Try_Catch en saveUsers](images/saveUsersTry_Catch.png)
3. Bad_Alloc en setUsers
![Bad_Alloc en setUsers](images/setUsers_badAlloc.png)

### Depurador GDB
- Gracias al depurador gdb podemos tener un mayor control en nuestro programa y realizar un seguimiento de lo que esta ocurriendo, entre las instrucciones más utiles encontramos break para pararnos en un punto en especifico de nuestro programa y print (nombre_variable) para ver el estado de la variable (útil para ver si estamos guardando en el set de Usuarios punteros y los objetos directamente).
1. Ejecutar gdb (main puede ser cambiado por el nombre del ejecutable que queremos depurar)
```bash
gdb main
```
2. Estructura de almacenamiento (set de punteros a Usuarios)
![setUsers](images/setUsers.png)
3. Atributo compartido en herencia (Sensores) (¡Importante, los sensores han cambiado su forma de almacenarse y ahora son tambien un set de punteros, pero para ver los atributos sirve esta captura antigua)
![atributosHijas](images/atributosHijas.png)
4. Bloque de repetición (print de Usuarios)
![bloqueRepeticion](images/bloqueRepeticion.png)
5. Construcción de objeto que sea instancia de clase hija/nieta
![hijaNieta](images/hijaNieta.png)

### Doxygen
- Gracias a Doxygen si nuestro programa tiene comentarios enriquezidos podemos generar una documentación en HTML y en LATEX, a continuación los pasos para generar la documentación:
1. Comentarios Enriquezidos
![comentariosDox](images/comentariosDox.png)
2. Generar fichero configuración Doxyfile
```bash
doxygen -g
```
3. Configurar el fichero doxygen (ruta donde generar los HTML y el LATEX, idioma, versión de nuestra documentación...)
4. Ejecutar Doxygen
```bash
doxygen Doxyfile
```
5. Ahora podemos ver el HTML en la carpeta de HTML generada, el fichero principal es index.html
6. Ahora con el LATEX podemos compilarlo en un pdf (refman.pdf) con:
```bash
pdflatex refman.tex 
```

## Compilar y ejecutar
### Compilar
- Con el siguiente comando se compila todos los .cpp que se encuntren en SOURCES
```bash
make
```
- Con el siguiente comando se limpia todos los .o de los .cpp que se encuetren en SOURCES
```bash
make clean
```
- Con el siguiente comando se le aplican unas normas de estilo a los .cpp y a los .h
```bash
make set_style
```
### Ejecutar
Por defecto el SOURCES tiene todo lo necesrio para compilar el programa principal **main.cpp**. Aquí están los pasos
1. Comprobar que el SOURCES es el necesario para compilar main.cpp, por defecto esta puesto el SOURCES correcto:
```make
SOURCES =  main.cpp GreenHouse.cpp AlarmSensors.cpp UsersServer.cpp MonitoringSystem.cpp AirQualitySensor.cpp Hardware.cpp HydrometerSensor.cpp KeyboardHardware.cpp LightSensor.cpp TemperatureSensor.cpp UserAdmin.cpp UserGuest.cpp UserEmployee.cpp User.cpp PhSensor.cpp PressureSensor.cpp ScreenHardware.cpp Sensor.cpp SwitchHardware.cpp UsersDatabase.cpp
```
2. Compilar con el comando del apartado anterior:
```bash
make
```
3. Ejecutar el programa, cualquier programa se ejecutara como a continación independientemente del SOURCES del MakeFile
```bash
./main
```