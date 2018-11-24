const { exec }= require ('child_process');
const http = require('http');

exports.scoreupd = function(i,name,response)
{	
	exec('echo "' + i +' '+ name.question[1] + ' '+name.owner +'" | cat >> scorelog.txt',(err,stdout,stderr) =>{
		exec('./standingscalc');
		response.end();
	});
}
