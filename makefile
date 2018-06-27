

objects = obj/kernel.o obj/loader.o obj/gdt.o

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	i686-elf-gcc -c -o $@ $< -ffreestanding -fno-exceptions -fno-rtti
	
obj/%.o: src/%.s
	mkdir -p $(@D)
	i686-elf-as  -o $@ $<
	
kernel.bin: Link.ld $(objects)
	echo $(objects)
	i686-elf-gcc -T $< -o $@ -nostdlib -lgcc $(objects)
	
projectJupiter.iso: kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "projectJupiter" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/kernel.bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=projectJupiter.iso iso
	rm -rf iso
	
run: projectJupiter.iso
	(killall VirtualBox && sleep 1) || true
	VirtualBox --startvm 'Project Jupiter' &
	
.PHONY: clean
clean:
	rm -rf obj kernel.bin projectJupiter.iso
