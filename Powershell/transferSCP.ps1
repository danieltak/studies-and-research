$lib = 'root@1.1.1.1:/path/lib'
$bin = 'root@1.1.1.1:/path/bin'

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


if( (Test-NetConnection -ComputerName "1.1.1.1" -port 22).TcpTestSucceeded )
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