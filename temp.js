var express = require('express'), 
     app = express(), 
     server = require('http').createServer(app) 
     io = require('socket.io').listen(server); 
 
 
 var port = '/dev/usbmodem'; 
 var serialport = require("serialport"); 
 var SerialPort = serialport.SerialPort; 
 
 
 var sp = new SerialPort(port, { 
   parser: serialport.parsers.readline("\n"), 
   baudrate: 9600 
 }); 
  
 
 sp.on("open", function () { 
     console.log('open'); 
 
     sp.on('data', function(data){ }); 
  
     io.sockets.on('connection', function (socket) { 
       sp.on('data', function(data) { 
       socket.emit('temps', { temp: data }); 
     }); 
   }); 
 }); 
 
 
 app.engine('html', require('ejs').renderFile); 
 app.set('view engine', 'html');  
   
 app.get('/', function (req, res) { 
   //res.sendfile(__dirname + '/views/index.html'); 
   res.render('index', {title: "3,2,1"}); 
 }); 
 
 
 app.use(express.static(__dirname + '/public')); 
 var port = process.env.PORT || 3000 
 console.log('listening on port ' + port + ''); 
 server.listen(port); 
