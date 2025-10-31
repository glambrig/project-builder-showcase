# project-builder

A C++ project generator that creates modular, multi-threaded applications with automatic inter-module communication.

---

## What it does

I built this tool because I was tired of setting up the same boilerplate code for every C++ project that needed multiple components talking to each other. Instead of manually writing thread management, message queues, and module interfaces every time, this generator creates all of that automatically. I got the idea from my previous boss who had a similar system for his company. I decided to make my own.

**Core idea**: Define your modules and request types via command line, get a complete working C++ project with threading, communication, and build system already set up.

## Key features

**Project generation**
- Complete C++ project structure with CMake
- Supports up to 80+ modules running concurrently
- Thread-safe communication between all modules

**Threading system**
- Each module runs in its own thread
- Automatic thread lifecycle management
- Clean shutdown handling (no hanging processes)

**Message passing**
- Type-safe request/response system between modules
- Modules don't need to know about each other's internals
- Built-in timeout and error handling

**Performance focused**
- Minimal overhead communication
- Memory-efficient template instantiation
- Performance monitoring hooks built in

## Architecture

```
Python CLI -> Template Engine -> Generated C++ Project
     │              │                    │
Command line    File generation    Compiled application
validation      CMake setup        with running modules
```

The Python frontend handles argument parsing and template processing. The generated C++ code includes base classes, thread handlers, and a request/response framework that modules inherit from.

## Example usage

```bash
# Create an IoT gateway project
project-builder -n iot-gateway \
  -m sensorReader -m dataProcessor -m networkManager \
  -r readSensorData -r processData -r sendToCloud
```

This generates a complete project where:
- `sensorReader` module can send `readSensorData` requests
- `dataProcessor` handles the data and sends `processData` requests  
- `networkManager` receives `sendToCloud` requests
- All communication is thread-safe and typed

## Performance testing

I stress-tested this with 10 modules constantly sending requests to each other:
- Handles 10,000+ messages/second between modules
- Sub-millisecond latency for most requests
- Memory usage: ~2MB per module
- Build time stays under 30 seconds even for large projects

## Why I built this

Working on embedded systems and real-time applications, I kept running into the same patterns:
- Multiple independent components that need to communicate
- Each component should run in its own thread
- Communication needs to be reliable and fast
- Setting up all the boilerplate takes forever

This tool solves the setup problem so I can focus on the actual business logic of each module instead of writing the same threading and communication code over and over.

## Technical details

**Languages**: Python for the generator, C++17 for the runtime framework

**Build system**: CMake with automatic configuration generation

**Threading**: std::thread with RAII-based lifecycle management

**Communication**: Template-based message queues with compile-time type checking

The generated code uses modern C++ features like smart pointers, RAII, and template metaprogramming to ensure memory safety and performance.

---

I don't want the real tool to be public, so this README serves as an introduction to anyone who might be seeing `project-builder` on my CV :)
