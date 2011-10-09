@echo off

REM c:\\Python27\\python.exe playgame.py --engine_seed 42 --player_seed 42 --food none --end_wait=0.25 --verbose --log_dir game_logs --turns 30 --map_file submission_test/test.map %1 "python submission_test/TestBot.py" -e --nolaunch --strict --capture_errors

set PlayGameCmd=c:\\Python27\\python.exe playgame.py

REM set Bot="../../Project_2008/AntWar/Debug/AntWar.exe"
set Bot="AntWar.exe"

set Command= --engine_seed 42 --player_seed 42 --food none --end_wait=0.25 --verbose --log_dir game_logs --turns 30 --map_file submission_test/test.map %Bot% "python submission_test/TestBot.py" -e --nolaunch --strict --capture_errors

%PlayGameCmd% %Command%

pause