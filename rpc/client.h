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