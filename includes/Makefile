CXX = g++
CXXFLAGS = -g -Wall -fPIC
ROOTFLAGS = `root-config --cflags --glibs --libs` -lTreePlayer -lEG -lMinuit 
INCLUDE += -I$(PLOTUTILSROOT/../include)/  -I$(UNFOLDUTILSROOT)/../include/
LDLIBS += -L$(PLOTUTILSROOT) -lMAT -lMAT-MINERvA -L$(UNFOLDUTILSROOT) -lUnfoldUtils

# make a binary for every .cxx file
all : $(patsubst %.cxx, %.o, $(wildcard *.cxx))

# rule for each one
%.o : %.cxx
	$(CXX) $(INCLUDE) $(CXXFLAGS) $(ROOTFLAGS) -o $*.o $(LDLIBS) -c -DMNVROOT6  $*.cxx #compile
#	$(CXX) $(INCLUDE) $(CXXFLAGS) $(ROOTFLAGS) $(LDLIBS) -o $* $*.o        #link

clean:
	rm -f $(wildcard *.o) $(patsubst %.cxx, %, $(wildcard *.cxx))
