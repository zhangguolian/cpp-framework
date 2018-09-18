#include <iostream>
#include <rpc/rpc.h>
#include <tests/rpc/rpc.grpc.pb.h>

RPC_SERVICE_METHOD(RpcTestService, Search) {
    printf("RpcTestService Search req:%s\n", request->request().c_str());
    response->set_result("success");
    return grpc::Status::OK;
}

int main() {
    START_RPC_SERVER(50051);

    return 0;
}