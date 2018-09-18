#pragma once 

#include <memory>
#include <grpcpp/grpcpp.h>

namespace rpc {

typedef grpc::Status Status;

class RpcServer {
public:
    static RpcServer* GetInstance();
    
    void Run(int port);
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