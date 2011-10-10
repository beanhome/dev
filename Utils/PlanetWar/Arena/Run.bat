@set PlayGameCmd=java -Duser.language=en -Duser.region=US -jar tools/PlayGame.jar
REM @set PlayGameCmd=java -jar tools/PlayGame.jar

@set MapName=maps/map17.txt

REM @set Bot01="java -jar example_bots/RandomBot.jar"
@set Bot01="../../../Build/PlanetWar/exe/Debug/Beanhome.exe"
REM @set Bot01="Arena/IAs/Beanhome.exe"

REM @set Bot02="java -jar example_bots/BullyBot.jar"
REM @set Bot02="java -jar example_bots/DualBot.jar"
REM @set Bot02="java -jar example_bots/ProspectorBot.jar"
REM @set Bot02="java -jar example_bots/RageBot.jar"
REM @set Bot02="java -jar example_bots/RandomBot.jar"

@set Bot02="Arena/IAs/Beanhome_02.exe"
REM @set Bot02="archive/Beanhome_01.exe"


%PlayGameCmd% %MapName% 1000 1000 log.txt %Bot01% %Bot02% | java -jar tools/ShowGame.jar