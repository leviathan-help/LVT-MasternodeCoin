
Debian
====================
This directory contains files used to package leviathand/leviathan-qt
for Debian-based Linux systems. If you compile leviathand/leviathan-qt yourself, there are some useful files here.

## leviathan: URI support ##


leviathan-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install leviathan-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your leviathan-qt binary to `/usr/bin`
and the `../../share/pixmaps/leviathan128.png` to `/usr/share/pixmaps`

leviathan-qt.protocol (KDE)

