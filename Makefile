OBJ = src/base.o \
	src/map.o \
	src/string.o \
	src/preferences.o

CFLAGS += -I./include -Wall
default:CFLAGS += -g

default: $(OBJ)
	mkdir -p target/debug
	$(CC) -shared $(CFLAGS) -o target/debug/liblaniakea.so $^

src/%.o: src/%.c
	$(CC) -c $(CFLAGS) -fPIC -o $@ $<

release: $(OBJ)
	mkdir -p target/release
	$(CC) -shared $(CFLAGS) -o target/release/liblaniakea.so $^

test:
	$(CC) $(CFLAGS) tests/test_preferences_load.c -Ltarget/debug -llaniakea -o tests/test_preferences_load
	LD_LIBRARY_PATH=target/debug tests/test_preferences_load
	$(CC) $(CFLAGS) tests/test_map.c -Ltarget/debug -llaniakea -o tests/test_map
	LD_LIBRARY_PATH=target/debug tests/test_map

clean:
	rm -rf target
	rm -rf src/*.o
