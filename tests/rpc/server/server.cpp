/*
 *
 * Copyright 2018 Guolian Zhang.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <rpc/rpc.h>
#include <tests/rpc/rpc.grpc.pb.h>
#include <logs/logs.hpp>
#include <reflect/reflect.h>
#include <base/base.h>

struct SearchRequest {
    // Define reflect params
    REFLECT_DEFINE(std::string, data);
};

// Define rpc service
RPC_SERVICE(RpcTestService) {
    // Define rpc service method
    RPC_METHOD(RpcTestService, Search);
    RPC_METHOD(RpcTestService, Search1);
};

// Register rpc service
RPC_SERVICE_DEFINE(RpcTestService);

// Define rpc service method Search
RPC_METHOD_DEFINE(RpcTestService, Search) {
    printf("RpcTestService Search req:%s\n", request->request().c_str());

    SearchRequest search;
    if (!base::JsonUnmarshal(request->request(), search)) {
        printf("JsonUnmarshal fail\n");
        return rpc::Status(rpc::StatusCode::UNKNOWN, "Invail params");
    }

    printf("data:%s\n", search.data.c_str());

    response->set_result("success");
    return rpc::Status::OK;
}

// Define rpc service method Search1
RPC_METHOD_DEFINE(RpcTestService, Search1) {
    printf("RpcTestService Search1 req:%s\n", request->request().c_str());

    SearchRequest search;
    if (!base::JsonUnmarshal(request->request(), search)) {
        printf("JsonUnmarshal fail\n");
        return rpc::Status(rpc::StatusCode::UNKNOWN, "Invail params");
    }

    printf("data:%s\n", search.data.c_str());

    response->set_result("success");
    return rpc::Status::OK;
}

int main() {
    // Start rpc server
    START_RPC_SERVER("127.0.0.1", 50051);

    return 0;
}