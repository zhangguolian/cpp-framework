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

#include <rpc/async_server_impl.h>

#include <base/base.h>
#include <logs/logs.hpp>

namespace rpc {

AsyncRpcServerImpl* AsyncRpcServerImpl::rpc_server_ = NULL;

AsyncRpcServerImpl::AsyncRpcServerImpl() {

}
AsyncRpcServerImpl::~AsyncRpcServerImpl() {
    cq_->Shutdown();
}

AsyncRpcServerImpl* AsyncRpcServerImpl::GetInstance() {
    if (NULL == rpc_server_) {
        rpc_server_ = new AsyncRpcServerImpl();
    }

    return rpc_server_;
}
    
void AsyncRpcServerImpl::Join() {
    if (thread_.get() != NULL) {
        thread_->Join();
    }
}

void AsyncRpcServerImpl::Init(int thread_num) {
    if (thread_.get() == NULL) {
        thread_.reset(new async::Thread(thread_num));
    }
}

void AsyncRpcServerImpl::Run(const std::string& host, int port) {
    cq_ = builder_.AddCompletionQueue();

    RpcServer::Run(host, port);

    for (size_t i = 0; i < init_call_data_list_.size(); i++) {
        init_call_data_list_[i]->Proceed();
    }
    init_call_data_list_.clear();

    thread_->PostTask(boost::bind(&AsyncRpcServerImpl::HandleRpcs, this));
}

void AsyncRpcServerImpl::AddInitCallData(CallData* call_data) {
    init_call_data_list_.push_back(call_data);
}

grpc::ServerCompletionQueue* AsyncRpcServerImpl::cq() {
    return cq_.get();
}

void AsyncRpcServerImpl::HandleRpcs() {
    while (true) {
        // Block waiting to read the next event from the completion queue. The
        // event is uniquely identified by its tag, which in this case is the
        // memory address of a CallData instance.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or cq_ is shutting down.
        bool ok = false;
        void* tag = NULL;
        cq_->Next(&tag, &ok);
        if (!ok || NULL == tag) {
            continue;
        }
        
        static_cast<CallData*>(tag)->Proceed();
    }
}

} // namespace rpc

