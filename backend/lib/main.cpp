#include "easylogging++.h"
#include "utils.h"
#include "simulator.h"

#include "PID_Simulator.h"
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/THttpServer.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;


class PID_SimulatorHandler : virtual public PID_SimulatorIf {
 public:
  PID_SimulatorHandler() {
    // Your initialization goes here
  }

  void simulate(std::vector< ::Simulator_Product> & _return, const  ::Simulator_Parameters& params) {
    // Your implementation goes here
    LOG(DEBUG) << "Simulation started";

    _return = Simulator().simulate(params);

    LOG(DEBUG) << "Simulation ended";
  }

};

// Necessary for logging to work properly
INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv) {
  initializeLogging(argc, argv);
  int port = 9090;
  shared_ptr<PID_SimulatorHandler> handler(new PID_SimulatorHandler());
  shared_ptr<TProcessor> processor(new PID_SimulatorProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new THttpServerTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TJSONProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

