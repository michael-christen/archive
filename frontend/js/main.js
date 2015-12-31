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

function renderModel(model) {
    graph.update(model.theta);
}

function runSimulation(simulated_steps) {
    for(var i = 0; i < simulated_steps.length; ++i) {
        renderModel(simulated_steps[i].model);
    }
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
