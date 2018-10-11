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
#include <memory>
#include <string>

#include <rpc/rpc.h>
#include <tests/rpc/rpc.grpc.pb.h>
#include <reflect/reflect.h>
#include <base/base.h>

struct SearchRequest {
    SearchRequest() {
        // Regist reflect params
        REFLECT_REGIST(this, std::string, data);
    }
    ~SearchRequest() {
        // Unregist reflect params
        REFLECT_UNREGIST(this);
    }

    std::string data;
};

class RpcTestClient : public rpc::RpcClientBase<RpcTestService, RpcTestService::Stub>   {
public:
    RpcTestClient(const std::string& rpc_url) 
                 : rpc::RpcClientBase<RpcTestService, RpcTestService::Stub>(rpc_url) {

    }
    ~RpcTestClient() {

    }

    // Assembles the client's payload, sends it and presents the response back
    // from the server.
    std::string Search(const std::string& serach) {
        // Data we are sending to the server.
        RpcTestServiceRequest request;
        request.set_request(serach);

        // Container for the data we expect from the server.
        RpcTestServiceResponse response;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        rpc::ClientContext context;

        // The actual RPC.
        rpc::Status status = stub_->Search(&context, request, &response);

        // Act upon its status.
        if (status.ok()) {
            return response.result();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                    << std::endl;
            return "RPC failed";
        }
    }
};

int main(int argc, char** argv) {
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint (in this case,
    // localhost at port 50051). We indicate that the channel isn't authenticated
    // (use of InsecureChannelCredentials()).
    RpcTestClient rpc_client("localhost:50051");

    SearchRequest search;
    search.data = "Hello Word!";

    std::string reply = rpc_client.Search(base::JsonMarShal(search));
    std::cout << "Rpc client received: " << reply << std::endl;

    return 0;
}
