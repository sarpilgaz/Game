# Define project name and build directories
PROJECT_NAME := Game
BUILD_DIR := build

# Define the configuration (can be overridden from the command line)
CONFIG := Debug

# Set CMake build type based on the configuration
ifeq ($(CONFIG),Release)
	CMAKE_BUILD_TYPE := Release
else
	CMAKE_BUILD_TYPE := Debug
endif

# Default target
all: configure build

# Configure target
configure:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)

# Build target
build:
	cmake --build $(BUILD_DIR)

# Clean target
clean:
	cmake --build $(BUILD_DIR) --target clean
	rm -rf $(BUILD_DIR)
	rm -rf bin/

# Run target (optional, if you want to run the built executable)
run: build
	./bin/$(CMAKE_BUILD_TYPE)/$(PROJECT_NAME)

# Specify phony targets
.PHONY: all configure build clean run
