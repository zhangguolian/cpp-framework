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

// Register rpc service
ASYNC_RPC_SERVICE_DEFINE(RpcTestService);

// Define rpc service method Search
ASYNC_RPC_METHOD_DEFINE(RpcTestService, Search) {
    printf("RpcTestService Search req:%s\n", request.request().c_str());
    if (request.request() == "") {
        return;
    }

    SearchRequest search;
    if (!base::JsonUnmarshal(request.request(), search)) {
        printf("JsonUnmarshal fail\n");
        responder.Finish(response, rpc::Status(rpc::StatusCode::UNKNOWN, "Invail params"), this);
        return ;
    }

    printf("data:%s\n", search.data.c_str());

    response.set_result("success");
    responder.Finish(response, rpc::Status::OK, this);

    return;
}

// Define rpc service method Search1
ASYNC_RPC_METHOD_DEFINE(RpcTestService, Search1) {
    printf("RpcTestService Search1 req:%s\n", request.request().c_str());
    if (request.request() == "") {
        return;
    }

    SearchRequest search;
    if (!base::JsonUnmarshal(request.request(), search)) {
        printf("JsonUnmarshal fail\n");
        responder.Finish(response, rpc::Status(rpc::StatusCode::UNKNOWN, "Invail params"), this);
        return ;
    }

    printf("data:%s\n", search.data.c_str());

    response.set_result("success");
    responder.Finish(response, rpc::Status::OK, this);

    return;
}

int main() {
    // Start rpc server
    START_ASYNC_RPC_SERVER("127.0.0.1", 50051, 8);
    
    // Wait async server thread
    JOIN_ASYNC_RPC_SERVER();
    
    return 0;
}