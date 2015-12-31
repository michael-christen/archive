requirejs.config({
    baseUrl: 'js/app',
    paths: {
        lib: '../lib',
    }
});
requirejs([
    'SimulatorKnockout',
    'graph'
],
function (SimulatorKO, graph) {
var transport = new Thrift.Transport("http://localhost:9090");
var protocol  = new Thrift.Protocol(transport);
var client    = new PID_SimulatorClient(protocol);

function getDefaultParameters() {
    var paramObj = new Simulator_Parameters();
    paramObj.constants = DefaultConstants;
    paramObj.pid_values = DefaultPID;
    paramObj.model = DefaultModel;
    paramObj.desired_theta = 180.0;
    return paramObj;
}

// A global instance of the example struct
var simParams = ko.mapping.fromJS(getDefaultParameters(), SimulatorKO.SimulatorMapping);
// Apply the binding to the DOM
ko.applyBindings(simParams, document.getElementById('simulator-div'));

// Functions that use the struct
var sim_index = 0;
var sim_step  = null;
var sim_steps = null;
var sim_frame = null;
var sim_start = null;
function renderModel(timestamp) {
    if(!sim_start) {
        sim_start = timestamp;
        sim_step = sim_steps[sim_index];
    }
    var t_diff = (timestamp - sim_start)/1000.0;
    // Find closest step.time that is below t_diff
    if(sim_index < sim_steps.length - 1) {
        for(var i = 1; i + sim_index < sim_steps.length; ++i) {
            var next_step = sim_steps[sim_index + i];
            // If have a valid step after time diff 
            if(next_step.time > t_diff) {
                sim_index += i - 1;
                sim_step = sim_steps[sim_index];
                graph.update(sim_step.model.theta);
                sim_frame = window.requestAnimationFrame(renderModel);
                break;
            }
        }
    }
}

function runSimulation(simulated_steps) {
    sim_index = 0;
    sim_steps = simulated_steps;
    sim_start = null;
    sim_frame = window.requestAnimationFrame(renderModel);
}


function simulate() {
    try {
        var result = client.simulate(ko.mapping.toJS(simParams));
        // Upate graph
        runSimulation(result);
    } catch(NetworkError) {
        console.log("<WARNING>: Network Error.");
        alert("Can't connect to the thrift server, try running it.");
        throw NetworkError;
    }
}

// Register dom with functions
$("#simulate-btn").click(simulate);

graph.update(0);
});
