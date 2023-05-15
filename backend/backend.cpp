#include <iostream>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef server::message_ptr message_ptr;

void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg);

int main()
{
    server echo_server;

    try {
        // Set logging settings
        echo_server.set_access_channels(websocketpp::log::alevel::all);
        echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize Asio
        echo_server.init_asio();
        // Register our message handler
        echo_server.set_message_handler(bind(&on_message, &echo_server, ::_1, ::_2));
        // Listen on port 9002
        echo_server.listen(9002);
        // Start the server accept loop
        echo_server.start_accept();
        // Start the ASIO io_service run loop
        echo_server.run();
    }
    catch (websocketpp::exception const& e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "other exception" << std::endl;
    }
}

void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
    // recive message from client
    std::cout << msg->get_payload() << std::endl;
    // send message to client
    std::string str = "Server received: " + msg->get_payload();
    s->send(hdl, str, msg->get_opcode());
}
