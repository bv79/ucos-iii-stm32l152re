# ucos-iii-STM32L152RE

## Table of Contents

<!-- vim-markdown-toc GFM -->

- [Hardware](#hardware)
- [Install toolchain (on Arch Linux)](#install-toolchain-on-arch-linux)
- [Porting ucos-iii](#porting-ucos-iii)
- [Problems](#problems)

<!-- vim-markdown-toc -->

## Hardware
- [STM32 Nucleo-L152RE](https://www.st.com/en/evaluation-tools/nucleo-l152re.html)

## Install toolchain (on Arch Linux)
- [STM32CubeMX](https://aur.archlinux.org/packages/stm32cubemx/)
- [python](https://archlinux.org/packages/extra/x86_64/python/)
- [platformio](https://docs.platformio.org/en/latest/core/installation.html)

---
>**NOTE:** 
>- Install [pip](https://archlinux.org/packages/extra/any/python-pip/) if you use `Python Package Manager` to install `platformio`. 
>- Use `sudo` to install `platformio` globally. If `platformio` is installed locally then the script location should be added to `PATH` variable.

---
- [stlink](https://archlinux.org/packages/community/x86_64/stlink/)
    - Add [99-platformio-udev.rules](https://raw.githubusercontent.com/platformio/platformio-core/master/scripts/99-platformio-udev.rules) under `/usr/lib/udev/rules.d/` directory for PlatformIO supported boards/devices. 
    ---
    >**NOTE:**
    >- `rules.d` directory might be located in differ path depending which Linux distribution you are using.

    ---
    - Restart `udev`
    ```bash
    sudo udevadm control --reload-rules
    sudo udevadm trigger
    ```
    - Plug `STM32 Nucleo L152RE` in and find info of the device. For example: 
    ```bash
    stat /dev/ttyACM0 
    ```
    ```
      File: /dev/ttyACM0
      Size: 0               Blocks: 0          IO Block: 4096   character special file
    Device: 5h/5d   Inode: 870         Links: 1     Device type: a6,0
    Access: (0666/crw-rw-rw-)  Uid: (    0/    root)   Gid: (  987/    uucp)
    Access: 2021-04-07 15:01:25.817096629 +0300
    Modify: 2021-04-07 15:01:25.817096629 +0300
    Change: 2021-04-07 15:01:25.817096629 +0300
     Birth: -
    ```
    - As in the above output, the device belongs to `uucp` group so you need to add you to `uucp` group
    ```bash
    sudo usermod -a -G uucp $USER
    ```
    ---
    >**NOTE:**
    >- Log out and log in again or restart for the changes to take effect.
    >- Run `groups` command to check if the user is add to `lock` and `uucp` groups
    ---
- [visual-studio-code](https://aur.archlinux.org/packages/visual-studio-code-bin/) and [PlatformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) plug-in.

## Porting ucos-iii
- Copy and modify `startup_stm32l152xe.S` file
- Fix compiling errors:
	- Enable `CPU_CFG_NVIC_PRIO_BITS` in `cpu_cfg.h` file to fix following error:
![](attachments/nvic-prio-bits-error.png)
	- Change `#include  "../../../Source/os.h"`  in `os_cpu_c.c` file to `#include "os.h"` to fix following error:
![](attachments/include-os-header-error.png)

## Problems
- Can't debug when PC13 is enabled. Solutions:
	- Call any `HAL_GPIO_xxx()` function
	- Disable pin `PC13`

