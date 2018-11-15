var http = require('http');
var formidable = require('formidable');
var fs = require('fs');
var url = require('url');
const { exec }= require ('child_process');

function typecheck(name)
{
	var str=name.slice(name.lastIndexOf('.'),name.length);
	switch(str)
	{
		case '.cpp' : return 1;
		case '.c' : return 2;
		case '.h' : return 3;
		default : return 0;
	}
}
function splitstring(codeurl)
{
	var res = codeurl.split('/');
	var str = fs.readFileSync('./main/' + res[2] + '/testcase/input/cons.txt' ,'utf8');
	var cons = str.split('\n');
	var ret={
		main : res[1],
		question :res[2],
		name : res[4],
		input : './main/' + res[2] + '/testcase/input/',
		output : './main/' + res[2] + '/testcase/output/' ,
		timelt : cons[0] , 
		tot_test : cons[1] ,
		origin : codeurl  
	};
	return ret;
}
function step(i,tot_test,name,res)
{
	if(i<tot_test){
		var infile = name.input + 'input'+i+'.txt';
		var outfile = name.origin + 'output'+ i +'.txt';
		var tym = Date.now(); 
		exec('cat '+infile+' | timeout '+name.timelt+' '+name.origin+' > '+ outfile,(err,stdout,stderr)=>{ 
			var timeused =Date.now()-tym;
			res.write('testcase '+i+': ');
			res.write('(' + timeused+' ms)');
			if(timeused > name.timelt * 1000)
			{	
				res.write(' TLE\n');
				return res.end();
			}
			if(err)
				{
					res.write(`${stderr}`);
					return res.end();
				}
			var ansfile = name.output + 'ans' + i +'.txt';
			exec(name.output +'checker '+ansfile + ' ' +outfile ,(err,stdout,stderr)=>{
				if(err)
					console.log(' '+`${stderr}`);	
				var ans = `${stdout}`;
				if(ans == 0)
				{
					res.write(' AC\n');
					step(i+1,tot_test,name,res);
				}
				else 
				{
					res.write(' WA\n');
					return res.end();
				}
				});
		});
	}
	else return res.end();
}
function compile(name,res)
{
	res.write('Runtime result:\n');
	step(0,name.tot_test,name,res);
}
http.createServer(function (req, res) 
{
 	var q = url.parse(req.url, true);
	var page = '.'+q.pathname;
	if(page == './')
  		fs.readFile('main.html',function(err,data){
  			if (err) 
			{
		      res.writeHead(404, {'Content-Type': 'text/html'});
		      return res.end("404 Not Found");
		    }  
			res.writeHead(200, {'Content-Type': 'text/html'});
			res.write(data);
			res.end();
  		});
  	else if(page.endsWith('upcode'))
  	{
  		var form = new formidable.IncomingForm();
		form.parse(req, function (err, fields, files) 
			{
				if(! files.code)
				{
					res.write("Code not found !");
					return res.end();
				}
      			var oldpath = files.code.path;
      			var newpath = files.code.name;
			    var flag = typecheck(newpath);
			    if(flag==3)
			    {
			    	fs.rename(oldpath,page +'/'+ newpath, function (err)
			    	{
			    		if(err) throw err;
				       	res.write('Header File uploaded and ready to use please go back to submit your code!\n');
				    	res.end();
			    	});
			    }
				else if(flag)
				{
			      fs.rename(oldpath,page +'/'+ newpath, function (err)
			       {
				        if (err) throw err;
				       	res.write('File uploaded and moved!\n');
				       	var str = page +'/'+ newpath;
				       	var codefile = str.slice(0,str.lastIndexOf('.'));
				       	exec('make '+codefile , (err, stdout, stderr) => 
				       	{		
							res.write('Compilation result:\n');
							res.write(`${stdout}`+ '\n') ;
							if (err) 
							{
								var error = `${stderr}`;
								res.write( error + '\nCompilation failed !');
								return res.end();
							}
							else
							{
								res.write('Successfully Compiled !\n\n');
								var name = splitstring(codefile);
								compile(name,res);
							}
						});
			       });
				}
				else
				{
					res.writeHead(200, {'Content-Type': 'text/html'});
					res.write('<p>*.c or *.cpp file is to be passed, go back</p>');
					res.end();
				}
			});
  	}
  	else 
  		fs.readFile(page,function(err,data){
  			if (err) 
			{
		      res.writeHead(404, {'Content-Type': 'text/html'});
		      return res.end("404 Not Found");
		    }  
			res.writeHead(200, {'Content-Type': 'text/html'});
			res.write(data);
	res.end();
  		});
}).listen(8000);