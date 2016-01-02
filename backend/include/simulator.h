#ifndef __SIMULATOR__H__
#define __SIMULATOR__H__

#include "easylogging++.h"
#include "PID_Simulator.h"

#include <math.h>

#define PI 3.14159265
#define D2R (PI / 180.0)
#define R2D (180.0 / PI)

class Simulator {
    public:
        std::vector< ::Simulator_Product> simulate(const  ::Simulator_Parameters& params);
        bool validate_simulation(const std::vector< ::Simulator_Product>& simulation);
};

#endif
