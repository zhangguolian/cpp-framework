#include <iostream>
#include <rpc/rpc.h>
#include <tests/rpc/rpc.grpc.pb.h>
#include <jsoncpp/json/json.h>
#include <logs/logs.hpp>

// RPC_SERVICE_METHOD(RpcTestService, Search) {
//     printf("RpcTestService Search req:%s\n", request->request().c_str());
//     response->set_result("success");
//     return rpc::Status::OK;
// }

RPC_SERVICE(RpcTestService) {
    RPC_METHOD(RpcTestService, Search);
};

RPC_SERVICE_DEFINE(RpcTestService);

RPC_METHOD_DEFINE(RpcTestService, Search) {
    printf("RpcTestService Search req:%s\n", request->request().c_str());

    Json::Value json_value;
    Json::Reader json_reader;
    if (!json_reader.parse(request->request(), json_value)) {
        LOG_ERROR("RpcTestService::Search json_reader.parse fail, req:%s.", 
                request->request().c_str());
        return rpc::Status(rpc::StatusCode::INVALID_ARGUMENT, "Invail params");  
    }

    if (!json_value["test"].isString()) {
        LOG_ERROR("RpcTestService::Search json_reader.parse fail, req:%s.", 
                request->request().c_str());
        return rpc::Status(rpc::StatusCode::INVALID_ARGUMENT, "Invail params");
    }

    printf("test:%s\n", json_value["test"].asString().c_str());

    response->set_result("success");
    return rpc::Status::OK;
}

int main() {
    START_RPC_SERVER("127.0.0.1", 50051);

    return 0;
}