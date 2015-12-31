#include "easylogging++.h"
#include "utils.h"

#include "PID_Simulator.h"
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/THttpServer.h>

#include <math.h>
#define PI 3.14159265

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

    // Setup simulation
    ::Model state = params.model;
    state.alpha = 0;
    ::Simulator_Product temp_result;
    double gravity_force = params.constants.g * params.constants.mass;
    double denominator = params.constants.mass * params.constants.radius;
    double dt = params.constants.dt;
    // Run simulation
    for(double time = 0.0; time <= params.constants.max_time; time += dt) {
        // Record the simulated step
        temp_result.time = time;
        temp_result.model = state;
        _return.push_back(temp_result);
        // Calculate the new state
        double force = 0.0;  // TODO: perform PID control
        // TODO: double check ordering of simulation
        state.theta += state.omega*dt;
        state.omega += state.alpha*dt;
        state.alpha = (force - gravity_force * sin(state.theta * PI / 180.0)) / denominator;
    }
    // Record the simulated step
    temp_result.time = params.constants.max_time;
    temp_result.model = state;
    _return.push_back(temp_result);

    LOG(DEBUG) << "Simulation ended";
  }

};

// Necessary for logging to work properly
INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv) {
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

