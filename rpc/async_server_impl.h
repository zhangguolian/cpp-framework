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
#include <rpc/server.h>

namespace rpc {

class AsyncRpcServerImpl : public RpcServer {
public:
    class CallData {
    public:
        // Let's implement a tiny state machine 
        // with the following states.
        enum CallStatus { CREATE, PROCESS, FINISH };
        
        CallData() {}
        virtual ~CallData() {}

        virtual void Proceed() = 0;

    protected:
        // The current serving state.
        CallStatus status; 
        grpc::ServerContext context;
    };

    static AsyncRpcServerImpl* GetInstance();
    
    void Join();
    void Init(int thread_num);
    void Run(const std::string& host, int port) override;
    void AddInitCallData(CallData* call_data);

    grpc::ServerCompletionQueue* cq();

private:
    void HandleRpcs();

    AsyncRpcServerImpl();
    ~AsyncRpcServerImpl();

public:
    std::unique_ptr<async::Thread> thread_;
    std::unique_ptr<grpc::ServerCompletionQueue> cq_;
    std::vector<CallData*> init_call_data_list_; 

    static AsyncRpcServerImpl* rpc_server_;
};

}; // namespace rpc