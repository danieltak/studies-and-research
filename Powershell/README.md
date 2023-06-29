## Introduction

[PowerShell](https://learn.microsoft.com/en-us/powershell/scripting/overview?view=powershell-7.3) is cross-platform, but it will be used mainly on Windows SO, the following is a description from the official documentation:

>Powershell is a cross-platform task automation solution made up of a command-line shell, a scripting language, and a configuration management framework. PowerShell runs on Windows, Linux, and macOS.
>
>PowerShell is a modern command shell that includes the best features of other popular shells. Unlike most shells that only accept and return text, PowerShell accepts and returns .NET objects.
>
>As a scripting language, PowerShell is commonly used for automating the management of systems. It's also used to build, test, and deploy solutions, often in CI/CD environments. PowerShell is built on the .NET Common Language Runtime (CLR). All inputs and outputs are .NET objects. No need to parse text output to extract information from output.

The scripting can be used with scheduling, mainly on Windows Server for maintenance purposes or for daily tasks that repeatedly occur.

## Transfer file SCP

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

