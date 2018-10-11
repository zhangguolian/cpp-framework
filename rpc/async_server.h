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

#pragma once 

#include <memory>
#include <async/async.h>
#include <grpcpp/grpcpp.h>

namespace rpc {

class AsyncRpcServer {
public:
    class CallData {
    public:
        CallData() {}
        virtual ~CallData() {}

        virtual void Proceed() = 0;

    protected:
        grpc::ServerContext context_;
        // Let's implement a tiny state machine with the following states.
        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus status_;  // The current serving state.
    };

    static AsyncRpcServer* GetInstance();
    
    void Join();
    void Run(const std::string& host, int port);
    void RegisterService(grpc::Service* service);

private:
    void HandleRpcs();

    AsyncRpcServer();
    ~AsyncRpcServer();

public:
    async::Thread thread_;
    grpc::ServerBuilder builder_;
    std::unique_ptr<grpc::Server> server_;
    std::unique_ptr<grpc::ServerCompletionQueue> cq_;

    static AsyncRpcServer* rpc_server_;
};

}; // namespace rpc