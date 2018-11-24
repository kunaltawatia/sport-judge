var py_checkerjs = require ('./py_checker'); 

exports.compile = function(name,res)
{
	res.write('Runtime result:\n');
	py_checkerjs.step(0,name.tot_test,name,res);
}