# dwm - dynamic window manager

Build of dwm by [Rafael Cavalcanti](https://rafaelc.org/dev), 2020-2024. dwm is an extremely fast, small, and dynamic window manager for X.

Refer to [ansible-role-dwm](https://github.com/rc2dev/ansible-role-dwm) for the full environment.

_Notice: To cleanly integrate updates from upstream, this branch might be rebased._

## Third party patches

- adjacenttag-skipvacant
- alwayscenter
- bar height
- cyclelayouts
- fixborders
- focusonnetactive
- hide vacant tags
- noborder
- notitle
- pertag
- restartsig
- sticky
- systray and "icon size"
- tapresize
- toggle systray
- vanitygaps
- xresources

## My own patches

- Switch to corresponding tag on spawning an application.
- Prevent other tiled windows to show below transparent windows on monocle layout.
- Prevent other tiled windows to show below transparent windows on deck layout.
- Complement to `vanitygaps` patch: Allow toggling smartgaps on runtime.
- Complement to `vanitygaps` patch: Add gaps to monocle, respecting smartgaps.
- Complement to `vanitygaps` patch: Add `vanitygaps.c` to `Makefile`, so changes are detected.
- Complement to `noborder` patch: Draw borders if gaps are enabled.
- Complement to `sticky` patch: Ignore sticky flag if fullscreen. Sticking a full screen window is not useful and prevents from switching tags (see commit 38fc072).
- Complement to `alwayscenter` patch: If the floating window is sticky, place it on the bottom right instead of centering it (and take the bar into account). This allows me to watch videos on all my tags unobtrusively.
- Use more human friendly symbols for some layouts.
- Add key mask for slock's mediakey patch.
- Key and mouse bindings, window rules, aesthetics.
- Show up on display managers, with `dwm.desktop`.

## Requirements

In order to build dwm you need the Xlib header files.

## Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install

## Running dwm

Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm

## Configuration

The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
