#include "socket_comm.hpp"

class socket_comm_client : public socket_comm {
    boost::asio::ip::tcp::socket socket_;
public:
    socket_comm_client(const std::string& host, int port);
    void run() override;
    ~socket_comm_client() override;
};