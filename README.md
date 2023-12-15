# Zappy
A tribute to Zaphod Beeblebrox

## Project
The goal of this project is to create a network game where several teams confront on a tiles map containing
resources.
The winning team is the first one where at least 6 players who reach the maximum elevation.

More informations about the project in the [docs](docs) folder.

We had to create three binaries:
* [`zappy_server`](server): c server that generates the game's world
* [`zappy_gui`](gui): c++ graphical client; can be used to watch what happen in the world
* [`zappy_ai`](ai): python client controlling one of the world's inhabitant

### Dependencies
Langages used:
* [C++](https://en.wikipedia.org/wiki/C%2B%2B)
* [C](https://en.wikipedia.org/wiki/C_(programming_language))
* [Python](https://www.python.org/)

Build system:
* [Make](https://www.gnu.org/software/make/manual/make.html)
* [CMake](https://cmake.org/)

## Build
To build the project, follow the steps below:
```bash
# Make sure you have the necessary system packages installed
# ⚠️ The following system packages installation commands may change depending on 
# your OS. Below example is for Ubuntu 20.04
sudo apt-get update -qq
sudo apt-get install -y ninja-build clang-tidy-12 ccache
sudo update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-12 100
sudo apt-get install -y --no-install-recommends libsfml-dev
sudo apt-get install -y python3

# clone the repository
git clone git@github.com:Lukacms/Zappy.git
cd Zappy

# build all executables
make && make clean
```

Once the project is build, all the executables will be at the root of the project
```
.
├── zappy_ai
├── zappy_gui
└── zappy_server
```

### Makefile options
| Command               | Result                                          |
| --------------------- | ----------------------------------------------- |
| `make`                | Builds ```zappy_ai```, ```zappy_gui``` and ```zappy_server``` executables.          |
| `make clean`          | Cleans build dumps, keeping the executable.     |
| `make fclean`         | Removes all of the files created by the build.  |
| `make re`             | Calls `make fclean` and then `make`.            |
| `make tests_run`      | Run tests on all of the projects.               |
| `make zappy_ai`       | Build the ```zappy_ai``` executable.            |
| `make zappy_gui`      | Build the ```zappy_gui``` executable.           |
| `make zappy_server`   | Calls `make` in the `server` folder.            |

## Authors
* [Luka Camus](https://github.com/Lukacms)
* [Louis Bassagal](https://github.com/LouisBassagal)
* [Samuel Florentin](https://github.com/SamuelFlorentin)
* [Édouard Pradie](https://github.com/EdouardPradie)
* [Léopold Sallan](https://github.com/sgLeopold)
* [Ayman Tebini](https://github.com/aymteb)
