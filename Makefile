# variables
TARGET_DIR = test
CONFIG = Debug
PROGRAM = $(TARGET_DIR)
EXE = $(TARGET_DIR)\bin\$(CONFIG)\$(PROGRAM).exe

# faster | run this when changing/testing code
compile-run:
	cmake --build $(TARGET_DIR)
	.\$(EXE)

# slower | run this when adding/remove source files
full-build-run:
	cmake -B $(TARGET_DIR)
	cmake --build $(TARGET_DIR)
	.\$(EXE)

clean:
	rmdir /s /q .\$(TARGET_DIR)