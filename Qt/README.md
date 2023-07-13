# Qt
<!-- vscode-markdown-toc -->
* 1. [General Issues](#GeneralIssues)
	* 1.1. [Locale](#Locale)
	* 1.2. [Weston non-root permission](#Westonnon-rootpermission)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->




##  1. <a name='GeneralIssues'></a>General Issues

###  1.1. <a name='Locale'></a>Locale

The following error message is displayed:

>Detected system locale encoding (ANSI_X3.4-1968, locale "C") is not UTF-8. Qt shall use a UTF-8 locale ("UTF-8") instead. If this causes problems,
reconfigure your locale. See the locale(1) manual for more information.

A temporary solution is to set the environmental variable `LANG` with the following command on the terminal:

`export LANG=en_US.utf8`

However, it is only a temporary solution for tests, a better solution is to install the `locale` command and set the locale on the system startup.

###  1.2. <a name='Westonnon-rootpermission'></a>Weston non-root permission

The following error message is displayed:

> QStandardPaths: runtime directory '/run/user/1000' is not owned by UID 0, but a directory permissions 0700 owned by UID 1000 GID 1000

When you try to run a executable with the root user on Wayland, using Weston, the GUI executable will be owned by the weston user and the root user can't access it.

A temporary solution is to change the ownership of the executable file.

On the [Free Desktop email list question "Weston on RPi: running as non-root"](https://lists.freedesktop.org/archives/wayland-devel/2013-January/006871.html):

> Weston will create the socket with permissions so that only the user
weston runs as can access it.  This is deliberate and how the
authentication works.  As such, you can't run weston as root and then
connect to it as a different, regular user.  In fact, you shouldn't
run weston (including all of GL, shader compiler, protocol handling
etc) as root.  I'm not familiar with the requirements of the rpi
backend, that is, what kind of access is required to run weston, but
if there's a graphics device that you need to be root to open, we
should do that in weston-launch, similar to how we handle the
limitations of linux drm and input devices.

 Although it is not recommended, you can change the file at `/etc/init.d/weston` and change the user var from weston to root.

## Qt Projects

- https://github.com/gamecreature/QtAwesome
- https://github.com/zhuzichu520/FluentUI
- https://github.com/Swordfish90/cool-retro-term
- https://github.com/lirios/fluid
- https://github.com/jaredtao/TaoQuick
- 