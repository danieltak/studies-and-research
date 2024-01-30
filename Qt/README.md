# Qt
<!-- vscode-markdown-toc -->
* 1. [General Issues](#GeneralIssues)
	* 1.1. [Locale](#Locale)
	* 1.2. [Weston non-root permission](#Westonnon-rootpermission)
* 2. [Porting from X11 to Waylandd](#PortingfromX11toWaylandd)
	* 2.1. [Problemm](#Problemm)
* 3. [Word Wrapping](#WordWrapping)
* 4. [Qt Projects](#QtProjects)
* 5. [QML](#QML)
* 6. [HMI High Performance](#HMIHighPerformance)
	* 6.1. [Color Blindness](#ColorBlindness)
* 7. [QML tips](#QMLtips)
	* 7.1. [Reset Code Model](#ResetCodeModel)
	* 7.2. [Templates](#Templates)
* 8. [Icons](#Icons)
	* 8.1. [Windows Fluent Icons](#WindowsFluentIcons)
* 9. [QML Book](#QMLBook)
* 10. [Time Picker](#TimePicker)

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

##  2. <a name='PortingfromX11toWaylandd'></a>Porting from X11 to Waylandd

 **TL;DR;**

It is not a plug & play migration, since Wayland is different from X11 and [QT Wayland Compositor](https://doc.qt.io/qt-6/qtwaylandcompositor-index.html) must be implemented.
###  2.1. <a name='Problemm'></a>Problemm

 As stated on [Open Desktop archives](https://wayland-devel.freedesktop.narkive.com/6XzmsY3c/random-window-position-with-desktop-shell), wayland uses non-deterministic positioning logic on the client shell. So the window will open on random positioning every time it is created and the client doesn’t control this positioning.

 So new QObjects without parent or QDialogs are created on random positioning. So QDialogs should be avoided.

 A question from [Qt forum (2023)](https://forum.qt.io/topic/142827/what-can-i-do-for-my-qtwidget-program-s-window-correctly-positioned-on-the-screen) and from [Free Desktop mailing list (2014)](https://lists.freedesktop.org/archives/wayland-devel/2014-August/016472.html) states that Qt Wayland Compositor needs an implementation to achieve this positioning control.

Links:

https://doc.qt.io/qt-6/wayland-and-qt.html

https://archive.fosdem.org/2014/schedule/event/porting_legacy_x11_to_wayland/

https://doc.qt.io/qt-6/qtwaylandcompositor-examples.html

https://community.kde.org/Guidelines_and_HOWTOs/Wayland_Porting_Notes

https://github.com/qt/qtwayland

https://github.com/Distrotech/qtwayland/tree/master/examples/qwindow-compositor

##  3. <a name='WordWrapping'></a>Word Wrapping

The automatic word wrapping from Qt using some flags didn't work properly on `QTableWidget` class.

The solution was to create a `QStyledItemDelegate` and to overload the sizeHint function by calculating the size by using the font size and width of each column.

A for loop is used to slice the string and to check the width of the sliced string using the current font, if it is larger than the width of the column it will slice at the last space position.

```cpp
QSize CFireListBoxDelegate::sizeHint(const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    int height = 0;
    int width = 0;

    if (true == index.isValid())
    {
        QString currentText = index.data().toString();
        QTableWidget* parent = static_cast<QTableWidget*> (this->parent());

        if (nullptr !=  parent)
        {
            QFontMetrics metrics(parent->font());
            int fontHeight = static_cast<Rhp_int32_t>(
                qCeil( (static_cast<Rhp_float32_t>((parent->font().pointSizeF()) / 0.7)) ));

            if (true == currentText.isEmpty())
            {
                currentText = "H";
            }

            QSize textSize =  metrics.size(Qt::TextSingleLine, currentText);

            int textHeight = textSize.height();
            int textWidth  = textSize.width();
            width = parent->columnWidth(index.column());

            if  (true == parent->wordWrap()
                && ( width <= textWidth ) )
            {
                QString qStrSliced;
                int iStartPos = 0;
                int iLineCount = 1;

                for( int iChar = 0; iChar <= currentText.size(); iChar++ )
                {
                    qStrSliced = currentText.sliced( iStartPos, iChar - iStartPos );
                    int iSlicedWidth = metrics.size( Qt::TextSingleLine, qStrSliced ).width();
                    if( iSlicedWidth >= width )
                    {
                        int iLastSpacePos = iStartPos + qStrSliced.lastIndexOf( QChar::Space, -1 );
                        if ( iLastSpacePos > -1 )
                        {
                            iStartPos = iLastSpacePos;
                            iChar = iLastSpacePos;
                        }
                        else
                        {
                            iStartPos = iChar;
                        }
                        iLineCount++;
                    }
                    else if( true == qStrSliced.contains( QChar::LineFeed ) )
                    {
                        iLineCount++;
                        iStartPos = iChar;
                    }
                    else
                    {
                        //
                    }
                }

                height =  iLineCount * textHeight;
            }
            else
            {
                height = ( (currentText.count("\n") + 1) * fontHeight) + 2;
            }

            height +=  m_iRowSpacing;
        }
    }

    return QSize(width, height);
}
```

##  4. <a name='QtProjects'></a>Qt Projects

- https://github.com/gamecreature/QtAwesome
- https://github.com/zhuzichu520/FluentUI
- https://github.com/Swordfish90/cool-retro-term
- https://github.com/lirios/fluid
- https://github.com/jaredtao/TaoQuick
- https://github.com/e-fever/e-fever-codebase
- https://apps.kde.org/pt-br/kapptemplate/
- https://github.com/madduci/moderncpp-project-template/tree/master

##  5. <a name='QML'></a>QML

https://develop.kde.org/docs/plasma/widget/plasma-qml-api/

https://community.kde.org/Plasma/DeveloperGuide

https://github.com/cppqtdev/Tesla

https://github.com/cppqtdev/Car-Dashboard-2

https://github.com/cppqtdev/gauge

https://github.com/MontyTheSoftwareEngineer/CoolQMLButton

https://github.com/uwerat/qskinny


https://github.com/Roniasoft/RoniaKit/tree/master

Performace

https://doc.qt.io/qt-6/qtquick-performance.html

Best Practice

https://doc.qt.io/qt-6/qtquick-bestpractices.html

https://github.com/Furkanzmc/QML-Coding-Guide

Animations

https://stackoverflow.com/questions/49113178/how-can-we-make-an-element-animate-with-glow-pulsating-effect-in-qml



##  6. <a name='HMIHighPerformance'></a>HMI High Performance

###  6.1. <a name='ColorBlindness'></a>Color Blindness

https://davidmathlogic.com/colorblind/#%23D81B60-%231E88E5-%23FFC107-%23004D40

https://davidmathlogic.com/colorblind/#%23648FFF-%23785EF0-%23DC267F-%23FE6100-%23FFB000

https://davidmathlogic.com/colorblind/#%23000000-%23E69F00-%2356B4E9-%23009E73-%23F0E442-%230072B2-%23D55E00-%23CC79A7

https://www.hmicons.com/2019/08/01/high-performance-hmi-color-palettes/

##  7. <a name='QMLtips'></a>QML tips

###  7.1. <a name='ResetCodeModel'></a>Reset Code Model

https://forum.qt.io/topic/92025/unknown-component-m300-for-custom-qml-class/3

###  7.2. <a name='Templates'></a>Templates

https://doc.qt.io/qt-6/qtquicktemplates2-index.html

##  8. <a name='Icons'></a>Icons

###  8.1. <a name='WindowsFluentIcons'></a>Windows Fluent Icons

https://learn.microsoft.com/en-us/windows/apps/design/style/segoe-fluent-icons-font

https://learn.microsoft.com/en-us/windows/apps/design/downloads/#fonts


##  9. <a name='QMLBook'></a>QML Book

https://www.qt.io/product/qt6/qml-book

##  10. <a name='TimePicker'></a>Time Picker

https://github.com/ekke/biz_data_x/blob/master/qml/popups/TimePicker.qml

https://github.com/ekke/c2gQtCon_x

https://code.qt.io/cgit/qt/qtdeclarative.git/tree/tests/auto/quick/doc/how-tos/how-to-qml/time-picker?h=6.6