all:
	/nobackup/jlwegene/mbed/workspace_tools/make.py -m NUCLEO_F401RE -t GCC_ARM -p 0 -d /media/NUCLEO
	#git stash
	#git pull

clean:
	rm -r /nobackup/jlwegene/mbed/build/tests