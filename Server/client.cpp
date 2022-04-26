#include <iostream>
#include "inc/olc_network.h"
#include "inc/common.h"
#include "dest/addressbook.pb.h"
#include <chrono>
#include <thread>
#include <sstream>
#include <ctime>
#include <memory>
#include <iomanip>
#include "../Serialization/proto/GameState.pb.h"
// #include "../Entity/Map/Box.h"

class GameClient : public olc::net::client_interface<GameMessage> {
};

std::string time_in_HH_MM_SS_MMM()
{
    using namespace std::chrono;

    // get current time
    auto now = system_clock::now();

    // get number of milliseconds for the current second
    // (remainder after division into seconds)
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // convert to std::time_t in order to convert to std::tm (broken time)
    auto timer = system_clock::to_time_t(now);

    // convert to broken time
    std::tm bt = *std::localtime(&timer);

    std::ostringstream oss;

    oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

int main() {
    std::cout << "Compiled!" << '\n';
    GameClient client;
    std::string str;
    if (client.Connect("127.0.0.1", 60000)) {
        std::thread([&]{
            while (client.IsConnected()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                while (!client.Incoming().empty()) {
                    auto msg = client.Incoming().pop_front().msg;
                    if (msg.header.id == GameMessage::NEW_GAME_STATE) {
                        // std::vector<std::vector<Box>> boxes;
                        char str[25000];
                        msg >> str;
                        serialized::GameState gs;
                        // boxes.resize(gs.map().rowsnumber(), std::vector<Box>(gs.map().columnsnumber()));
                        gs.ParseFromArray(str, 10000);
                        std::cout << "New game state: " << gs.map().rowsnumber() << ", time: " << time_in_HH_MM_SS_MMM() << "\n";
                        // for (int i = 0; i < gs.map().rowsnumber(); i++) {
                        //     auto mapRow = gs.map().rows().at(i);
                        //     for (int j = 0; j < gs.map().columnsnumber(); j++) {
                                // boxes[i][j] = Box()
                                // std::cout << mapRow.boxes().at(j).x() << " ";
                            // }
                            // std::cout << '\n';
                        // }
                    }
                    if (msg.header.id == GameMessage::SERVER_STOP) {
                        client.Disconnect();
                    }
                }
            }
        }).detach();
        // while (std::getline(std::cin, str)) {
        //     olc::net::message<GameMessage> msg;
        //     msg.header.id = GameMessage::ON_KEY_PRESSED;
        //     msg << str[0];
        //     client.Send(msg);
        // }
    }
    return 0;
}