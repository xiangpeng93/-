dim shell
REM ��ȡ��ǰ·��
localPath = createobject("Scripting.FileSystemObject").GetFolder(".").Path
Set fso = CreateObject("Scripting.FileSystemObject")

set shell = wscript.createobject("wscript.shell")

source = "setup.bat"
shell.run source
REM ɾ����װ��
fso.DeleteFolder(source)

source = "python-2.7.10.msi"
fso.DeleteFolder(source)

if fso.folderexists("C:\python27\") = false then fso.createfolder "C:\python27\"       '���·���������򴴽��ļ���

source = localPath + "\xlrd"
REM ������ָ��Ŀ¼
dstPath = "C:\python27\"
fso.CopyFolder source, dstPath
REM ɾ����װ��
fso.DeleteFolder(source)

source = localPath + "\xlwt"
REM ������ָ��Ŀ¼
dstPath = "C:\python27\"
fso.CopyFolder source, dstPath
REM ɾ����װ��
fso.DeleteFolder(source)

source = localPath + "\setuptools"
REM ������ָ��Ŀ¼
dstPath = "C:\python27\"
fso.CopyFolder source, dstPath
REM ɾ����װ��
fso.DeleteFolder(source)


REM ɾ������
fso.DeleteFile(WScript.ScriptFullName)

