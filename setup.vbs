REM ��ȡ��ǰ·��
localPath = createobject("Scripting.FileSystemObject").GetFolder(".").Path

Set fso = CreateObject("Scripting.FileSystemObject")
source = localPath + "\TBM"

REM ������ָ��Ŀ¼
dstPath = "C:\Program Files (x86)\"
fso.CopyFolder source, dstPath

REM ɾ����װ��
fso.DeleteFolder(source)

set WshShell=WScript.CreateObject("WScript.Shell")  

strDesktop=WshShell.SpecialFolders("Desktop")  
set oShellLink=WshShell.CreateShortcut(strDesktop & "\ˢ������.lnk")  
oShellLink.TargetPath="C:\Program Files (x86)\TBM\ˢ������.exe"  
oShellLink.WindowStyle=1
oShellLink.Description="ˢ������"  
oShellLink.WorkingDirectory=strDesktop  
oShellLink.Save 

REM ɾ������
fso.DeleteFile(WScript.ScriptFullName)
