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

#include <rpc/server.h>
#include <rpc/server_impl.h>
#include <rpc/async_server_impl.h>
#include <rpc/client.h>

namespace rpc {

typedef grpc::Status Status;
typedef grpc::StatusCode StatusCode;
typedef grpc::ClientContext ClientContext;

};

// Start an rpc server.
//
// Param host is a string server host, like "localhost".
// Param port is a int server listen port, like 8080.
#define START_RPC_SERVER(host, port)\
    rpc::RpcServerImpl::GetInstance()->Run(host, port);

// Rpc service define.
#define RPC_SERVICE(service)\
class Rpc##service final : public service::Service

// Rpc method define.
#define RPC_METHOD(service, method)\
grpc::Status method(grpc::ServerContext* context,\
                    const service##Request* request,\
                    service##Response* response) override;

// Rpc service register.
#define RPC_SERVICE_DEFINE(service)\
class RpcTmp##service {\
public:\
    RpcTmp##service() {\
        rpc::RpcServerImpl::GetInstance()->RegisterService(&service_);\
    }\
    Rpc##service service_;\
};\
RpcTmp##service g_rpc_##service;

// Rpc method define.
#define RPC_METHOD_DEFINE(service, method)\
grpc::Status Rpc##service::method(grpc::ServerContext* context,\
                                  const service##Request* request,\
                                  service##Response* response)


#define START_ASYNC_RPC_SERVER(host, port, thread_num)\
    rpc::AsyncRpcServerImpl::GetInstance()->Init(thread_num);\
    rpc::AsyncRpcServerImpl::GetInstance()->Run(host, port);

#define JOIN_ASYNC_RPC_SERVER()\
    rpc::AsyncRpcServerImpl::GetInstance()->Join();

#define ASYNC_RPC_SERVICE_DEFINE(service)\
class AsyncRpcTmp##service {\
public:\
    AsyncRpcTmp##service() {\
        rpc::AsyncRpcServerImpl::GetInstance()->RegisterService(&service_);\
    }\
    service::AsyncService service_;\
};\
AsyncRpcTmp##service g_async_rpc_##service;

#define ASYNC_RPC_METHOD_DEFINE(service, method)\
class CallData##service##method : public rpc::AsyncRpcServerImpl::CallData {\
public:\
    CallData##service##method() : responder(&context) {}\
    void Proceed() override;\
    void Handle##method();\
private:\
    service##Request request;\
    service##Response response;\
    grpc::ServerAsyncResponseWriter<service##Response> responder;\
};\
class CallDataTmp##service##method {\
public:\
    CallDataTmp##service##method() {\
        auto call_data = new CallData##service##method();\
        rpc::AsyncRpcServerImpl::GetInstance()->AddInitCallData(call_data);\
    }\
};\
CallDataTmp##service##method call_data_tmp_##service##method;\
void CallData##service##method::Proceed() {\
    if (status == CREATE) {\
        status = PROCESS;\
        g_async_rpc_##service.service_.Request##method(&context, &request,\
                                                       &responder,\
                                                       rpc::AsyncRpcServerImpl::GetInstance()->cq(),\
                                                       rpc::AsyncRpcServerImpl::GetInstance()->cq(),\
                                                       this);\
    } else if (status == FINISH) {\
        delete this;\
    } else {\
        status = FINISH;\
        auto call_data = new CallData##service##method();\
        call_data->Proceed();\
        Handle##method();\
    }\
}\
void CallData##service##method::Handle##method()

                                          