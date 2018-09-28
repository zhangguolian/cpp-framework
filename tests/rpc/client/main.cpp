#include <iostream>
#include <memory>
#include <string>

#include <rpc/rpc.h>
#include <tests/rpc/rpc.grpc.pb.h>


class RpcTestClient : public rpc::RpcClientBase<RpcTestService, RpcTestService::Stub>   {
public:
    RpcTestClient(const std::string& rpc_url) 
                 : rpc::RpcClientBase<RpcTestService, RpcTestService::Stub>(rpc_url) {

    }
    ~RpcTestClient() {

    }

    // Assembles the client's payload, sends it and presents the response back
    // from the server.
    std::string Search(const std::string& user) {
        // Data we are sending to the server.
        RpcTestServiceRequest request;
        request.set_request("test");

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
    std::string user("world");
    std::string reply = rpc_client.Search(user);
    std::cout << "Rpc client received: " << reply << std::endl;

    return 0;
}
