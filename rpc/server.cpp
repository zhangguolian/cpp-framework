#include <rpc/server.h>

namespace rpc {

RpcServer* RpcServer::rpc_server_ = NULL;

RpcServer::RpcServer() {

}
RpcServer::~RpcServer() {

}

RpcServer* RpcServer::GetInstance() {
    if (rpc_server_ == NULL) {
        rpc_server_ = new RpcServer();
    }

    return rpc_server_;
}
    
void RpcServer::Run() {
    std::string server_address("0.0.0.0:50051");
    builder_.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    server_ = builder_.BuildAndStart();
    server_->Wait();
}

void RpcServer::RegisterService(grpc::Service* service) {
    builder_.RegisterService(service);
}

}

