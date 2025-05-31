# SGLauncher
Simple GTK Logout Menu

Features:

- [x] Window positioning
- [x] Grid, single row and single column layouts
- [x] Custom icon size
- [x] Toggleable icons and text
- [x] Set custom commands
- [x] Custom CSS

## Dependencies
- GTK 3
- [GTK Layer Shell](https://github.com/wmww/gtk-layer-shell) (if building for Wayland)
- [SGXPos](https://codeberg.org/ItsZariep/SGXPos) (if building for X11)

## Building

```bash
make
```

You can also build only one backend:

* For **X11** only:

  ```bash
  make X11=1
  ```

* For **Wayland** only:

  ```bash
  make WAYLAND=1
  ```
 
* Without libs

  ```bash
  make LIBS_NOLIBS=1
  ```

> [!NOTE]  
> Without libs, window position settings are naturally unavailable.
---

## Installation

```bash
sudo make install
```