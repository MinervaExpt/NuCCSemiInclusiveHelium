CXX = g++
CXXFLAGS = -g -Wall -fPIC -Wno-unused-variable 
ROOTFLAGS = `root-config --cflags --glibs` -lTreePlayer -lEG -lMinuit
INCLUDE += -I$(PLOTUTILSROOT/../include)/ -I$(UNFOLDUTILSROOT)/../include/
LDLIBS += -L$(PLOTUTILSROOT) -lMAT -lMAT-MINERvA -L$(UNFOLDUTILSROOT) -lUnfoldUtils

# make a binary for every .cxx file
all : $(patsubst %.cxx, %.o, $(wildcard *.cxx))

# rule for each one
%.o : %.cxx
	$(CXX) -ggdb  $(INCLUDE) $(CXXFLAGS) $(ROOTFLAGS) -o $*.o $(LDLIBS) -c -DMNVROOT6 $*.cxx  #compile
	$(CXX) -ggdb  $(INCLUDE) $(CXXFLAGS) $(ROOTFLAGS) $(LDLIBS) -o $* $*.o ../includes/*.o   #link

clean:
	rm -f $(wildcard *.o) $(patsubst %.cxx, %, $(wildcard *.cxx))
