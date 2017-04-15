set shell = wscript.createobject("wscript.shell")

REM 设置环境变量
pythonEnv = shell.Environment.Item( "PATH" ) & ";C:\python27\"
shell.Environment.Item( "PATH" ) = pythonEnv

Set fso = CreateObject("Scripting.FileSystemObject")

source = "setenv.bat"
shell.run source
REM 删除安装包
fso.DeleteFolder(source)


REM 删除自身
fso.DeleteFile(WScript.ScriptFullName)