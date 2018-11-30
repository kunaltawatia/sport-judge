sudo apt install nodejs
sudo apt install npm
npm i formidable
sudo apt-get update
sudo apt-get install gcc-6 g++-6
sudo apt install python3.6
echo "Compiling files ..."
g++ -std=c++1y checkip.cpp -o checkip 
g++ -std=c++1y reguser.cpp -o reguser
g++ -std=c++1y standingscalc.cpp -o standingscalc
g++ -std=c++1y ./main/q1/testcase/output/checker.cpp -o ./main/q1/testcase/output/checker
g++ -std=c++1y ./main/q2/testcase/output/checker.cpp -o ./main/q2/testcase/output/checker
g++ -std=c++1y ./main/q3/testcase/output/checker.cpp -o ./main/q3/testcase/output/checker
g++ -std=c++1y ./main/q4/testcase/output/checker.cpp -o ./main/q4/testcase/output/checker
echo "Ready to create server"
