# Linux POSIX

<!-- vscode-markdown-toc -->
* 1. [Misc Commands](#MiscCommands)
	* 1.1. [Valgrind](#Valgrind)
	* 1.2. [top](#top)
* 2. [Use ip instead of ifconfig](#Useipinsteadofifconfig)
* 3. [Netlink](#Netlink)
* 4. [LTTng](#LTTng)
* 5. [Default Permission](#DefaultPermission)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->


##  1. <a name='MiscCommands'></a>Misc Commands

###  1.1. <a name='Valgrind'></a>Valgrind

https://valgrind.org/docs/manual/quick-start.html

```
valgrind --leak-check=full \
         --show-leak-kinds=definite \
         --track-origins=yes \
         --verbose \
         --log-file=/home/root/valgrind-date.txt \
         /path/to/executable "args"
```

###  1.2. <a name='top'></a>top

First use `ps aux` to list every process running and get the target process id (PID), then run `top -H -p pid_number` to watch the running threads or for the child processes `pgrep -lP pid_number`



##  2. <a name='Useipinsteadofifconfig'></a>Use ip instead of ifconfig

On an answer from 2012 on the [Sever Fault website](https://serverfault.com/questions/458628/should-i-quit-using-ifconfig):

>The command `/bin/ip` has been around for some time now. But people continue using the older command `/sbin/ifconfig`. Let's be clear: `ifconfig` will not quickly go away, but its newer version, `ip`, is more powerful and will eventually replace it.
>
>The man page of ip may look intimidating at first, but once you get familiar with the command syntax, it is an easy read. This page will not introduce the new features of ip. It rather features a side-by-side comparison if ifconfig and ip to get a quick overview of the command syntax.
>
>Similarly, the `arp`, `route` and `netstat` commands are also deprecated.

https://unix.stackexchange.com/questions/605615/how-to-change-network-mask-using-ip-command

https://access.redhat.com/sites/default/files/attachments/rh_ip_command_cheatsheet_1214_jcs_print.pdf

https://vmware.github.io/photon/assets/files/html/3.0/photon_admin/use-ip-and-ss-commands.html

##  3. <a name='Netlink'></a>Netlink

On the [Kernel website](https://docs.kernel.org/userspace-api/netlink/intro.html) the introduction to Netlink is the following:

> Netlink is often described as an ioctl() replacement. It aims to replace fixed-format C structures as supplied to ioctl() with a format which allows an easy way to add or extended the arguments.
>
>To achieve this Netlink uses a minimal fixed-format metadata header followed by multiple attributes in the TLV (type, length, value) format.
>
>Unfortunately the protocol has evolved over the years, in an organic and undocumented fashion, making it hard to coherently explain. To make the most practical sense this document starts by describing netlink as it is used today and dives into more "historical" uses in later sections.

An example can be found on the [ucon.c](ucon.c) file.

https://github.com/mwarning/netlink-examples

https://www.kernel.org/doc/Documentation/connector/connector.txt

https://docs.kernel.org/userspace-api/netlink/index.html

https://man7.org/linux/man-pages/man7/netlink.7.html

https://stackoverflow.com/q/3299386/7690982

https://natanyellin.com/posts/buggy-netlink-process-connectors/

One example of use is a connector of `proc_event`, filename `cn_proc.h`.

##  4. <a name='LTTng'></a>LTTng

https://imasters.com.br/devsecops/introducao-a-ferramenta-lttng-monitorando-eventos-em-linux

https://man7.org/linux/man-pages/man1/lttng.1.html

https://lttng.org/

##  5. <a name='DefaultPermission'></a>Default Permission

The default file permissions can be set using Access Control List (ACL), that provides an additional, more flexible permission mechanism for [file systems](https://wiki.archlinux.org/title/File_systems). It is designed to assist with UNIX file permissions. ACL allows you to give permissions for any user or group to any disk resource.

The `chmod` and `chown` commands are used to change the permissions of the target files and folders only once, [setfacl](https://linux.die.net/man/1/setfacl) command needs to be used to set the permissions rules on an advanced way.

