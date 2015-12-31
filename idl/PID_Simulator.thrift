include "types.thrift"

service PID_Simulator {
    list<types.Simulator_Product> simulate(
        1:types.Simulator_Parameters params
    ),
}
