#!/bin/bash

cp -v ~/.Xresources ~/.Xresources_bak
cp -v .Xresources ~/.Xresources
sudo cp -v /usr/share/sxmo/background.jpg /usr/share/sxmo/background.jpg_bak
sudo cp -v background.jpg /usr/share/sxmo/background.jpg
cp -v userscripts/*.sh $XDG_CONFIG_HOME/sxmo/userscripts/

for file in ~/.local/share/applications/anbox/*.desktop;
do
    appName=$(cat $file | grep "Name=" | cut -d'=' -f 2)
    execCommand=$(cat $file | grep "Exec=" | cut -d'=' -f 2-)

    echo -e "#!/bin/bash\n" > $XDG_CONFIG_HOME/sxmo/$appName.sh
    echo "export EGL_PLATFORM=x11" >> $XDG_CONFIG_HOME/sxmo/$appName.sh
    echo $execCommand >> $XDG_CONFIG_HOME/sxmo/$appName.sh
done

chmod +x $XDG_CONFIG_HOME/sxmo/userscripts/*.sh
