#define START_ASYNC_RPC_SERVER(host, port)\
    rpc::AsyncRpcServer::GetInstance()->Run(host, port);

#define ASYNC_RPC_SERVICE_DEFINE(service)\
class AsyncRpcTmp##service {\
public:\
    AsyncRpcTmp##service() {\
        rpc::AsyncRpcServer::GetInstance()->RegisterService(&service_);\
    }\
    service::AsyncService service_;\
};\
AsyncRpcTmp##service g_async_rpc_##service;

#define ASYNC_RPC_METHOD_DEFINE(service, method)\
class CallData##service##method : public rpc::AsyncRpcServer::CallData {\
public:\
    void Proceed() override;\
    void Handle##method();\
private:\
    service##Request request_;\
    service##Response response_;\
    grpc::ServerAsyncResponseWriter<service##Response> responder_;\
};\
void CallData##service##method::Proceed() {\
    if (status_ == CREATE) {\
        status_ = PROCESS;\
        g_async_rpc_##service.service_->Request##method(&contenx_, &request_,\
                                                        &responder_,\
                                                        rpc::AsyncRpcServer::GetInstance()->cq_.get(),\
                                                        rpc::AsyncRpcServer::GetInstance()->cq_.get(),\
                                                        this);\
    } else if (status_ == FINISH) {\
        delete this;\
    } else {\
        status_ = FINISH;\
        new CallData##service##method(g_async_rpc_##service.service_,\
                                      rpc::AsyncRpcServer::GetInstance()->cq_.get());\
        Handle##method();\
    }\
}\
void CallData##service##method::Handle##method()


class AsyncRpcServer {
public:
    class CallData {
    public:
        CallData() {
            //////////////////////////
            //Proceed();
        }
        virtual ~CallData();

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

AsyncRpcServer* AsyncRpcServer::rpc_server_ = NULL;

AsyncRpcServer::AsyncRpcServer() {

}
AsyncRpcServer::~AsyncRpcServer() {

}

AsyncRpcServer* AsyncRpcServer::GetInstance() {
    if (rpc_server_ == NULL) {
        rpc_server_ = new AsyncRpcServer();
    }

    return rpc_server_;
}
    
void AsyncRpcServer::Join() {
    thread_.Join();
}

void AsyncRpcServer::Run(const std::string& host, int port) {
    std::string server_address = base::StringPrintf("%s:%d", host.c_str(), port);
    builder_.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    cq_ = builder_.AddCompletionQueue();
    server_ = builder_.BuildAndStart();

    LOG_INFO("AsyncRpcServer Run, listening on %s.", server_address.c_str());

    thread_.PostTask(boost::bind(&AsyncRpcServer::HandleRpcs, this));
}

void AsyncRpcServer::RegisterService(grpc::Service* service) {
    builder_.RegisterService(service);
}

void AsyncRpcServer::HandleRpcs() {
    void* tag;  // uniquely identifies a request.
    bool ok;
    while (true) {
        // Block waiting to read the next event from the completion queue. The
        // event is uniquely identified by its tag, which in this case is the
        // memory address of a CallData instance.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or cq_ is shutting down.
        GPR_ASSERT(cq_->Next(&tag, &ok));
        GPR_ASSERT(ok);
        static_cast<CallData*>(tag)->Proceed();
    }
}

