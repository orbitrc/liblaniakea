OBJ = src/base.o \
	src/ini.o \
	src/map.o \
	src/preferences.o \
	src/string.o \
	src/vec.o

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
	$(CC) $(CFLAGS) tests/test_ini.c -Ltarget/debug -llaniakea -o tests/test_ini
	LD_LIBRARY_PATH=target/debug tests/test_ini
	$(CC) $(CFLAGS) tests/test_vec.c -Ltarget/debug -llaniakea -o tests/test_vec
	LD_LIBRARY_PATH=target/debug tests/test_vec
	$(CC) $(CFLAGS) tests/test_string.c -Ltarget/debug -llaniakea -o tests/test_string
	LD_LIBRARY_PATH=target/debug tests/test_string

clean:
	rm -rf target
	rm -rf src/*.o
