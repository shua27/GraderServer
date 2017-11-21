ifeq ($(OS),Windows_NT)
	CLEAN=rmdir /S /Q bin
	BUILD=javac -d bin -cp ".;libraries/json-simple-1.1.1.jar" -sourcepath src src/main/Main.java
else
	CLEAN=rm -rf bin
	BUILD=javac -d bin -cp ".:libraries/json-simple-1.1.1.jar" -sourcepath src src/main/Main.java
endif

all:
	$(BUILD)
	
clean:
	$(CLEAN)
	mkdir bin
	
.PHONY: all clean