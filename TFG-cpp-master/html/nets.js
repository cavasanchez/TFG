$(document).ready(function () {
    var dataWaypoints = readTextFile("http://127.0.0.1/waypoints.txt");
    console.log(dataWaypoints);
    var nodes = new vis.DataSet(dataWaypoints);
    var dataFlights = readTextFile("http://127.0.0.1/flights.txt");
    var edges = new vis.DataSet(dataFlights);
    // create an array with nodes
    //    var nodes = new vis.DataSet([
    //        {
    //            id: 1
    //            , label: 'Node 1'
    //        }
    //        , {
    //            id: 2
    //            , label: 'Node 2'
    //        }
    //        , {
    //            id: 3
    //            , label: 'Node 3'
    //        }
    //        , {
    //            id: 4
    //            , label: 'Node 4'
    //        }
    //        , {
    //            id: 5
    //            , label: 'Node 5'
    //        }
    //  ]);
    // create an array with edges
    // var edges = new vis.DataSet([
    /* {
     from: 1
     , to: 3
 }, {
     from: 1
     , to: 2
 }, {
     from: 2
     , to: 4
 }, {
     from: 2
     , to: 5
 }*/
    //]);
    // create a network
    var container = document.getElementById('mynetwork');
    var data = {
        nodes: nodes
        , edges: edges
    };
    console.log(data);
    var options = {};
    var network = new vis.Network(container, data, options);
});

function readTextFile(file) {
    var data;
    var rawFile = new XMLHttpRequest();
    rawFile.open("GET", file, false);
    console.log(rawFile);
    rawFile.onreadystatechange = function () {
        if (rawFile.readyState === 4) {
            if (rawFile.status === 200 || rawFile.status == 0) {
                var allText = rawFile.responseText;
                if (file.includes("waypoints")) {
                    data = parseWaypoints(allText);
                }
                else {
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
    console.log(text);
    var split = text.split("\n");
    console.log(split);
    split.forEach(function (entry) {
        lineSplitted = entry.split(" ");
        var newWaypoint = {
            id: lineSplitted[0]
            , label: "Sector " + lineSplitted[1]
        }
        result.push(newWaypoint);
    });
    console.log(result);
    return result
}

function parseFlights(text) {
    var result = Array();
    console.log(text);
    var split = text.split("\n");
    console.log(split);
    split.forEach(function (entry) {
        lineSplitted = entry.split(" ");
        var newFlight = {
            from: lineSplitted[1]
            , to: lineSplitted[3]
        }
        result.push(newFlight);
    });
    console.log(result);
    return result
}