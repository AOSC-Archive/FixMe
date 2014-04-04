fixme
=====

Qt5 frontend for MantisBT and other bug tracking system.


## Build && Install

```
export QT_SELECT=5
qmake
make
sudo make install
```

## Dependence for MantisBT backend

### for ArchLinux

```
sudo pacman -S nginx php php-fpm
sudo systemctl start php-fpm
sudo systemctl enable php-fpm
```
