dim shell
REM 获取当前路径
localPath = createobject("Scripting.FileSystemObject").GetFolder(".").Path
Set fso = CreateObject("Scripting.FileSystemObject")

set shell = wscript.createobject("wscript.shell")


source = localPath + "\xlrd"
REM 拷贝至指定目录
dstPath = "C:\python27\"
fso.CopyFolder source, dstPath
REM 删除安装包
fso.DeleteFolder(source)

source = localPath + "\xlwt"
REM 拷贝至指定目录
dstPath = "C:\python27\"
fso.CopyFolder source, dstPath
REM 删除安装包
fso.DeleteFolder(source)

source = localPath + "\setuptools"
REM 拷贝至指定目录
dstPath = "C:\python27\"
fso.CopyFolder source, dstPath
REM 删除安装包
fso.DeleteFolder(source)

source = "setup.bat"
shell.run source
REM 删除安装包
fso.DeleteFolder(source)

source = "python-2.7.10.msi"
fso.DeleteFolder(source)

REM 删除自身
fso.DeleteFile(WScript.ScriptFullName)

