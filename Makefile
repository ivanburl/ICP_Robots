all: clean build doxygen


build: clean_build
	mkdir "build"
	cd build && cmake ../src
	cd build && cmake --build .
	mv ./build/robots ./robots

clean_build:
	rm -rf ./build

clean_doc:
	rm -rf ./docs/*

clean: clean_build clean_doc

doxygen:
	cd src && doxygen ./dconfig