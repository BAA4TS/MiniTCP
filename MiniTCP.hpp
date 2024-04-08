#ifndef Mini_Cliente
#define Mini_cliente

#include <iostream>
#include <WinSock2.h>
#include <stdexcept>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")

namespace Mini
{
    class MIniTCP
    {
    private:
        // Declaracion de variables
        WSADATA ws;
        SOCKET SocketCliente;
        struct sockaddr_in ClientConfig;
        char Mensaje[1024];
        int bytesEnviar, bytesRecibir;

    public:
        /**
         * @brief Función para conectar con un servidor remoto.
         *
         * @param HOST Dirección IP o nombre del host al que conectar.
         * @param PORT Puerto del servidor al que conectar.
         * @param INTENTOS Número máximo de intentos de conexión.
         * @return int 0 si la conexión es exitosa, el número de intentos si falla, 1 si hay un error desconocido.
         */
        int Connectarse_TCP_AND_DNS(const char *HOST, int PORT, int INTENTOS)
        {
            int Contador = 0;
            while (Contador < INTENTOS)
            {
                try
                {
                    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
                    {
                        throw std::runtime_error(""); // Error 1
                    }

                    SocketCliente = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                    if (SocketCliente == SOCKET_ERROR)
                    {
                        throw std::runtime_error(""); // Error 2
                    }

                    struct hostent *host;
                    if ((host = gethostbyname(HOST)) == NULL)
                    {
                        throw std::runtime_error(""); // Error 3
                    }

                    ClientConfig.sin_family = AF_INET;
                    ClientConfig.sin_addr.s_addr = *((unsigned long *)host->h_addr);
                    ClientConfig.sin_port = htons(PORT);

                    if (connect(SocketCliente, reinterpret_cast<sockaddr *>(&ClientConfig), sizeof(ClientConfig)) == SOCKET_ERROR)
                    {
                        throw std::runtime_error(""); // Error 4
                    }

                    return 0; // Conexión exitosa
                }
                catch (const std::exception &e)
                {
                    Contador++;
                    if (Contador == INTENTOS)
                    {
                        return Contador; // Máximo de intentos alcanzado
                    }
                }
            }
            return 1; // Error desconocido
        }

        // Funciones para mensajes

        /**
         * @brief Envía un mensaje al servidor.
         *
         * Este método envía un mensaje al servidor a través del socket TCP establecido.
         *
         * @param Mensaje El mensaje que se va a enviar al servidor.
         *
         * @return 100 si el mensaje se envió correctamente.
         *         4 si hubo un error al enviar el mensaje.
         */
        int EnviarMensaje(const char *Mensaje)
        {
            bytesEnviar = send(SocketCliente, Mensaje, strlen(Mensaje), 0);
            if (bytesEnviar == SOCKET_ERROR)
            {
                return 4;
            }
            return 100;
        }

        /**
         * @brief Recibe un mensaje del servidor.
         *
         * Este método recibe un mensaje del servidor a través del socket TCP establecido.
         *
         * @return El mensaje recibido del servidor.
         *         Retorna un valor nulo si ocurre un error durante la recepción.
         */
        char *Recibir()
        {
            bytesRecibir = recv(SocketCliente, Mensaje, sizeof(Mensaje), 0);
            if (bytesRecibir == SOCKET_ERROR)
            {
                // Retorna un valor nulo para indicar un error durante la recepción
                return nullptr;
            }
            // Agregar el carácter nulo al final del buffer para convertirlo en una cadena válida
            Mensaje[bytesRecibir] = '\0';
            return Mensaje;
        }
    };

}

#endif