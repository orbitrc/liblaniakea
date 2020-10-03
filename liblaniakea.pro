QT -= gui

TEMPLATE = library

INCLUDEPATH = ./include

HEADERS += \
        include/laniakea/base.h \
        include/laniakea/string.h \
        include/laniakea/vec.h \
        include/laniakea/map.h \
        include/laniakea/ini.h \
        include/laniakea/preferences.h

SOURCES += \
        src/string.c \
        src/vec.c \
        src/map.c \
        src/ini.c \
        src/preferences.c
