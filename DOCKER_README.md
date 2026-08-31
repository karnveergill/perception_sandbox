## Development Environment

The project uses Docker to provide a reproducible Linux C++ development environment. The container includes the compiler, CMake, Git, debugging tools, and SDL2 development libraries.

The source tree remains on the host machine and is mounted into the container, allowing files to be edited normally while all C++ development tools run inside Linux.

### Prerequisites

Install:

* Docker
* Docker Compose

Verify Docker is available:

```bash
docker --version
docker compose version
```

### Build the Development Image

From the project root:

```bash
docker compose build
```

The Docker image contains the project's Linux development dependencies, including:

* GCC
* CMake
* Git
* GDB
* OpenSSH client
* SDL2 development libraries

The image only needs to be rebuilt when the Dockerfile or development dependencies change.

### Start the Development Container

Start an interactive development container with:

```bash
docker compose run --rm cpp-dev
```

The `--rm` option automatically removes the temporary container when the shell exits.

Once inside the container, the project should be available at:

```bash
cd ~/Development/perception-sandbox
```

### Build the Project

From the project directory:

```bash
mkdir -p build
cd build
cmake ..
make
```

Or, after the initial configuration:

```bash
make
```

Executables and libraries are generated inside the `build/` directory.

### Verify SDL2

SDL2 is installed as part of the Docker image.

Verify the installation with:

```bash
sdl2-config --version
```

You can also verify that the development package is available:

```bash
pkg-config --modversion sdl2
```

The SDL2 headers should be available at:

```bash
/usr/include/SDL2/
```

### Rebuilding After Dockerfile Changes

If the Dockerfile is modified, rebuild the image:

```bash
docker compose build
```

Then start a new container:

```bash
docker compose run --rm cpp-dev
```

For a completely clean rebuild without using Docker's build cache:

```bash
docker compose build --no-cache
```

Use `--no-cache` only when necessary. A normal `docker compose build` is significantly faster because Docker can reuse unchanged build layers.

### Starting a Persistent Development Container

For normal development, the following is also available:

```bash
docker compose up -d
```

Then enter the running container:

```bash
docker compose exec cpp-dev bash
```

When finished:

```bash
docker compose down
```

For this project, `docker compose run --rm cpp-dev` is generally the simplest workflow when an interactive shell is all that is needed.

### Development Workflow

A typical development session is:

```bash
docker compose run --rm cpp-dev
```

Then inside the container:

```bash
cd ~/Development/perception-sandbox

cd build
cmake ..
make
```

Run an application:

```bash
./apps/hello
```

or:

```bash
./apps/math_demo
```

Source files are stored on the host machine, so changes made inside or outside the container are immediately reflected in the project directory.

### Cleaning the Build

The CMake build directory can safely be removed and regenerated:

```bash
rm -rf build
mkdir build
cd build
cmake ..
make
```

The `build/` directory contains generated files and should not be committed to Git.

### Docker Environment vs. Project Source

The Docker image provides the development environment:

```text
Docker image
├── Ubuntu
├── GCC
├── CMake
├── Git
├── GDB
├── SDL2
└── development tools
```

The project source remains on the host:

```text
perception-sandbox/
├── apps/
├── include/
├── src/
├── tests/
├── docs/
└── CMakeLists.txt
```

Docker Compose connects the two by mounting the project directory into the container.
