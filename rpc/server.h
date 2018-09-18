#pragma once 

#include <memory>
#include <grpcpp/grpcpp.h>

namespace rpc {

class RpcServer {
public:
    static RpcServer* GetInstance();
    
    void Run();
    void RegisterService(grpc::Service* service);

private:
    RpcServer();
    ~RpcServer();

private:
    grpc::ServerBuilder builder_;
    std::unique_ptr<grpc::Server> server_;

    static RpcServer* rpc_server_;
};

};