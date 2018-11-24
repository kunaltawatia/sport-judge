var c_cpp_checkerjs = require ('./c_cpp_checker'); 
const { exec }= require ('child_process');
var score = require('./score');

exports.step = function(i,tot_test,name,res)
{
	if(i<tot_test){
		var infile = name.input + 'input'+i+'.txt';
		var outfile = name.origin + 'output'+ i +'.txt';
		var tym = Date.now(); 
		// console.log('testcase:' + i);
		exec('cat '+infile+' | timeout '+name.timelt+' '+name.origin+' > '+ outfile,(err,stdout,stderr)=>{ 
			// console.log('cat '+infile+' | timeout '+name.timelt+' '+name.origin+' > '+ outfile);
			var timeused =Date.now()-tym;
			res.write('testcase '+i+': ');
			res.write('(' + timeused+' ms)');
			if(timeused > name.timelt * 1000)
			{	
				res.write(' TLE\n');
				if(i>=name.min_testcase){
					score.scoreupd(i,name,res);
				}
				return res.end();
			}
			if(err)
			{
				// console.log('yes');
				res.write(`${stderr}`);
				return res.end();
			}
			var ansfile = name.output + 'ans' + i +'.txt';
			// console.log(name.output +'checker '+ansfile + ' ' +outfile);
			exec(name.output +'checker '+ansfile + ' ' +outfile ,(err,stdout,stderr)=>{
				if(err)
					console.log(`${stderr}`);	
				var ans = `${stdout}`;
				if(ans == '0')
				{
					res.write(' AC\n');
					c_cpp_checkerjs.step(i+1,tot_test,name,res);
				}
				else 
				{
					res.write(' WA\n');
					if(i>=name.min_testcase){
						score.scoreupd(i,name,res);
					}
					return res.end();
				}
				});
		});
	}
	else
	{
		score.scoreupd(i,name,res);
	}
}
