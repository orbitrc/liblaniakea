OBJ = src/base.o \
	src/ini.o \
	src/map.o \
	src/preferences.o \
	src/string.o \
	src/vec.o

TEST_EXEC = tests/test_preferences_load \
	tests/test_map \
	tests/test_ini \
	tests/test_vec \
	tests/test_string

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

tests/%: tests/%.c
	$(CC) $(CFLAGS) $< -Ltarget/debug -llaniakea -o $@

test: $(TEST_EXEC)
	LD_LIBRARY_PATH=target/debug tests/test_preferences_load
	LD_LIBRARY_PATH=target/debug tests/test_map
	LD_LIBRARY_PATH=target/debug tests/test_ini
	LD_LIBRARY_PATH=target/debug tests/test_vec
	LD_LIBRARY_PATH=target/debug tests/test_string

clean:
	rm -rf target
	rm -rf src/*.o
