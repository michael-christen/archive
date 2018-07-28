#include "easylogging++.h"
#include "utils.h"
#include "simulator.h"

#include "PID_Simulator.h"
#include "types_constants.h"

bool test_normal() {
    // Test without PID
    ::Simulator_Parameters params;
    ::typesConstants c;
    params.model = c.DefaultModel;
    params.constants = c.DefaultConstants;
    Simulator s;
    return s.validate_simulation(s.simulate(params));
}

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv) {
    initializeLogging(argc, argv);
    LOG(DEBUG) << "Starting test";
    if(! test_normal()) {
        LOG(DEBUG) << "Test failed";
        return 1;
    } else {
        LOG(DEBUG) << "Normal Test passed";
    }
    return 0;
}
