# Powershell
<!-- vscode-markdown-toc -->
* 1. [Introduction](#Introduction)
* 2. [Transfer file SCP](#TransferfileSCP)
* 3. [Compress and copy](#Compressandcopy)
* 4. [Windows PowerShell ISE](#WindowsPowerShellISE)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->
##  1. <a name='Introduction'></a>Introduction

[PowerShell](https://learn.microsoft.com/en-us/powershell/scripting/overview?view=powershell-7.3) is cross-platform, but it will be used mainly on Windows SO, the following is a description from the official documentation:

>Powershell is a cross-platform task automation solution made up of a command-line shell, a scripting language, and a configuration management framework. PowerShell runs on Windows, Linux, and macOS.
>
>PowerShell is a modern command shell that includes the best features of other popular shells. Unlike most shells that only accept and return text, PowerShell accepts and returns .NET objects.
>
>As a scripting language, PowerShell is commonly used for automating the management of systems. It's also used to build, test, and deploy solutions, often in CI/CD environments. PowerShell is built on the .NET Common Language Runtime (CLR). All inputs and outputs are .NET objects. No need to parse text output to extract information from output.

The scripting can be used with scheduling, mainly on Windows Server for maintenance purposes or for daily tasks that repeatedly occur.

##  2. <a name='TransferfileSCP'></a>Transfer file SCP

The file `transferSCP.ps1` contains the following code for file transfer over SCP:

```ps1
$lib = 'root@1.1.1.1:/path/lib'
$bin = 'root@1.1.1.1:/path/bin'
$targetIP = '1.1.1.1'

$libFolders = @('build\System\Source\Applications\AppLib\libAppLib.so',
'build\System\Source\Applications\ConfigLib\libConfigLib.so',
'build\System\Source\Applications\LoggingLib\libLoggingLib.so',
'build\System\Source\Applications\MiddlewareLib\libMiddlewareLib.so',
'build\System\Source\Applications\PlatformLib\libPlatformLib.so',
'build\System\Source\Applications\UtilityLib\libUtilityLib.so',
'build\System\Source\Applications\WrapperLib\libWrapperLib.so',
'build\System\Source\UI_Applications\libGUI\liblibGUI.so',
'build\System\Source\UI_Applications\UI_Config\libUI_Config.so'
)

$binFolders = @('build\System\Source\UI_Applications\AppName\AppName',
'build\System\Source\Applications\MiddlewareProcess\MiddlewareProcess',
'build\System\Source\UI_Applications\AppSimulator\AppSimulator',
'build\System\Source\Applications\GUIDataManager\GUIDataManager',
'build\System\Source\UI_Applications\AppMonitor\AppMonitor'
)


if( (Test-NetConnection -ComputerName $targetIP -port 22).TcpTestSucceeded )
{

    foreach ($path in $libFolders)
    {
        Write-Output $path
	    scp $path $lib
    }
    

    foreach ($path in $binFolders)
    {
        Write-Output $path
	    scp $path $bin
    }
}

Read-Host -Prompt "Press Enter to exit"
```

##  3. <a name='Compressandcopy'></a>Compress and copy

For backup purposes, sometimes it is necessary to compress files and then copy to a server location. This was previously done with Robocopy and some third party compressing software. However, with powershell it can be done without third party.

Some tutorials will recommend `Robocopy`, don't use this deprecated feature.

##  4. <a name='WindowsPowerShellISE'></a>Windows PowerShell ISE

Modern Windows distributions have the PowerShell ISE to code scripts with the `ps1` extension.

To open it, right click the `ps1` file and click on edit, the software will execute:

![ISE](images/ISE.png)