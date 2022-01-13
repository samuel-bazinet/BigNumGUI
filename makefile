all:
	g++ `fltk-config --cxxflags` BigNumGUI.cpp LLBigNums.cpp `fltk-config --ldflags` -o a.out

clear:
	rm a.out
	rm LLBigNums