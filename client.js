   var socket = io.connect('http://localhost'); 
   socket.on('temps', function (data) { 
     console.log(data.temp); 
     socket.emit('my other event', { my: 'data' }); 
 
 
     document.getElementById('display_temperature').innerHTML = data.temp; 
   }); 
