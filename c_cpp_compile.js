var c_cpp_checkerjs = require ('./c_cpp_checker');
const { exec }= require ('child_process'); 

exports.compile = function(name,res,codefile,flag)
{
	if(flag==1)
	{
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
					res.write('Runtime result:\n');
					c_cpp_checkerjs.step(0,name.tot_test,name,res);
				}
		});
	}
	else
	{
		exec('g++ -std=c++1y '+name.initialtitle + ' -o ' + codefile , (err, stdout, stderr) => 
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
					res.write('Runtime result:\n');
					c_cpp_checkerjs.step(0,name.tot_test,name,res);
				}
		});
	}
}