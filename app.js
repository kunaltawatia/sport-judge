var http = require('http');
var formidable = require('formidable');
var fs = require('fs');
var url = require('url'); 
var c_cpp_compiler = require ('./c_cpp_compile');
var py_compile = require ('./py_compile'); 
const { exec }= require ('child_process');

function typecheck(name)
{
	name = name.slice(name.lastIndexOf('.')+1,name.length);
	switch(name)
	{
		case 'cpp': return 2;
		case 'c': return 1;
		case 'py': return 3;
		case 'h': return 4;
		default: return 0;
	} 
}
function splitstring(codeurl)
{
	var res = codeurl.split('/');
	var str = fs.readFileSync('./main/' + res[2] + '/testcase/input/cons.txt' ,'utf8');
	var str1 = fs.readFileSync('./main/' + res[2] + '/testcase/input/scoring.txt' ,'utf8');
	var cons = str.split('\n');
	var scr = str1.split('\n');
	var ret={
		main : res[1],
		question :res[2],
		name : res[4],
		input : './main/' + res[2] + '/testcase/input/',
		output : './main/' + res[2] + '/testcase/output/' ,
		timelt : cons[0] , 
		tot_test : cons[1] ,
		min_testcase : scr[0] ,
		owner: '',        
		initialtitle: '',
		origin : codeurl  
	};
	return ret;
}
function checkip(ipaddr)
{
	exec ('./checkip '+ipaddr,(err,stdout,stderr)=>
	{
		return `${stdout}`;
	});
}
http.createServer(function (req, res) 
{
	var q = url.parse(req.url, true);
	var page = '.'+q.pathname;
	var ipaddr = (req.connection.remoteAddress);
	ipaddr = ipaddr.slice(ipaddr.lastIndexOf(':')+1,ipaddr.length);
	if(page.endsWith('upuser'))
	{
		var form = new formidable.IncomingForm();
		form.parse(req,function (err, fields, files) 
		{
			exec('./reguser '+fields.handler+ ' '+ipaddr,(err,stdout,stderr)=>{
			res.writeHead(302, {
				'Content-Type': 'text/plain',
				'Location': '/'});
			res.end();
			});
		});
	}
	else
	{
		var isuser ;//= checkip(ipaddr);
		exec ('./checkip '+ipaddr,(err,stdout,stderr)=>
		{
			isuser = `${stdout}`;
			if(isuser)
			{
				req.user = isuser;
				console.log(isuser);
				if(page == './')
			  		fs.readFile('main.html',function(err,data)
			  		{
			  			if (err) 
						{
					      res.writeHead(404, {'Content-Type': 'text/html'});
					      return res.end("404 Not Found");
					    }  
						res.writeHead(200, {'Content-Type': 'text/html'});
						res.write(data);
						res.write('<p style="text-align : center;">Welcome '+req.user +'</p>');
						res.end();
			  		});
			  	else if(page.endsWith('standings'))
			  	{
			  		exec('cat standings.txt',(err,stdout,stderr)=>{
			  			res.writeHead(200, {'Content-Type': 'text/plain-text'});
			  			
			  			res.write(`${stdout}`);
			  			res.end();
			  		});
			  	}
			  	else if(page.endsWith('upcode'))
			  	{
			  		var form = new formidable.IncomingForm();
			  		//console.log(form);
					form.parse(req,function (err, fields, files) 
						{
							//console.log(files.code);
							if(!files.code.size)
							{
								res.write("Code not found !");
								return res.end();
							}
			      			var oldpath = files.code.path;
			      			var newpath = files.code.name;
						    var flag = fields.language;
							var str = page +'/'+ newpath;
							var codefile = str.slice(0,str.lastIndexOf('.'));
							var name = splitstring(codefile);
							var ipaddr = (req.connection.remoteAddress);
							name.owner = ipaddr.slice(ipaddr.lastIndexOf(':')+1,ipaddr.length);
							name.initialtitle = str;
							//console.log(name.owner);
							if(flag && flag < 4)
							{		
						       fs.rename(oldpath,page +'/'+ newpath, function (err)
						       {
							        if (err) throw err;
							       	res.write('File uploaded and moved!\n');
							       	if(flag<3) c_cpp_compiler.compile(name,res,codefile,flag);
									else py_compile.compile(name,res);
						       });
							}
							else if(flag==4)
						    {
						    	fs.rename(oldpath,page +'/'+ newpath, function (err)
						    	{
						    		if(err) throw err;
							       	res.write('Header File uploaded and ready to use please go back to submit your code!\n');
							    	res.end();
						    	});
						    }
							else
							{
								res.writeHead(200, {'Content-Type': 'text/html'});
								res.write('<p text-align=center;>Code file is to be passed, go back</p>');
								res.end();
							}
						});
			  	}
			  	else {
			  		page=page.slice(0,page.lastIndexOf('.'));
			  		fs.readFile(page+'.html',function(err,data){
			  			if (err) 
						{
					      res.writeHead(404,{'Content-Type': 'text/html'});
					      return res.end("404 Not Found");
					    }  
						res.writeHead(200,{'Content-Type': 'text/html'});
						res.write(data);
						res.end();
			  		});
			  	}
			}
			else
			{
				console.log(ipaddr);
				fs.readFile('newuser.html',function(err,data){
			  			if (err) 
						{
					      res.writeHead(404,{'Content-Type': 'text/html'});
					      return res.end("404 Not Found");
					    }  
						res.writeHead(200,{'Content-Type': 'text/html'});
						res.write('<p>Your IP : '+ipaddr+' is not registered with our system.</p>');
						res.write(data);
						res.end();
			  		});
			}
		});
	}
}).listen(8000);
