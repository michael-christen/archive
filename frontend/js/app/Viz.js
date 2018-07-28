define(["lib/d3.min"], function(d3) {
    function Viz() {
        if(!(this instanceof Viz)) {
            throw new TypeError("Constructor can't be called as a function");
        }
        this.id = "graph";
        this.margin = {top: 10, right: 10, bottom: 10, left: 10},
        this.width  = 775 - this.margin.left - this.margin.right,
        this.height = 775 - this.margin.top - this.margin.bottom;
        this.center = {
            x: this.width/2 + this.margin.left,
            y: this.height/2 + this.margin.top
        };
        this.radius = Math.min(this.width, this.height) / 2 - 10;
        this.svg = d3.select("#graph").append("svg")
            .attr("width", this.width + this.margin.left + this.margin.right)
            .attr("height", this.height + this.margin.top + this.margin.bottom);
        // Pivot circle
        this.pivotCircle = this.svg.append("circle")
            .attr("id", "pivot")
            .attr("cx", this.center.x)
            .attr("cy", this.center.y)
            .attr("r", 5)
            .style("stroke", "black")
            .style("fill", "white");
        // Draw line
        this.line = this.svg.append("line")
            .attr("id", "line")
            .attr("x1", this.center.x)
            .attr("y1", this.center.y)
            .attr("x2", this.center.x)
            .attr("y2", this.center.y + this.radius)
            .style("stroke-width", 1)
            .style("stroke", "black");
        // Draw mass
        this.mass = this.svg.append("circle")
            .attr("id", "mass")
            .attr("cx", this.center.x)
            .attr("cy", this.center.y + this.radius)
            .attr("r", 10)
            .style("fill", "steelblue");
    }

    Viz.prototype = {
        // Point base constructor back @ original
        constructor: Viz,

        update: function(theta) {
            // Use simulations frame 0 = bottom, 90 = left, 180 = top, 270 = right
            theta -= 90;
            // Change line and mass dependent on theta
            var point = {
                // Our model changes direction of +theta
                x: this.center.x - this.radius * Math.cos(theta*Math.PI/180),
                // Subtract because down is + in SVG
                y: this.center.y - this.radius * Math.sin(theta*Math.PI/180)
            };
            // Update line
            this.line.attr("x2", point.x)
                .attr("y2", point.y);
            // Draw new mass
            this.mass.attr("cx", point.x)
                .attr("cy", point.y);
        }
    };
    return Viz;
});
