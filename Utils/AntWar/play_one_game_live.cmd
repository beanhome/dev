@echo off

set Map=maze\maze_9.map

set PlayGameCmd=c:\\Python27\\python.exe %~dp0playgame.py

set Option=-So --engine_seed 42 --player_seed 42 --end_wait=0.25 --verbose --log_dir game_logs --turns 200 --map_file %~dp0maps\%Map% %*


set Bot1="../../Build/AntWar/exe/Release/AntWar.exe"
REM set Bot1=./bots/AntWar.exe

REM set Bot1="python %~dp0sample_bots\python\HunterBot.py"
set Bot2="python %~dp0sample_bots\python\LeftyBot.py"

set Bot3="python %~dp0sample_bots\python\HunterBot.py"
set Bot4="python %~dp0sample_bots\python\LeftyBot.py"

%PlayGameCmd% %Option% %Bot1% %Bot2% %Bot3% %Bot4% | java -jar visualizer.jar

copy "..\..\Build\AntWar\exe\Release\Input.txt" "..\..\WorkingDir\AntWar\"