# VisualStudioUninstaller
A batch script based on wmic to unstall Microsoft Visual Studio 2013.

### Introduction
Visual Studio is a high integrated software whose components may depend on:

* Its locale, such as ent, chs, ...
* Its edition, such as ultimate, professional, enterprise, ...
* Its version, such as 2008, 2010, 2012, ...
* Does it contain service packs, such as sp1, or update1, update2, ...
* The components you selected when you installed Visual Studio.
* The architecture of your Operating System, 32 or 64 bit.
* The programs already installed on your computer. For example, if you have installed .NET Framework, then VS installer will not install it again.

Each condition may need its own uninstall script. This script is specified for **default installation of VS2013 Ultimate with Update 2 Chinese Simplified**.

The script is based on **wmic**, which is a Windows tool for system management.

I listed VS2013's components by `wmic product list`. And uninstall them one by one by `wmic product where name="name" call uninstall`. I determined which component belongs to VS2013 by checking its date of installing. You can do the same to other versions of Visual Studios, and write your own script to uninstall them.

### Steps
1. Run VS2013 uninstaller in Control Panel.
2. Run this batch file to uninstall addtional components.

### Note
* Please be aware of that the uninstallation of some components **may cause other programs not functioning**. You may need to reinstall them later.
* Some components cannot be uninstalled this way. I'm not sure what causes it now. They could be uninstalled manually in Control Panel.

### Plan
I'm trying to develop a program which can auto-detect the components you have installed. Then it will generate a component list. You could select those you want to uninstall, and do the uninstallation.