all: clean build doxygen


build: clean_build
	mkdir "build"
	cd build && cmake ../src
	cd build && cmake --build .
	mv ./build/robots ./robots

clean_build:
	rm -rf ./build
	rm -f robots

clean_doc:
	rm -rf ./docs/*

clean: clean_build clean_doc

doxygen:
	cd src && doxygen ./dconfig

pack:
	zip -r xburlu00_xbuten00_50_50.zip .

run: clean_build build
	./robots