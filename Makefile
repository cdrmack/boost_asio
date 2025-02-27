BOOST_LIB = /usr/local/lib
BOOST_INC = /usr/local/include/boost

CXXFLAGS = -std=c++23 -Wall -Wextra -Werror
LDFLAGS = -L$(BOOST_LIB) -lboost_system -pthread

asio: main.cpp
	$(CXX) $(CXXFLAGS) -I$(BOOST_INC) main.cpp -o asio $(LDFLAGS)

clean:
	rm -f asio

.PHONY: clean
