define(function() {
// View Model
function SimulatorVM(data) {
    var self = this;
    // Thrift object
    ko.mapping.fromJS(data, {}, self);
    // Additional fields
}

// Mapping
var SimulatorMapping = {
    create: function(options) {
        return new SimulatorVM(options.data);
    }
};

// Interface
return {
    SimulatorMapping: SimulatorMapping
};
});
