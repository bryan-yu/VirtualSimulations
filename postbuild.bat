del %~dp0resources\lib\debug\clean.lib
del %~dp0resources\lib\release\clean.lib

copy /y %~dp0Debug\clean.lib %~dp0resources\lib\debug\clean.lib
copy /y %~dp0Release\clean.lib %~dp0resources\lib\release\clean.lib