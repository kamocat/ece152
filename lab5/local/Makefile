# Detect platform
UNAME = $(shell uname)

ifeq ($(UNAME),Linux)
ENV=unix
endif

ifeq ($(UNAME),Darwin)
ENV=unix
endif

ifndef ENV
ENV=windows
endif

ifeq ($(ENV),unix)
CC = g++
BOOSTFLAGS = -lboost_system -lpthread
else
CC = g++
BOOSTFLAGS = -lboost_system -lws2_32 -D _WIN32_WINNT=0x0501
endif

all:
	$(CC) lab5.cpp -Wall $(BOOSTFLAGS) -o lab5

clean:
	rm -f *.exe
	rm -f *.out
	rm -f *.o
	rm -f lab5
	
