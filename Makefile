findcomp:	ConnectedComponents.cpp PGMImageProcessor.cpp findcomp.cpp
	g++ ConnectedComponents.cpp PGMImageProcessor.cpp findcomp.cpp -o findcomp
Test:	UnixTest.cpp
	g++ ConnectedComponents.cpp PGMImageProcessor.cpp UnixTest.cpp -o UnixTest
test:
	./UnixTest


run:
	./findcomp -w new.pgm -c A.pgm -s 3 6 -t 200 chess-thresh.pgm

clean:
	rm findcomp
	rm UnixTest
	@rm -f *.o