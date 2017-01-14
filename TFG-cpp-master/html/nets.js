currentFlight = -1;
currentColor = 0;


$(document).ready(function () {
    table = document.getElementById("legend");
    var dataWaypoints = readTextFile("http://127.0.0.1/waypoints.txt");
    var nodes = new vis.DataSet(dataWaypoints);
    var dataFlights = readTextFile("http://127.0.0.1/flights.txt");
    var edges = new vis.DataSet(dataFlights);

    // create a network
    var container = document.getElementById('mynetwork');
    var data = {
        nodes: nodes
        , edges: edges
    };
    console.log(data);
    var options = {
        nodes: {
            font: {
                size: 11,
                color: '#000000'
            },
            borderWidth: 2
        },
        edges: {
            width: 2
        }
    };
    var network = new vis.Network(container, data, options);
    
    
    network.on("click", function (params) {
        params.event = "[original event]";
        document.getElementById('eventSpan').innerHTML = '<h2>Click event:</h2>' + JSON.stringify(params, null, 4);
    });
    network.on("doubleClick", function (params) {
        params.event = "[original event]";
        document.getElementById('eventSpan').innerHTML = '<h2>doubleClick event:</h2>' + JSON.stringify(params, null, 4);
    });
});

function readTextFile(file) {
    var data;
    var rawFile = new XMLHttpRequest();
    rawFile.open("GET", file, false);
    rawFile.onreadystatechange = function () {
        if (rawFile.readyState === 4) {
            if (rawFile.status === 200 || rawFile.status == 0) {
                var allText = rawFile.responseText;
                if (file.includes("waypoints")) {
                    data = parseWaypoints(allText);
                } else {
                    data = parseFlights(allText);
                }
            }
        }
    }
    rawFile.send(null);
    return data;
}

function parseWaypoints(text) {
    var result = Array();
    var split = text.split("\n");
    split.forEach(function (entry) {
        lineSplitted = entry.split(" ");
        var newWaypoint = {
            id: lineSplitted[0],
            label: "Waypoint " + lineSplitted[1],
            group: lineSplitted[3]
        };
        if (lineSplitted[2] == 1) {
            newWaypoint.color = "green";
        }
        result.push(newWaypoint);
    });
    return result;
}

function parseFlights(text) {
    var result = Array();
    var split = text.split("\n");
    split.forEach(function (entry) {
        lineSplitted = entry.split(" ");
        if (lineSplitted[0] != currentFlight) {
            currentColor = getRandomColor();
            currentFlight = lineSplitted[0];
            fillTableData(lineSplitted[0], currentColor);
        }
        var newFlight = {
            from: lineSplitted[1],
            to: lineSplitted[3],
            color: {color: currentColor},
            idFlight: lineSplitted[0],
            arrows: 'to',
            label: lineSplitted[5],
            font: {align: 'middle'}
        };
        result.push(newFlight);
    });
    return result;
}

function getRandomColor() {
    var rgb = [];
    for (var i = 0; i < 3; i++)
        rgb.push(Math.floor(Math.random() * 255));
    return 'rgb(' + rgb.join(',') + ')';
}

function fillTableData(flightId, color) {
    var row = table.insertRow(table.rows.length);
    var cell1 = row.insertCell(0);
    var cell2 = row.insertCell(1);
    cell1.innerHTML = "<p>Flight " + flightId + "<p>";
    cell2.innerHTML = '<p style="color: ' + color + '">color</p>';


}