.PHONY: config build

all: x86

x86: config_86 build
x64: config_64 build

config_86:
	@cmake -DCMAKE_TOOLCHAIN_FILE=toolchain-i686.cmake -G "Ninja" -S . -B build

config_64:
	@cmake -DCMAKE_TOOLCHAIN_FILE=toolchain-x86_64.cmake -G "Ninja" -S . -B build

build:
	@cmake --build build --target iso

clean:
	@rm -rf build