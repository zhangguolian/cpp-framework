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
    
void RpcServer::Run(const std::string& host, int port) {
    std::string server_address = base::StringPrintf("%s:%d", host.c_str(), port);
    builder_.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    server_ = builder_.BuildAndStart();

    LOG_INFO("RpcServer Run, listening on %s.", server_address.c_str());

    server_->Wait();
}

void RpcServer::RegisterService(grpc::Service* service) {
    builder_.RegisterService(service);
}

} // namespace rpc

