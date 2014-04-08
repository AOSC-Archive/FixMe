## Testcase

### inotifywait

```
sudo pacman -S inotify-tools

inotifywait -m -r /var/log/journal/
```

### segfault

```
make
./segfault
```

inotifywait shown as below:

```
/var/log/journal/76b0b0b065044a64bf79fe61240a30c8/ MODIFY system.journal
/var/log/journal/76b0b0b065044a64bf79fe61240a30c8/ MODIFY system.journal
...
```
