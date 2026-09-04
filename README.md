# Hobby OS

Yes, I'm doing what (I think) practically every low-level programmer has done before, building an OS.  
I'm mainly doing this because a lot of great principles programming come from OS'.  
So, it is practically a learning exercise.

The goals:
- Bootable kernel.
- Shell.
- Simple UNIX-like applications.
- Allow for building and running simple user applications.

I can't say if I will or will not finish this, we'll see.

## Building

Requirements
- grub-mkrescue:  
`sudo apt install grub-common grub-pc-bin xorriso mtools`  
For Windows: WSL is **needed** in order to run `grub-mkrescue` and build the ISO.
- `x86_64-elf` cross compiler inside your path.  
Available [here](https://github.com/lordmilko/i686-elf-tools/releases), or you can build it yourself.
- `Make`, `CMake`, `Ninja` and `NASM`.

## Emulation

I recommend: [QEMU](https://www.qemu.org/).

Running
```shell
qemu-system-x86_64 -cdrom ./build/hobby_os.iso
```