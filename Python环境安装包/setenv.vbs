set shell = wscript.createobject("wscript.shell")

REM ���û�������
pythonEnv = shell.Environment.Item( "PATH" ) & ";C:\python27\"
shell.Environment.Item( "PATH" ) = pythonEnv

Set fso = CreateObject("Scripting.FileSystemObject")


REM ɾ������
fso.DeleteFile(WScript.ScriptFullName)