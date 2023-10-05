CXXFLAGS = -std=c++17
sources = median.cpp tdd.cpp

test: tdd
	./tdd

tdd: $(sources:.cpp=.o)
	$(CXX) $(CXXFLAGS) -o $@ $^

include $(sources:.cpp=.d)

%.d: %.cpp
	@set -e; rm -f $@; \
		$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

clean:
	rm *.o *.d tdd
