# LOG

## Table of Contents

<!-- vim-markdown-toc GFM -->

- [Hardware](#hardware)
- [Install tool-chain (on Arch Linux)](#install-tool-chain-on-arch-linux)
- [Troubleshooting](#troubleshooting)

<!-- vim-markdown-toc -->

## Hardware
- [STM32 Nucleo-L152RE](https://www.st.com/en/evaluation-tools/nucleo-l152re.html)
## Install tool-chain (on Arch Linux)
- [STM32CubeMX](https://aur.archlinux.org/packages/stm32cubemx/)
- [python](https://archlinux.org/packages/extra/x86_64/python/)
- [platformio](https://docs.platformio.org/en/latest/core/installation.html)

---
>**NOTE:** 
>- Install [pip](https://archlinux.org/packages/extra/any/python-pip/) if you use `Python Package Manager` to install `platformio`. 
>- Use `sudo` to install `platformio` globally. If `platformio` is installed locally then script location should be added to `PATH` variable.

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
    - Add your username to `uucp` and `lock` groups.
    ```bash
    sudo usermod -a -G uucp $USER
    sudo usermod -a -G lock $USER
    ```
    ---
    >**NOTE:**
    >- Log out and log in again or restart for the changes to take effect.
    >- Run `groups` command to check if the user is add to `lock` and `uucp` groups
    ---
- [visual-studio-code](https://aur.archlinux.org/packages/visual-studio-code-bin/) and [PlatformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) plug-in.

## Troubleshooting
