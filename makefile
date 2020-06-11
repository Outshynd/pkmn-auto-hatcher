# Default target
all:
	make -f teensy.mk
	make -f promicro.mk
	rm -f *.bin *.eep *.elf *.lss *.map *.sym

clean:
	rm -f *.bin *.eep *.elf *.lss *.map *.sym
	rm -f ./obj/*


teensy:
	make -f teensy.mk

pro_micro:
	make -f promicro.mk