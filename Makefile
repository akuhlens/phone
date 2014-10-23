all:
	git stash
	git pull
	make clean
	/nobackup/jlwegene/mbed/workspace_tools/make.py -m NUCLEO_F401RE -t GCC_ARM -p 0

download:
	/nobackup/jlwegene/mbed/workspace_tools/make.py -m NUCLEO_F401RE -t GCC_ARM -p 0 -d /media/NUCLEO

clean:
	rm -fr /nobackup/jlwegene/mbed/build/test