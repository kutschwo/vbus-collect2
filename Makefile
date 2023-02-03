############
# Makefile #
############

# C source files
SOURCES = printvbus.c kbhit.c serial.c vbus.c sqlite.c mqtt.c config.c homeassistant.c main.c

# Optimization
OPT = -O3 -flto

# For Debugging
#OPT = -g

TARGET = vbus-collector

#===================================================================================

GIT_VERSION := "$(shell git describe --long --always --tags)"

CC = gcc
CFLAGS = -std=gnu11 $(OPT) -c -Wall -Ipaho.mqtt.c/src/  -DGIT_VERSION=\"$(GIT_VERSION)\"

# uncomment next line if you have
# Resol DeltaSol E Controller
# Citrin Solar CS 3.2 is identical, but branded by company Citrin Solar Moosburg (Germany)
CFLAGS += -DDS_E_CONTROLLER

# uncomment next item if you have a
# Resol DeltaSol BS Plus
#CFLAGS += -DDS_BS_PLUS
# uncomment next line for Json config file support
CFLAGS += -D__JSON__

# uncomment if you want to store values to
# a sqlite3 database
CFLAGS += -D__SQLITE__

# uncomment if you want compile
# homassistant support
CFLAGS += -D__HOASTNT__

LDFLAGS = -LcJSON/build/ -Lpaho.mqtt.c/build/src/ $(OPT) -fuse-linker-plugin -lcurl -lsqlite3 -l:libpaho-mqtt3c.a -l:libcjson.a -lpthread -lm
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

REMOVE    = rm -f
REMOVEDIR = rm -rf
CREATEDIR = mkdir -p
GET_VERSION = git describe --tags --long

# Object files directory
OBJDIR = obj

#===================================================================================

all: createdirs $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

createdirs:
	@$(CREATEDIR) $(OBJDIR)

clean:
	$(REMOVEDIR) $(OBJDIR)
	$(REMOVE) $(TARGET)



