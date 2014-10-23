all:
	git stash
	git pull
	/nobackup/jlwegene/mbed/workspace_tools/make.py -m NUCLEO_F401RE -t GCC_ARM -p 0 -d /media/NUCLEO

clean:
	rm -r /nobackup/jlwegene/mbed/build/test/*