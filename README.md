# Should Launch Everything Maximized Switch (SLEMS)
This tool controls Windows' Maximize Policy, that it applies to certain hardware configurations from Windows 8 onwards, the effect being, that all applications started from the shell (mostly double-clicks in folders and `Win+R`) start with an maximized window, whether or not the window is designed for that.

## Note
You run this application at YOUR OWN RISK. This functionality may change in future versions on Windows. The source is provided only as reference, it will NOT COMPILE, unless you provide the missing components.

## Details
More detailed explanation is on: [http://nn.ai4rei.net/dev/ref/sme/](http://nn.ai4rei.net/dev/ref/sme/)
([backup](https://mk-pmb.github.io/win8-disable-launch-everything-maximized/dev-notes-backup/dev-ref-sme.html))

## System Requirements
* Windows 8+ 32-bit/64-bit

## Usage
```
slems
slems /setstate <new state>
slems /?
```

The first variant will launch the GUI, that displays the current state and allows to update it.

The second variant will set the state to enabled (1) or disabled (0) without any feedback. This is intended to run when a user logs-in as a permanent solution. If it does not work, try adding some delay (Task Scheduler allows this).

The third variant will show a compact usage help.
