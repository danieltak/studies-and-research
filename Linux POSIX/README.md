# Linux POSIX

<!-- vscode-markdown-toc -->
* 1. [Misc Commands](#MiscCommands)
	* 1.1. [Valgrind](#Valgrind)
	* 1.2. [top](#top)
* 2. [Use ip instead of ifconfig](#Useipinsteadofifconfig)
* 3. [Netlink](#Netlink)
* 4. [LTTng](#LTTng)
* 5. [Default Permission](#DefaultPermission)
* 6. [Filesystem Hierarchy Standard (FHS)](#FilesystemHierarchyStandardFHS)
* 7. [Time](#Time)
* 8. [Send Signal](#SendSignal)

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

##  6. <a name='FilesystemHierarchyStandardFHS'></a>Filesystem Hierarchy Standard (FHS) 

The [version 3.0](https://refspecs.linuxfoundation.org/FHS_3.0/fhs/index.html) is the most recent version of the FHS. It is a TL;DR; from the Linux Foundation's documentation.

This [SOen](https://askubuntu.com/a/308048/721545) answer explains the differences between /bin, /sbin, /usr/bin, /usr/sbin, /usr/local/bin, /usr/local/sbin.

For a brief explanation of the FHS, see the [wikipedia](https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard):

>The Filesystem Hierarchy Standard (FHS) is a reference describing the conventions used for the layout of a UNIX system. It has been made popular by its use in Linux distributions, but it is used by other UNIX variants as well. It is maintained by the Linux Foundation. The latest version is 3.0, released on 3 June 2015.

| Directory       | Description                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
|-----------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| /               | Primary hierarchy root and root directory of the entire file system hierarchy.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| /bin            | Essential command binaries that need to be available in single-user mode, including to bring up the system or repair it, for all users (e.g., cat, ls, cp).                                                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| /boot           | Boot loader files (e.g., kernels, initrd).                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| /dev            | Device files (e.g., /dev/null, /dev/disk0, /dev/sda1, /dev/tty, /dev/random).                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
| /etc            | Host-specific system-wide configuration files.  There has been controversy over the meaning of the name itself. In early versions of the UNIX Implementation Document from Bell labs, /etc is referred to as the etcetera directory, as this directory historically held everything that did not belong elsewhere (however, the FHS restricts /etc to static configuration files and may not contain binaries). Since the publication of early documentation, the directory name has been re-explained in various ways. Recent interpretations include backronyms such as "Editable Text Configuration" or "Extended Tool Chest". |
| /etc/opt        | Configuration files for add-on packages stored in /opt.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    |
| /etc/sgml       | Configuration files, such as catalogs, for software that processes SGML.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
| /etc/X11        | Configuration files for the X Window System, version 11.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
| /etc/xml        | Configuration files, such as catalogs, for software that processes XML.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    |
| /home           | Users' home directories, containing saved files, personal settings, etc.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
| /lib            | Libraries essential for the binaries in /bin and /sbin.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    |
| /lib<qual>      | Alternate format essential libraries. These are typically used on systems that support more than one executable code format, such as systems supporting 32-bit and 64-bit versions of an instruction set. Such directories are optional, but if they exist, they have some requirements.                                                                                                                                                                                                                                                                                                                                                   |
| /media          | Mount points for removable media such as CD-ROMs (appeared in FHS-2.3 in 2004).                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            |
| /mnt            | Temporarily mounted filesystems.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           |
| /opt            | Add-on application software packages.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
| /proc           | Virtual filesystem providing process and kernel information as files. In Linux, corresponds to a procfs mount. Generally, automatically generated and populated by the system, on the fly.                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| /root           | Home directory for the root user.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          |
| /run            | Run-time variable data: Information about the running system since last boot, e.g., currently logged-in users and running daemons. Files under this directory must be either removed or truncated at the beginning of the boot process, but this is not necessary on systems that provide this directory as a temporary filesystem (tmpfs).                                                                                                                                                                                                                                                                                                |
| /sbin           | Essential system binaries (e.g., fsck, init, route).                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |
| /srv            | Site-specific data served by this system, such as data and scripts for web servers, data offered by FTP servers, and repositories for version control systems (appeared in FHS-2.3 in 2004).                                                                                                                                                                                                                                                                                                                                                                                                                                               |
| /sys            | Contains information about devices, drivers, and some kernel features.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  |
| /tmp            | Directory for temporary files (see also /var/tmp). Often not preserved between system reboots and may be severely size-restricted.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |
| /usr            | Secondary hierarchy for read-only user data; contains the majority of (multi-)user utilities and applications. Should be shareable and read-only.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
| /usr/bin        | Non-essential command binaries (not needed in single-user mode); for all users.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            |
| /usr/include    | Standard include files.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    |
| /usr/lib        | Libraries for the binaries in /usr/bin and /usr/sbin.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      |
| /usr/libexec    | Binaries run by other programs that are not intended to be executed directly by users or shell scripts (optional).                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |
| /usr/lib<qual>  | Alternative-format libraries (e.g., /usr/lib32 for 32-bit libraries on a 64-bit machine (optional)).                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |
| /usr/local      | Tertiary hierarchy for local data, specific to this host. Typically has further subdirectories (e.g., bin, lib, share).[NB 1]                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
| /usr/sbin       | Non-essential system binaries (e.g., daemons for various network services).                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
| /usr/share      | Architecture-independent (shared) data.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    |
| /usr/src        | Source code (e.g., the kernel source code with its header files).                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          |
| /usr/X11R6      | X Window System, Version 11, Release 6 (up to FHS-2.3, optional).                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          |
| /var            | Variable files: files whose content is expected to continually change during normal operation of the system, such as logs, spool files, and temporary e-mail files.                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| /var/cache      | Application cache data. Such data are locally generated as a result of time-consuming I/O or calculation. The application must be able to regenerate or restore the data. The cached files can be deleted without loss of data.                                                                                                                                                                                                                                                                                                                                                                                                            |
| /var/lib        | State information. Persistent data modified by programs as they run (e.g., databases, packaging system metadata, etc.).                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    |
| /var/lock       | Lock files. Files keeping track of resources currently in use.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| /var/log        | Log files. Various logs.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
| /var/mail       | Mailbox files. In some distributions, these files may be located in the deprecated /var/spool/mail.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| /var/opt        | Variable data from add-on packages that are stored in /opt.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
| /var/run        | Run-time variable data. This directory contains system information data describing the system since it was booted.  In FHS 3.0, /var/run is replaced by /run; a system should either continue to provide a /var/run directory or provide a symbolic link from /var/run to /run for backwards compatibility.                                                                                                                                                                                                                                                                                                                        |
| /var/spool      | Spool for tasks waiting to be processed (e.g., print queues and outgoing mail queue).                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      |
| /var/spool/mail | Deprecated location for users' mailboxes.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
| /var/tmp        | Temporary files to be preserved between reboots.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           |

##  7. <a name='Time'></a>Time

The "time.h" library works and updates the system time, which you can verify using the `date` command on the linux terminal.

To get the time using the time.h library, use the `gettimeofday` function and NULL for the time zone.

```cpp
#include <sys/time.h>

struct timeval tTime;
gettimeofday( &tTime, NULL);
std::cout << tTime.tv_sec << std::endl;
std::cout << tTime.tv_usec << std::endl;
```

To set the time using the time.h library, use the `settimeofday` function and NULL argument for the time zone.

```cpp
#include <sys/time.h>

struct timeval tnewTime;
int iReturn;

tnewTime.tv_sec = 1691067482; // The time in seconds is calculated from some class created, here we are assuming a constant time value.
tnewTime.tv_usec = 0;

iReturn = settimeofday( & tnewTime , NULL );

if ( iReturn == 0 )
{
    system("hwclock --systohc");
}
```

To update the rtc time on the hardware use the `hwclock -w` or `hwclock --systohc`. So the application works on the user space and updates the system time and later a synchronization is required to update the hardware clock.

To verify the rtc time on the hardware use the `hwclock` command.

If you want to change the hardware clock and update the system time use the command `hwclock -s` or `hwclock --hctosys`.

##  8. <a name='SendSignal'></a>Send Signal

If you want to send a signal to a thread, you can use `pthread_kill()`, although it is not semantically correct, the man page states:

> The pthread_kill() function sends the signal sig to thread, a
       thread in the same process as the caller.  The signal is
       asynchronously directed to thread.
>
> If sig is 0, then no signal is sent, but error checking is still
       performed.

A code to get the signal of a thread and verify if the thread is "alive":

```cpp	
pthread_t m_iThreadID = your_thread_id_here;
int	iStatus  = pthread_kill( m_iThreadID, 0 );
if( iStatus != 0 )  
{
    // Thread Stopped!
    std::cout << "pthread_kill Error: " << errno << std::endl;
}
```

However, it is semantically strange to use a kill function to retrieve a signal and not kill the thread, right?

Althought it sound strange, pthread_kill() is widely used and has many tutorials and examples.

If you want to use other function or to send parameters, `pthread_sigqueue()` can be used. From man page:

> The pthread_sigqueue() function performs a similar task to
       sigqueue(3), but, rather than sending a signal to a process, it
       sends a signal to a thread in the same process as the calling
       thread.
>
> The thread argument is the ID of a thread in the same process as
       the caller.  The sig argument specifies the signal to be sent.
       The value argument specifies data to accompany the signal; see
       sigqueue(3) for details.

The optional argument on man page:

> The value argument is used to specify an accompanying item of
       data (either an integer or a pointer value) to be sent with the
       signal, and has the following type:
>
>           union sigval {
>               int   sival_int;
>               void *sival_ptr;
>           };

An example with a null signal value:

```cpp	
pthread_t m_iThreadID = your_thread_id_here;
sigval_t siValue;

int	iStatus  = pthread_sigqueue( m_iThreadID, 0, siValue );
if( iStatus != 0 )  
{
    // Thread Stopped!
    std::cout << "pthread_sigqueue Error: " << errno << std::endl;
}
```

The same can be applied to processes!

The `kill()` function can be used to get the status of a function, from man page:

>The kill() system call can be used to send any signal to any
>process group or process.
>
>If pid is positive, then signal sig is sent to the process with
>the ID specified by pid.
>
>If pid equals 0, then sig is sent to every process in the process
>group of the calling process.
>
>If pid equals -1, then sig is sent to every process for which the
>calling process has permission to send signals, except for
>process 1 (init), but see below.
>
>If pid is less than -1, then sig is sent to every process in the
>process group whose ID is -pid.
>
>If sig is 0, then no signal is sent, but existence and permission
checks are still performed; this can be used to check for the
existence of a process ID or process group ID that the caller is
permitted to signal.
>
>For a process to have permission to send a signal, it must either
be privileged (under Linux: have the CAP_KILL capability in the
user namespace of the target process), or the real or effective
user ID of the sending process must equal the real or saved set-
user-ID of the target process.  In the case of SIGCONT, it
suffices when the sending and receiving processes belong to the
same session.  (Historically, the rules were different; see
NOTES.)

An example:

```cpp	
pid_t m_iProcID = your_proc_id_here;

int	iStatus  = kill( m_iProcID, 0 );
if( iStatus != 0 )  
{
    // Process Stopped!
    std::cout << "kill Error: " << errno << std::endl;
}
```

Or to use `sigqueue()`:

```cpp	
pid_t m_iProcID = your_proc_id_here;
sigval_t siValue;

int	iStatus  = sigqueue( m_iProcID, 0, siValue );
if( iStatus != 0 )  
{
    // Process Stopped!
    std::cout << "sigqueue Error: " << errno << std::endl;
}
```