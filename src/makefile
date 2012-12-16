OBJ = meshviewer.o viewer.o ylpfile.o scomplex.o
CC = gcc
CFLAGS = -Wextra -Wall -O2 -I"D:\Develop\MinGW\freeglut\include" -I"C:\Yuhta\Develop\MinGW\freeglut\include" -D FREEGLUT_STATIC
#LDFLAGS = -Wl,--subsystem,windows
LDLIBS = -L"D:\Develop\MinGW\freeglut\lib" -lfreeglut_static -lopengl32 -lglu32 -L"C:\Yuhta\Develop\MinGW\freeglut\lib" -lwinmm -lgdi32

meshviewer: $(OBJ)

meshviewer.o: viewer.h ylpfile.h scomplex.h
viewer.o: viewer.h scomplex.h
ylpfile.o: ylpfile.h scomplex.h
scomplex.o: scomplex.h

.PHONY: clean
clean:
	del $(OBJ)
