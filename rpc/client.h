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
#include <grpcpp/grpcpp.h>

namespace rpc {

template<class T1, class T2>
class RpcClientBase {
public:
    RpcClientBase(const std::string& rpc_url) {
        std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(
        rpc_url, grpc::InsecureChannelCredentials());
        stub_ = T1::NewStub(channel);
    }
    virtual ~RpcClientBase() {

    }

protected:
    std::unique_ptr<T2> stub_;
};

};