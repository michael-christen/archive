define(["lib/d3.min"], function(d3) {
    function Chart(id) {
        this.id = id;
        this.margin = {top: 10, right: 10, bottom: 30, left: 45},
        this.width  = 450 - this.margin.left - this.margin.right,
        this.height = 260 - this.margin.top - this.margin.bottom;
        this.xScale = d3.scale.linear()
            .range([0, this.width]);
        this.linePadding = 10;
        this.yScale = d3.scale.linear()
            .range([this.height, 0]);
        this.xAxis = d3.svg.axis()
            .scale(this.xScale)
            .ticks(6)
            .tickFormat(formatTime)
            .innerTickSize(-this.height)
            .outerTickSize(0)
            .tickPadding(10)
            .orient("bottom");
        this.yAxis = d3.svg.axis()
            .scale(this.yScale)
            .orient("left");
        var local = this;
        this.line = d3.svg.line()
            .x(function(d) { return local.xScale(d.time); })
            .y(function(d) {
                return local.yScale(d.model[local.id]); });

        this.svg = d3.select("#" + this.id + "_graph").append("svg")
            .attr("width", this.width + this.margin.left + this.margin.right)
            .attr("height", this.height + this.margin.top + this.margin.bottom);
        // Axes
        this.xAxisGraph = this.svg.append("g")
        .attr("class", "x axis")
        .attr("transform", "translate(" + this.margin.left + "," + (this.margin.top + this.height) + ")");
        this.yAxisGraph = this.svg.append("g")
        .attr("class", "y axis")
        .attr("transform", "translate(" + this.margin.left + "," + (this.margin.top) + ")");

        // Lines
        this.lineContainer = this.svg.append("g")
        .attr("transform", "translate(" + this.margin.left + "," + this.margin.top + ")")
        .attr("id", this.id + "_lineContainer");
    }

    // Static metric ids to identify and retrieve
    Chart.METRIC_IDS = [
        "theta",
        "omega",
        "alpha",
        "ke",
        "pe",
        "me",
        "force"
    ];

    // Static generator function
    Chart.create_all = function() {
        var results = [];
        for(var i = 0; i < Chart.METRIC_IDS.length; ++i) {
            results.push(new Chart(Chart.METRIC_IDS[i]));
        }
        return results
    }

    Chart.prototype = {
        // Point base constructor back @ original
        constructor: Chart,

        // Plot whole simulation
        plot: function(simulation_results) {
            // Update domains
            this.xScale.domain([
                    d3.min(simulation_results, function(d) { return d.time; }),
                    d3.max(simulation_results, function(d) { return d.time; })
            ]);
            var local = this;
            this.yScale.domain([
                    d3.min(simulation_results, function(d) { return d.model[local.id]; }),
                    d3.max(simulation_results, function(d) { return d.model[local.id]; })
            ]);
            // Update axis
            this.xAxisGraph.call(this.xAxis);
            this.yAxisGraph.call(this.yAxis);

            // NOTE: Not following d3 methodology of update, enter, exit
            // Get rid of old path
            this.lineContainer.selectAll("path").remove();

            // Draw new path
            this.metric_line = this.lineContainer.append("path")
                .datum(simulation_results)
                .attr("class", "line")
                .attr("d", this.line);
        },

        // Set a visual cue where the simulation currently is in the graph
        update: function(theta) {
        }
    };
    
    // Helper functions
    function formatTime(d) {
        var prefix = d3.formatPrefix(d);
        return prefix.scale(d).toFixed(2) + prefix.symbol + 'S';
    }

    return Chart;
});
