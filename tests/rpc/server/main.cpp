#include <iostream>
#include <rpc/rpc.h>
#include <tests/rpc/rpc.grpc.pb.h>

RPC_SERVICE_METHOD(RpcTestService, Search) {
    printf("RpcTestService Search:%s\n", request->request().c_str());
    return grpc::Status::OK;
}

int main() {
    rpc::RpcServer::GetInstance()->Run();

    return 0;
}