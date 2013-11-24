function matchTests(txt) {
	var re = /-{25} (\d+) -{25}\n(perfect!|file server generated incorrect output|file server used too much memory|file server failed|file server caused test case to exit with non-zero status)/g;
	var match;
	var arr = new Array();
	while(match = re.exec(txt))
	{
		arr[match[1]] = match[2];
	}
	return arr;
}
var horizontal = true;

//Import bootstrap
var link = document.createElement('LINK');
link.rel='stylesheet';
link.type='text/css';
link.href='https://dl.dropboxusercontent.com/u/51182780/bootstrap.min.css';
document.getElementsByTagName('head')[0].appendChild(link);
//Import JQuery
var sc = document.createElement('SCRIPT');
sc.type='text/javascript';
sc.src ='https://dl.dropboxusercontent.com/u/51182780/jquery-1.10.1.min.js';
document.getElementsByTagName('head')[0].appendChild(sc);

var loc = /\/(submit.php|viewSubmission.php)\?/.exec(document.location.href)[1];
if(loc == 'viewSubmission.php') {
	//Create Table
	var table = document.createElement('table');
	table.id = 'submission_table';
	var arr = matchTests(document.body.innerText);
	if(horizontal) {
		//generate numbers
		var trNum = document.createElement('tr');
		for(var i in arr) {
			var tdI= document.createElement('td');
			tdI.innerText = i;
			trNum.appendChild(tdI);
		}
		table.appendChild(trNum);
		//generate Colors
		var trColor = document.createElement('tr');
		for(var i in arr) {
			var tdC= document.createElement('td');
			var statusColor;
			if(arr[i] == 'perfect!') {
				statusColor = 'green';
			}
			else if(arr[i] == 'file server failed') {
				statusColor = 'orange';
			}
			else {
				statusColor = 'red';
			}
			tdC.style.backgroundColor = statusColor;
			tdC.height = '10px';
			trColor.appendChild(tdC);
		}
		table.appendChild(trColor);
	}
	else {
		for(var i in arr) {
			var tr = document.createElement('tr');
			var tdI= document.createElement('td');
			tdI.innerText = i;
			tr.appendChild(tdI);
			var tdC= document.createElement('td');
			var statusColor;
			if(arr[i] == 'perfect!') {
				statusColor = 'green';
			}
			else if(arr[i] == 'file server failed') {
				statusColor = 'orange';
			}
			else {
				statusColor = 'red';
			}
			tdC.style.backgroundColor = statusColor;
			tdC.width = '10px';
			tr.appendChild(tdC);
			table.appendChild(tr);
		}
	}
	document.body.appendChild(table);
}

else if(loc == 'submit.php') {
	var submissionLinks = new Array();
	var responses = new Object();
	sc.onload = function() {
		//Get the Submission links
		var $anchors = $('a');
		for(var i =0; i < $anchors.length; ++i) {
			var a = $anchors[i];
			if(/viewSubmission/.test(a.href)) {
				submissionLinks.push(a);
			}
		}
		for(var i = 0; i < submissionLinks.length; ++i) {
			var go = $.get(submissionLinks[i].href, function(data) {
				var key = /&([^]*)$/.exec(this.url);
				key = key[1];
				responses[key] = matchTests(data);
				console.log("responses length: " + Object.keys(responses).length);
				console.log("submissionLinks length: " + submissionLinks.length);
				//When have gotten responses from everything
				if(Object.keys(responses).length == submissionLinks.length) {
					//Make sure all responses are same length
					var lengths = new Array();
					for(var i in responses) {
						lengths.push(responses[i].length);
					}
					if(lengths.length == 0) {
						alert("No submissions");
					}

					for(var i = 0; i < lengths.length -1; ++i) {
						if(lengths[i] != lengths[i+1]) {
							alert("Incompatible lengths");
						}
					}
					//Create Table
					var table = document.createElement('table');
					table.id = 'submission_table';
					var arr = matchTests(document.body.innerText);
					if(horizontal) {
						//generate numbers
						var trNum = document.createElement('tr');
						var tdHeader= document.createElement('th');
						tdHeader.innerText = 'Test Cases';
						trNum.appendChild(tdHeader);
						for(var i = 0; i < lengths[0]; ++i) {
							var tdI= document.createElement('td');
							tdI.innerText = i;
							trNum.appendChild(tdI);
						}
						table.appendChild(trNum);
						for(var index = 0; index < submissionLinks.length; ++index) {
							var key = /&([^]*)$/.exec(submissionLinks[index]);
							key = key[1];
							//generate Colors
							var trColor = document.createElement('tr');
							var thName = document.createElement('th');
							thName.innerText = key;
							trColor.appendChild(thName);
							var arr = responses[key];
							for(var i in arr) {
								var tdC= document.createElement('td');
								var statusColor;
								if(arr[i] == 'perfect!') {
									statusColor = 'green';
								}
								else
								    if(arr[i] == 'file server failed') {
									statusColor = 'orange';
								}
								else {
									statusColor = 'red';
								}
								tdC.style.backgroundColor = statusColor;
								tdC.height = '10px';
								trColor.appendChild(tdC);
							}
							table.appendChild(trColor);
						}
					}
					document.body.appendChild(table);
				}
			});
		}
	}
}
