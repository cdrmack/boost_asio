BOOST_LIB = /usr/local/lib

CXXFLAGS = -std=c++23 -Wall -Wextra -Werror -I/usr/local/include
LDFLAGS = -L$(BOOST_LIB) -lboost_system -pthread

SOURCES = client_server.cpp timer1.cpp timer2.cpp
TARGETS = $(SOURCES:.cpp=)

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

.PHONY: all clean
