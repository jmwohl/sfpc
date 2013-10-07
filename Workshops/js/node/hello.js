var http = require('http');

http.createServer(
	function (req, res) {
		console.log(req.headers);
		res.writeHead(200, {'Content-Type': 'text/html'});
		res.end("<h1>Hello World</h1>");
	}
).listen(8000);
