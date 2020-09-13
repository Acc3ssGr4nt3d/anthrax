###
# GreenPois0n Anthrax - Makefile
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
 
RM = rm -rf
CP = cp
SYNC = sync
HDIUTIL = hdiutil
XPWNTOOL = /usr/local/bin/xpwntool
IMAGE3MAKER = image3maker

LAUNCHD_TARGET = src/launchd
RAMDISK_TARGET = ramdisk.dmg
ENCRYPT_TARGET = ramdisk.img3


RAMDISK_LABEL=pois0ndisk
RAMDISK_VOLUME=/Volumes/$(RAMDISK_LABEL)

#******** Please fill these in for yourself *********
#RAMDISK_IV=6800a52c8761b30b001327ea9b918653 
#RAMDISK_KEY=53e72495ea0d5dba53a1eae7529d6a95e8eb1d5d9185298c0f3323bc2c27f26f 
#RAMDISK_TEMPLATE=018-7074-092.dmg

UNAME := $(shell uname -s)

ifeq ($(UNAME),Darwin)
	TARGETS = $(LAUNCHD_TARGET) $(RAMDISK_TARGET) $(ENCRYPT_TARGET)
else
	TARGETS =
endif

all: $(TARGETS)

clean:
	$(MAKE) -C src clean
	$(RM) ramdisk.img3 ramdisk.dmg

src/launchd:
	$(MAKE) -C src launchd

ramdisk.dmg: src/launchd
	$(CP) template.dmg ramdisk.dmg
	hdiutil attach ramdisk.dmg
	hfsplus ramdisk.dmg add src/launchd /sbin/launchd
	hfsplus ramdisk.dmg addall files/ /files
	$(CP) src/launchd $(RAMDISK_VOLUME)/sbin/
	$(CP) -R files/* $(RAMDISK_VOLUME)/files/
	hdiutil detach $(RAMDISK_VOLUME)

ramdisk.img3: ramdisk.dmg
	@$(IMAGE3MAKER) -t rdsk -f ramdisk.dmg -o deca5jb.img3
