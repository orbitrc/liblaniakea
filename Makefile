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

TARGET_DIR = target/release
default:TARGET_DIR = target/debug
test:TARGET_DIR = target/debug

VERSION_MAJOR = 0
VERSION_MINOR = 1
VERSION_PATCH = 0
SONAME = liblaniakea.so.$(VERSION_MAJOR)

default: $(OBJ)
	mkdir -p target/debug
	$(CC) -shared $(CFLAGS) -o target/debug/liblaniakea.so $^

src/%.o: src/%.c
	$(CC) -c $(CFLAGS) -fPIC -o $@ $<

release: $(OBJ)
	mkdir -p target/release
	$(CC) -shared $(CFLAGS) -Wl,-soname,$(SONAME) -o target/release/liblaniakea.so $^
	rm -rf $(TARGET_DIR)/*.so.*
	ln -s liblaniakea.so $(TARGET_DIR)/liblaniakea.so.$(VERSION_MAJOR)
	ln -s liblaniakea.so.$(VERSION_MAJOR) $(TARGET_DIR)/liblaniakea.so.$(VERSION_MAJOR).$(VERSION_MINOR)
	ln -s liblaniakea.so.$(VERSION_MAJOR).$(VERSION_MINOR) $(TARGET_DIR)/liblaniakea.so.$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)

tests/%: tests/%.c
	$(CC) $(CFLAGS) $< -Ltarget/debug -llaniakea -o $@

test: $(TEST_EXEC)
	echo -e "\t\e[1m\e[32m[test_preferences_load]\e[0m"
	LD_LIBRARY_PATH=$(TARGET_DIR) tests/test_preferences_load
	echo -e "\t\e[1m\e[32m[test_string]\e[0m"
	LD_LIBRARY_PATH=$(TARGET_DIR) tests/test_string
	echo -e "\t\e[1m\e[32m[test_vec]\e[0m"
	LD_LIBRARY_PATH=$(TARGET_DIR) tests/test_vec
	echo -e "\t\e[1m\e[32m[test_map]\e[0m"
	LD_LIBRARY_PATH=$(TARGET_DIR) tests/test_map
	echo -e "\t\e[1m\e[32m[test_ini]\e[0m"
	LD_LIBRARY_PATH=$(TARGET_DIR) tests/test_ini

clean:
	rm -rf target
	rm -rf src/*.o
