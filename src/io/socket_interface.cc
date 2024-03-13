#include "socket_interface.hpp"

#include <chrono>
#include <thread>

namespace Io
{
    void Server_socket_interface::task() {
        while (true) {
            memset(buffer, 0, sizeof(buffer));

            int n = recvfrom(sockfd, buffer, 256, MSG_WAITALL, (sockaddr *)&cli_addr, &cli_addr_len);
            if (n > 0) {
                // LOG_OK("%d bytes from client: %s\n", n, buffer);
            }
            uint8_t header = buffer[0];

            // TODO: send "real" info back to vision ros socket
            n = sendto(
                sockfd,
                (const char *)"Server got your message",
                strlen("Server got your message"),
                MSG_CONFIRM,
                (const struct sockaddr *)&cli_addr,
                cli_addr_len);
            if (n > 0) {
                // LOG_OK("%d bytes send to client: %s\n", n, buffer);
            }

            switch (header) {
                case 0xEA: unpack(); break;
                case 0x5A: break;  // TODO:
                case 0x6A: break;
                default:;
            }
        }
    }

    inline void Server_socket_interface::unpack() {
        fp32 yaw = p_robot_set->ins_yaw;
        fp32 pitch = p_robot_set->ins_pitch;
        fp32 roll = p_robot_set->ins_roll;

        for (size_t i = 0; i < sizeof(Robot::Robot_set); i++) {
            *((uint8_t *)p_robot_set.get() + i) = buffer[i];
        }

        p_robot_set->ins_yaw = yaw;
        p_robot_set->ins_pitch = pitch;
        p_robot_set->ins_roll = roll;
        p_robot_set->mode = Types::ROBOT_MODE::ROBOT_NOT_FOLLOW;
    }

    void Server_socket_interface::set_callback(const Server_socket_interface::callbackType &fun) {
        callback_fun = fun;
    }

    Server_socket_interface::Server_socket_interface(std::shared_ptr<Robot::Robot_set> robot_set)
        : port_num(51718),
          p_robot_set(robot_set) {
        // NOTE: read this https://www.linuxhowtos.org/C_C++/socket.htm
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) {
            LOG_ERR("can't open socket\n");
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port_num);

        if (bind(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            LOG_ERR("can't bind socket fd with port number");
        }
        cli_addr_len = sizeof(cli_addr);
    }

    Server_socket_interface::~Server_socket_interface() {
        close(sockfd);
    }
}  // namespace Io
