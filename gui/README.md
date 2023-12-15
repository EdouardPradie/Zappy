# Zappy - Gui

A tribute to Zaphod Beeblebrox

## Project
Our goal was to create a graphical client in order to show how IA move in the world of Trantor.

We had the following objectives:
* Represent what is happening on the server
* Create connection with sockets

### Dependencies
The GUI part is done in [C++](https://en.wikipedia.org/wiki/C%2B%2B), and build using [CMake](https://cmake.org/). Moreover, it uses [SFML](https://www.sfml-dev.org/), a multimedia library.

### Documentation

To have more information, look at the [docs](../docs) folder.

### Build project
Assuming you've already cloned the Zappy project following the [directories](../)
```bash
# Make sure you have the necessary system packages installed
# ⚠️ The following system packages installation commands may change depending on 
# your OS. Below example is for Ubuntu 20.04
sudo apt-get update -qq
sudo apt-get install -y ninja-build clang-tidy-12 ccache
sudo update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-12 100
sudo apt-get install -y --no-install-recommends libsfml-dev

# compile the project with fast building tool
./compile.sh --ninja
```

Once the project is build, you have (roughly) the following architecture:
```
..
├── gui
│   ├── build
│   │   └── zappy_gui-core.so
│   ├── src
│   └── tests
└── zappy_gui
```

### Launch GUI
After building project, here is the output of the help:
```bash
$ > ./zappy_gui -h
USAGE: ./zappy_gui <SERVER_IP> <SERVER_PORT>
    SERVER_IP: IP Adress of the zappy server
    SERVER_PORT: Port of the zappy server
```
You must precise:
* the `server_ip`, which is often *localhost*, or 127.0.0.1
* the `server_port`, which is the port given to the server to connect to

#### Interface
The Gui is divided in two parts, the first one is the world map which shows players and tiles.
![](https://cdn.discordapp.com/attachments/1105893572064067705/1120276134265880617/image.png)
The second one is the inventory of tiles or players.
![](https://media.discordapp.net/attachments/1105893572064067705/1120276345272926269/image.png?width=1300&height=686)
To see the inventory of players or tiles, you have to click on them.
