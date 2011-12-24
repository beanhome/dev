@echo off

REM set Map=maze\maze_20.map
set Map=multi_hill_maze\multi_maze_05.map

set PlayGameCmd=c:\\Python27\\python.exe %~dp0playgame.py

set Option=-So --engine_seed 42 --player_seed 42 --end_wait=0.25 --verbose --log_dir game_logs --turns 500 --map_file %~dp0maps\%Map% %*


set Bot1="../../Build/AntWar/exe/Release/AntWar.exe"
REM set Bot1=./bots/AntWar.exe

REM set Bot2="bots\Garion.exe"
REM set Bot2="bots\MomoBot_v11.exe"
set Bot2="../../Build/AntWar/exe/Release/AntWar.exe"


REM set Bot1="python %~dp0sample_bots\python\HunterBot.py"
REM set Bot2="python %~dp0sample_bots\python\LeftyBot.py"
set Bot3="python %~dp0sample_bots\python\HunterBot.py"
set Bot4="python %~dp0sample_bots\python\LeftyBot.py"
set Bot5="python %~dp0sample_bots\python\HunterBot.py"
set Bot6="python %~dp0sample_bots\python\HoldBot.py"
set Bot7="python %~dp0sample_bots\python\GreedyBot.py"
set Bot8="python %~dp0sample_bots\python\RandomBot.py"

REM %PlayGameCmd% %Option% %Bot1% %Bot2% %Bot3% %Bot4% %Bot5% %Bot6% %Bot7% %Bot8% | java -jar visualizer.jar
%PlayGameCmd% %Option% %Bot1% %Bot2% | java -jar visualizer.jar

copy "..\..\Build\AntWar\exe\Release\Input.txt" "..\..\WorkingDir\AntWar\"

REM pause