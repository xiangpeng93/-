set shell = wscript.createobject("wscript.shell")

REM ���û�������
pythonEnv = shell.Environment.Item( "PATH" ) & ";C:\python27\"
shell.Environment.Item( "PATH" ) = pythonEnv

Set fso = CreateObject("Scripting.FileSystemObject")

source = "setenv.bat"
shell.run source
REM ɾ����װ��
fso.DeleteFolder(source)


REM ɾ������
fso.DeleteFile(WScript.ScriptFullName)