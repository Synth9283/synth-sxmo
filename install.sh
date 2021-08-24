#!/bin/bash

cp -v ~/.Xresources ~/.Xresources_bak
cp -v .Xresources ~/.Xresources
sudo cp -v /usr/share/sxmo/background.jpg /usr/share/sxmo/background.jpg_bak
sudo cp -v background.jpg /usr/share/sxmo/background.jpg
chmod +x userscripts/*.sh
cp -v userscripts/*.sh $XDG_CONFIG_HOME/sxmo/userscripts/
