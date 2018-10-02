
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:%.cpp=%.o)

CFLAGS = -O3
OUTFILE= test

default: debug

release: ${OBJECTS}
	g++ ${CFLAGS} ${OBJECTS} -o ${OUTFILE}

debug: CFLAGS = -g -Wall -Wextra --pedantic-errors
debug: ${OBJECTS}
	g++ ${CFLAGS} ${OBJECTS} -o ${OUTFILE}

asan: ${SOURCES}
	./ASANvars.sh
	g++ -g -fsanitize=address -fno-omit-frame-pointer ${SOURCES} -o ${OUTFILE}

%.o: %.cpp ${HEADERS}
	g++ ${CFLAGS} -c $<

.PHONY: clean
clean:
	-@rm -f ${OUTFILE}
	-@rm -f ${OBJECTS}
