struct Simulator_Parameters {
    // Parameters that dictate how we run the simulation
    1: double dt,  // Time between recalculations of physical state
    2: double dt_pid,  // Time between pid adjustments (this should be much greater than dt)

    3: double g  // The acceleration due to gravity (typically 9.81 m/s^2)
}

struct Model {
    // Model physical situation
    // Rotational descriptions
    1: double theta,  // Angular position
    2: double omega,  // Angular velocity
    3: double alpha,  // Angular acceleration
    // Instance descriptions
    4: double radius,  // Radius of the pendulum
    5: double mass,  // Mass of the point on the pendulum
    // Output of simulation
    6: optional double force,  // Force exerted on pendulum by controller
}

struct PID {
    // PID values
    1: double p,
    2: double i,
    3: double d
}

struct Simulator_Product {
    // Returned by simulate call
    1: double time,
    2: Model model
}
