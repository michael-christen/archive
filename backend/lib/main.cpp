#include "easylogging++.h"
#include "utils.h"

#include "PID_Simulator.h"
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/THttpServer.h>

#include <math.h>
#define PI 3.14159265
#define D2R (PI / 180.0)
#define R2D (180.0 / PI)

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
    double moment_inertia = denominator * params.constants.radius;
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
        state.alpha = (force - gravity_force * sin(state.theta * D2R)) / denominator;
        state.omega += state.alpha*dt;
        state.theta += state.omega*dt;
        // Metrics
        double kinetic_energy = 0.5 * moment_inertia * state.omega * state.omega * D2R * D2R;
        double height = params.constants.radius * (1 + sin((state.theta - 90) * D2R));
        double potential_energy = gravity_force * height;
        CLOG(DEBUG, "main") << state.omega << '\t' << state.theta - 90 << '\t' << kinetic_energy << '\t' << potential_energy << '\t' << kinetic_energy + potential_energy;
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

