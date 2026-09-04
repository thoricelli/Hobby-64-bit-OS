.PHONY: config build

all: config build

config:
	@cmake -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake -G "Ninja" -S . -B build

build:
	@cmake --build build --target iso