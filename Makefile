OBJ = src/base.o \
	src/ini.o \
	src/map.o \
	src/preferences.o \
	src/string.o \
	src/vec.o

TEST_EXEC = tests/test_preferences \
	tests/test_map \
	tests/test_ini \
	tests/test_vec \
	tests/test_string

PREFIX ?= /usr/local

CFLAGS += -I./include -Wall
default:CFLAGS += -g

TARGET_DIR = target/release
default:TARGET_DIR = target/debug
test:TARGET_DIR = target/debug

VERSION_MAJOR = 0
VERSION_MINOR = 1
VERSION_PATCH = 0
VERSION = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)
SONAME = liblaniakea.so.$(VERSION_MAJOR)

default: $(OBJ)
	mkdir -p target/debug
	$(CC) -shared $(CFLAGS) -o target/debug/liblaniakea.so $^

src/%.o: src/%.c
	$(CC) -c $(CFLAGS) -fPIC -o $@ $<

release: $(OBJ)
	mkdir -p target/release
	$(CC) -shared $(CFLAGS) -Wl,-soname,$(SONAME) -o target/release/liblaniakea.so.$(VERSION) $^
	ln -f -s liblaniakea.so.$(VERSION) $(TARGET_DIR)/liblaniakea.so.$(VERSION_MAJOR).$(VERSION_MINOR)
	ln -f -s liblaniakea.so.$(VERSION_MAJOR).$(VERSION_MINOR) $(TARGET_DIR)/liblaniakea.so.$(VERSION_MAJOR)
	ln -f -s liblaniakea.so.$(VERSION_MAJOR) $(TARGET_DIR)/liblaniakea.so

tests/%: tests/%.c
	$(CC) $(CFLAGS) $< -Ltarget/debug -llaniakea -Wl,-rpath,'$$ORIGIN'/../$(TARGET_DIR) -o $@

test: $(TEST_EXEC)
	echo -e "\t\e[1m\e[32m[test_string]\e[0m"
	LD_LIBRARY_PATH=$(TARGET_DIR) tests/test_string
	echo -e "\t\e[1m\e[32m[test_vec]\e[0m"
	LD_LIBRARY_PATH=$(TARGET_DIR) tests/test_vec
	echo -e "\t\e[1m\e[32m[test_map]\e[0m"
	LD_LIBRARY_PATH=$(TARGET_DIR) tests/test_map
	echo -e "\t\e[1m\e[32m[test_ini]\e[0m"
	LD_LIBRARY_PATH=$(TARGET_DIR) tests/test_ini
	echo -e "\t\e[1m\e[32m[test_preferences]\e[0m"
	LD_LIBRARY_PATH=$(TARGET_DIR) tests/test_preferences

install: $(DESTDIR)/$(PREFIX)/lib $(DESTDIR)/$(PREFIX)/include
	strip target/release/liblaniakea.so.$(VERSION)
	cp -P target/release/liblaniakea.so* $(DESTDIR)/$(PREFIX)/lib/
	cp -r include/laniakea $(DESTDIR)/$(PREFIX)/include/

$(DESTDIR)/$(PREFIX)/lib:
	mkdir -p $(DESTDIR)/$(PREFIX)/lib

$(DESTDIR)/$(PREFIX)/include:
	mkdir -p $(DESTDIR)/$(PREFIX)/include

clean:
	rm -rf target
	rm -rf src/*.o
	rm $(TEST_EXEC)
