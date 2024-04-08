
# MiniTCP (C++)

Este es un mini proyecto en C++ con el objetivo de crear un mini cliente tcp.

[![AGPL License](https://img.shields.io/badge/C++-Solutions-blue.svg?style=flat&logo=c%2B%2B)](http://www.gnu.org/licenses/agpl-3.0)
[![Uruguay](https://img.shields.io/badge/country-Uruguay-green.svg)](https://en.wikipedia.org/wiki/Uruguay)
[![Version](https://img.shields.io/badge/version-2.0.1-orange.svg)](https://github.com/tu-repositorio)


![Logo](https://raw.githubusercontent.com/BAA4TS/BAA4TS.github.io/main/src/icono.png)


## Installation

Intalaccion descarga ```MiniTCP.hpp``` y despues agregala a tu proyecto 

```C++
#include "MiniTCP.hpp"
```
    
# Ejemplo de uso
```c++
#include <iostream>
#include "MiniTCP.hpp"

int main() {

    // Definición del host y puerto del servidor
    const char* HOST = "127.0.0.1";
    int PORT = 8080;

    // Creación de un objeto de la clase MiniTCP
    Mini::MIniTCP cliente;

    // Conexión al servidor
    int resultadoConexion = cliente.Connectarse_TCP_AND_DNS(HOST, PORT, 5);
    if (resultadoConexion != 0) {
        std::cout << "Error al conectar al servidor: " << resultadoConexion << std::endl;
        return 1;
    }

    // Recepción del mensaje del servidor
    char* mensajeRecibido = cliente.Recibir();
    if (mensajeRecibido == nullptr) {
        std::cout << "Error al recibir el mensaje del servidor." << std::endl;
        return 1;
    }

    // Impresión del mensaje recibido
    std::cout << "Mensaje recibido del servidor: " << mensajeRecibido << std::endl;


    return 0;
}
