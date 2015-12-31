include "types.thrift"

service PID_Simulator {
    list<types.Simulator_Product> simulate(
        1:types.Simulator_Parameters sim_params,
        2:types.PID pid_params,  // PID parameters
        3:types.Model model  // Initial conditions
    ),
}
