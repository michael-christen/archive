struct Simulator_Constants {
    // Parameters that dictate how we run the simulation
    1: double dt,  // Time between recalculations of physical state
    2: double dt_pid,  // Time between pid adjustments (this should be much greater than dt)
    3: double max_time,  // Max time alloted for simulation

    4: double g  // The acceleration due to gravity (typically 9.81 m/s^2)
    5: double radius,  // Radius of the pendulum
    6: double mass,  // Mass of the point on the pendulum
}

struct Model {
    // Model physical situation
    // Rotational descriptions
    1: double theta,  // Angular position
    2: double omega,  // Angular velocity
    3: double alpha,  // Angular acceleration
    // Output of simulation
    4: optional double force,  // Force exerted on pendulum by controller
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

struct Simulator_Parameters {
    // Makes JS easier, by combining in one
    1: Simulator_Constants constants,
    2: PID pid_values,
    3: Model model,  // Initial conditions
    4: double desired_theta
}

// Default values
const Simulator_Constants DefaultConstants = {
    "dt": 0.001,
    "dt_pid": 0.03,
    "max_time": 10,

    "g": 9.81,
    "radius": 1,
    "mass": 1
}

const PID DefaultPID = {
    "p": 0,
    "i": 0,
    "d": 0
}

const Model DefaultModel = {
    "theta": 0,
    "omega": 0,
    "alpha": 0,

    "force": 0
}
