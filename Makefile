BOOST_LIB = /usr/local/lib

CXXFLAGS = -std=c++23 -Wall -Wextra -Werror -I/usr/local/include
LDFLAGS = -L$(BOOST_LIB) -lboost_system -pthread

asio: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o asio $(LDFLAGS)

clean:
	rm -f asio

.PHONY: clean
