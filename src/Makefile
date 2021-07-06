###
# GreenPois0n Anthrax - src/Makefile
# Copyright (C) 2010 Chronic-Dev Team
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
###
 
SDKVER = 7.1
PLATFORM = /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform
SYSROOT = /Users/spiral/Downloads/iPhoneOS7.1.sdk
CC = `xcrun -find cc`
STRIP = `xcrun -find strip`
LDID = /usr/local/bin/ldid

TARGETS = $(LAUNCHD_TARGET)

# Setupp objects for launchd
LAUNCHD_TARGET = launchd
LAUNCHD_OBJECTS = launchd.o utils.o syscalls.o
LAUNCHD_CFLAGS = -I. -arch armv6 -static -nodefaultlibs -nostdlib -isysroot$(SYSROOT) -I$(SYSROOT) -fno-stack-protector -D__DARWIN_64_BIT_INO_T=0
LAUNCHD_LDFLAGS = -arch armv6 -Wl,-e,_main -Wl,-no_pie -nostartfiles

PWD = $(shell pwd)

%.o: %.S
	$(CC) -c $(<) -o $(@) $(LAUNCHD_CFLAGS)

%.o: %.c
	$(CC) -c $(<) -o $(@) $(LAUNCHD_CFLAGS) 

all: $(TARGETS)

launchd: $(LAUNCHD_OBJECTS)
	$(CC) -o $(LAUNCHD_TARGET) $(LAUNCHD_OBJECTS) $(LAUNCHD_CFLAGS) $(LAUNCHD_LDFLAGS)
	$(STRIP) $(LAUNCHD_TARGET)
	ldid -S $(LAUNCHD_TARGET)
	
clean:
	rm -rf *.o launchd


