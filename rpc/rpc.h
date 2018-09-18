#pragma once 

#include <rpc/server.h>

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