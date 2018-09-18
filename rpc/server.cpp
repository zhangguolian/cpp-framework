#include <rpc/server.h>

#include <base/base.h>
#include <logs/logs.hpp>

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
    
void RpcServer::Run(int port) {
    std::string server_address = base::StringPrintf("0.0.0.0:%d", port);
    builder_.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    server_ = builder_.BuildAndStart();

    LOG_INFO("RpcServer Run, listening on %s.", server_address.c_str());

    server_->Wait();
}

void RpcServer::RegisterService(grpc::Service* service) {
    builder_.RegisterService(service);
}

}

