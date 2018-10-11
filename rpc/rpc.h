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
#include <rpc/client.h>

#define START_RPC_SERVER(host, port)\
    rpc::RpcServer::GetInstance()->Run(host, port);

#define RPC_SERVICE(service)\
class Rpc##service final : public service::Service

#define RPC_METHOD(service, method)\
grpc::Status method(grpc::ServerContext* context,\
                    const service##Request* request,\
                    service##Response* response) override;

#define RPC_SERVICE_DEFINE(service)\
class RpcTmp##service {\
public:\
    RpcTmp##service() {\
        rpc::RpcServer::GetInstance()->RegisterService(&service_);\
    }\
    Rpc##service service_;\
};\
RpcTmp##service g_rpc_##service;

#define RPC_METHOD_DEFINE(service, method)\
grpc::Status Rpc##service::method(grpc::ServerContext* context,\
                                  const service##Request* request,\
                                  service##Response* response)


#define RPC_SERVICE_METHOD(service, method)\
class Rpc##service##method final : public service::Service {\
    grpc::Status method(grpc::ServerContext* context,\
                        const service##Request* request,\
                        service##Response* response) override;\
};\
class RpcTmp##service##method {\
public:\
    RpcTmp##service##method() {\
        rpc::RpcServer::GetInstance()->RegisterService(&service_);\
    }\
    Rpc##service##method service_;\
};\
RpcTmp##service##method g_rpc_##service##method;\
grpc::Status Rpc##service##method::method(grpc::ServerContext* context,\
                                          const service##Request* request,\
                                          service##Response* response)
                                          