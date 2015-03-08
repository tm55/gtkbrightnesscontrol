# GtkBrightnessControl
GtkBrightnessControl is a utility to control the brightness of your screen. This software is very simple and I wrote its code fast and without care, so if you want fix bugs or improve the software, you are welcome!

### Dependencies
You must manually install **xrandr** (command line tool) from repositories of your distro.

### Version
Alpha 0.1

### Screenshot
![GitHub Logo](/screenshot.jpg)

### Installation
I prepared an installation tool. You can use:
```sh
$ chmod +x GtkBrightnessControl_Installer_x86.run
$ ./GtkBrightnessControl_Installer_x86.run
```
To uninstall:
```sh
$ ./GtkBrightnessControl_Installer_x86.run uninstall
```

If you want install from sources:
```sh
$ cd SourceCode
$ ./configure
$ make
```
and move manually the binary executable with ui file in your destination folder.

### Tips
The tool has the following options:
```
--widget-mode to set widget mode
--background-color to set background color (e.g. "#FFFFFF" or "red" or "rgba(255,0,200,0.8)")
```
You can for example edit /usr/share/applications/gtkbrightnesscontrol.desktop file to add `--widget-mode` option and add the tool to your desktop panel.

### License
You can do everything you want with this tool
