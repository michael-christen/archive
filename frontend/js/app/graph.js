// Adapted from Line Chart example: http://bl.ocks.org/mbostock/3883245
define(["lib/d3.min"], function(d3) {
    // Visuals
    var margin = {top: 10, right: 10, bottom: 10, left: 10},
        width  = 600 - margin.left - margin.right,
        height = 600 - margin.top - margin.bottom;
    var center = {
        x: width/2 + margin.left,
        y: height/2 + margin.top
    };
    var radius = Math.min(width, height) / 2 - 10;
    /*
    var x = d3.scale.linear()
        .range([0, width]);
    var linePadding = 10;
    var y = d3.scale.linear()
        .range([height, 0]);
    function formatTime(d) {
        var prefix = d3.formatPrefix(d);
        return prefix.scale(d).toFixed(2) + prefix.symbol + 'S';
    }
    var xAxis = d3.svg.axis()
        .scale(x)
        .ticks(6)
        .tickFormat(formatTime)
        .innerTickSize(-height)
        .outerTickSize(0)
        .tickPadding(10)
        .orient("bottom");
    var yAxis = d3.svg.axis()
        .scale(y)
        .orient("left");
    var line = d3.svg.line()
        .x(function(d, i) { return x(i); })
        .y(function(d) { return y(d); });
    */
    // SVG Creation / update
    var svg = d3.select("#graph").append("svg")
        .attr("width", width + margin.left + margin.right)
        .attr("height", height + margin.top + margin.bottom);

    /*
    // Axes
    var xAxisGraph = svg.append("g")
        .attr("class", "x axis")
        .attr("transform", "translate(" + margin.left + "," + (margin.top + height) + ")");
    var yAxisGraph = svg.append("g")
        .attr("class", "y axis")
        .attr("transform", "translate(" + margin.left + "," + (margin.top) + ")");
    // Lines
    var lineContainer = svg.append("g")
        .attr("transform", "translate(" + margin.left + "," + margin.top + ")")
        .attr("id", "lineContainer");
    */
    // Pivot circle
    var pivotCircle = svg.append("circle")
        .attr("id", "pivot")
        .attr("cx", center.x)
        .attr("cy", center.y)
        .attr("r", 5)
        .style("stroke", "black")
        .style("fill", "white");
    // Draw line
    var line = svg.append("line")
        .attr("id", "line")
        .attr("x1", center.x)
        .attr("y1", center.y)
        .attr("x2", center.x)
        .attr("y2", center.y + radius)
        .style("stroke-width", 1)
        .style("stroke", "black");
    // Draw mass
    var mass = svg.append("circle")
        .attr("id", "mass")
        .attr("cx", center.x)
        .attr("cy", center.y + radius)
        .attr("r", 10)
        .style("fill", "steelblue");

    var update = function(theta) {
        // Use simulations frame 0 = bottom, 90 = left, 180 = top, 270 = right
        theta -= 90;
        // Change line and mass dependent on theta
        var point = {
            // Our model changes direction of +theta
            x: center.x - radius * Math.cos(theta*Math.PI/180),
            // Subtract because down is + in SVG
            y: center.y - radius * Math.sin(theta*Math.PI/180)
        };
        // Update line
        line.attr("x2", point.x)
            .attr("y2", point.y);
        // Draw new mass
        mass.attr("cx", point.x)
            .attr("cy", point.y);
        /*
            x.domain([
                    d3.min(data, function(d, i) { return i; }),
                    d3.max(data, function(d, i) { return i; })
                ]);
        y.domain([
                d3.min(data, function(d) { return d; }),
                d3.max(data, function(d) { return d; })
                ]);
        // Axis update
        xAxisGraph.call(xAxis);
        yAxisGraph.call(yAxis);
        // NOTE: Not following d3 methodology of update, enter, exit
        // Get rid of old path
        lineContainer.selectAll("path").remove();
        // Draw new path
        var myLine = lineContainer.append("path")
            .datum(data)
            .attr("class", "line")
            .attr("d", line);
        */
    };

    function splitD3Transform(elt) {
        var transformString = elt.attr("transform");
        var lParenPos = transformString.indexOf("(");
        var commaPos = transformString.indexOf(",");
        var rParenPos = transformString.indexOf(")");
        return {
            x: parseFloat(transformString.slice(lParenPos + 1, commaPos)),
            y: parseFloat(transformString.slice(commaPos + 1, rParenPos))
        };
    }

    return {
        update: update
    };
});
