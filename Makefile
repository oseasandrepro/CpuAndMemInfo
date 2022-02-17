CpuAndMemInfo: main.c mainGui.glade	
	gcc -Wall -Wextra -o CpuAndMemInfo main.c `pkg-config gtk+-3.0 --cflags --libs`
	

clean:
	rm CpuAndMemInfo
