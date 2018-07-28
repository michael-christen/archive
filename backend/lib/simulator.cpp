#include "simulator.h"

std::vector< ::Simulator_Product> Simulator::simulate(const  ::Simulator_Parameters& params) {
    std::vector< ::Simulator_Product> _return;

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
    return _return;
}

bool Simulator::validate_simulation(const std::vector< ::Simulator_Product>& simulation) {
    return true;
}
