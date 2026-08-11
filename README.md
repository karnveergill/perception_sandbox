# Perception Sandbox

A lightweight C++20 sandbox for implementing and experimenting with robotics perception and estimation algorithms from scratch.

The goal of this project is to build a small, modular perception library while developing a deeper understanding of the mathematics and software architecture behind common robotics algorithms.

The project intentionally avoids large robotics frameworks such as ROS and Gazebo. Algorithms are implemented directly in C++ wherever practical so that their underlying mathematics and behavior remain explicit and easy to inspect.

## Goals

* Implement common robotics perception algorithms from scratch.
* Develop strong C++ and modern CMake practices.
* Build a reusable mathematical foundation for perception algorithms.
* Experiment with sensor models, noise, estimation, tracking, and mapping.
* Keep the core library lightweight and independent of visualization or robotics frameworks.
* Provide reproducible simulations and measurable results.
* Document the mathematics, assumptions, and failure modes of each algorithm.

## Project Structure

```text
perception-sandbox/
├── apps/          # Executable demonstrations and experiments
├── cmake/         # CMake helper modules and generated-header templates
├── docker/        # Development-container configuration
├── docs/          # Algorithm and design documentation
├── include/       # Public library headers
├── src/           # Library implementations
├── tests/         # Automated unit tests
├── CMakeLists.txt
├── Dockerfile
├── docker-compose.yml
└── version.cmake
```

## Current Status

### Core

* [x] CMake project structure
* [x] C++20 build configuration
* [x] Version generation
* [x] Linux development container
* [x] Git/GitHub integration

### Math

* [x] Vector2
* [x] Vector3
* [ ] Matrix
* [ ] Random number generation
* [ ] Gaussian distributions

### Simulation

* [ ] Vehicle state
* [ ] Motion models
* [ ] World/time simulation

### Sensors

* [ ] GPS
* [ ] IMU
* [ ] Compass
* [ ] Radar

### Estimation

* [ ] Kalman Filter
* [ ] Extended Kalman Filter
* [ ] Particle Filter

### Tracking

* [ ] Single-target tracking
* [ ] Data association
* [ ] Multi-target tracking

### Mapping

* [ ] Occupancy grid

### Visualization

* [ ] Lightweight 2D renderer
* [ ] Sensor visualization
* [ ] State-estimation visualization

## Development Environment

The project is developed inside a Linux Docker container to provide a consistent C++ development environment while allowing the source tree to remain on the host machine.

The intended development environment consists of:

* Linux
* GCC
* C++20
* CMake
* Git
* Docker

The project is designed to remain independent of the host operating system.

## Building

Start the development container from the project root:

```bash
docker compose run --rm cpp-dev
```

Inside the container, create a build directory:

```bash
mkdir -p build
cd build
cmake ..
make -j$(nproc)
```

The resulting applications can be found under:

```text
build/apps/
```

For example:

```bash
./apps/hello
```

## Running Tests

Once the test suite is configured:

```bash
cd build
ctest --output-on-failure
```

Tests are intended to validate individual library components independently from the demonstration applications.

## License

TBD
