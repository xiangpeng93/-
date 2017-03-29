
REM 获取当前路径
localPath = createobject("Scripting.FileSystemObject").GetFolder(".").Path

Set fso = CreateObject("Scripting.FileSystemObject")
source = localPath + "\TBM"

REM 拷贝至指定目录
dstPath = "C:\Program Files (x86)\"
fso.CopyFolder source, dstPath

REM 删除安装包
fso.DeleteFolder(source)

set WshShell=WScript.CreateObject("WScript.Shell")  

strDesktop=WshShell.SpecialFolders("Desktop")  
set oShellLink=WshShell.CreateShortcut(strDesktop & "\刷单管理.lnk")  
oShellLink.TargetPath="C:\Program Files (x86)\TBM\刷单管理.exe"  
oShellLink.WindowStyle=1
oShellLink.Description="刷单管理"  
oShellLink.WorkingDirectory=strDesktop  
oShellLink.Save 

REM 删除自身
fso.DeleteFile(WScript.ScriptFullName)
