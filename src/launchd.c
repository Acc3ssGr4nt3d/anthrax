/**
  * GreenPois0n Anthrax - launchd.c
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Joshua Hill
  * Copyright (C) 2010 Dustin Howett
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <sys/stat.h>
#include <sys/wait.h>

#include "utils.h"
#include "syscalls.h"
#include "hfs_mount.h"

//#define INSTALL_AFC2
//#define INSTALL_FSTAB
#define INSTALL_Jailbreak
#define DO_UNTAR
//#define sach9
//#define INSTALL_HACKTIVATION
//#define INSTALL_UNTETHERED

#define DEVICE_UNK 0
#define DEVICE_NEW 1
#define DEVICE_OLD 2
#define DEVICE_ATV 3
#define NotiOS9
char* cache_env[] = {
		"DYLD_SHARED_CACHE_DONT_VALIDATE=1",
		"DYLD_SHARED_CACHE_DIR=/System/Library/Caches/com.apple.dyld",
		"DYLD_SHARED_REGION=private"
};

const char* fsck_hfs[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s1s1", NULL };
const char* fsck_hfs2[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s1s2", NULL };
const char* fsck_hfs_atv[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s1s1", NULL };
const char* fsck_hfs_user[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s2s1", NULL };
const char* fsck_hfs_user_old[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s2", NULL };
const char* fsck_hfs_user_atv[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s1s2", NULL };
const char* patch_dyld_new[] = { "/usr/bin/data", "-C", "/System/Library/Caches/com.apple.dyld/dyld_shared_cache_armv7", NULL };
const char* patch_dyld_old[] = { "/usr/bin/data", "-C", "/System/Library/Caches/com.apple.dyld/dyld_shared_cache_armv6", NULL };
const char* patch_kernel[] = { "/usr/bin/data", "-K", NULL };
const char* sachet[] = { "/sachet", "/Applications/Jailbreak.app", NULL };
const char* capable[] = { "/capable", NULL };
const char* afc2add[] = { "/afc2add", NULL };
const char* untarer[] = { "/untarer", NULL };
const char* tar[] = { "/mnt/bin/tar", "-xvf", "/mnt/private/var/Cydia.tar", "-C", "/mnt", NULL };
static char** envp = NULL;

int install_files(int device) {
	int ret = 0;
	//mkdir("/mnt/private", 0755);

#ifdef INSTALL_Jailbreak
		mkdir("/mnt/Applications/Jailbreak.app", 0755);

		puts("Installing Bootstrap\n");
		ret = install("/files/Jailbreak.app/Bootstrap", "/mnt/Applications/Jailbreak.app/Bootstrap", 0, 80, 0755);
		if (ret < 0) return ret;

		puts("Installing Jailbreak binary\n");
		ret = install("/files/Jailbreak.app/Jailbreak", "/mnt/Applications/Jailbreak.app/Jailbreak", 0, 80, 06755);
		if (ret < 0) return ret;
		unlink("/mnt/Applications/Jailbreak.app/Info.plist");
		puts("Installing Jailbreak Resource: Info.plist\n");
		ret = install("/files/Jailbreak.app/Info.plist", "/mnt/Applications/Jailbreak.app/Info.plist", 0, 80, 0755);
		if (ret < 0) return ret;

		puts("Installing Jailbreak Resource: icon.png\n");
		ret = install("/files/Jailbreak.app/icon.png", "/mnt/Applications/Jailbreak.app/icon.png", 0, 80, 0755);
		if (ret < 0) return ret;

		puts("Installing Jailbreak Resource: icon@2x.png\n");
		ret = install("/files/Jailbreak.app/icon@2x.png", "/mnt/Applications/Jailbreak.app/icon@2x.png", 0, 80, 0755);
		if (ret < 0) return ret;

		puts("Installing Jailbreak Resource: icon-ipad.png\n");
		ret = install("/files/Jailbreak.app/icon-ipad.png", "/mnt/Applications/Jailbreak.app/icon-ipad.png", 0, 80, 0755);
		if (ret < 0) return ret;
		puts("Installing Jailbreak Resource: PkgInfo\n");
		ret = install("/files/Jailbreak.app/PkgInfo", "/mnt/Applications/Jailbreak.app/PkgInfo", 0, 80, 0755);
		if (ret < 0) return ret;
        puts("Installing Jailbreak Resource: Cydia\n");
        // ret = install("/files/Jailbreak.app/Cydia-5.tar", "/mnt/Applications/Jailbreak.app/Cydia-5.tar", 0, 80, 0755);
        // if (ret < 0) return ret;
 		//  ret = install("/files/Jailbreak.app/Cydia-6.tar", "/mnt/Applications/Jailbreak.app/Cydia-6.tar", 0, 80, 0755);
  		// if (ret < 0) return ret;
   	ret = install("/files/Jailbreak.app/Cydia-7.tar", "/mnt/Applications/Jailbreak.app/Cydia-7.tar", 0, 80, 0755);
  		if (ret < 0) return ret;
//    ret = install("/files/Jailbreak.app/Cydia-8.tar", "/mnt/Applications/Jailbreak.app/Cydia-8.tar", 0, 80, 0755);
//    if (ret < 0) return ret;
    // ret = install("/files/Jailbreak.app/Cydia-9.tar", "/mnt/Applications/Jailbreak.app/Cydia-9.tar", 0, 80, 0755);
    // if (ret < 0) return ret;
        puts("Installing Jailbreak Resource: Fonts\n");
        ret = install("/files/Jailbreak.app/MazzardM-Bold.otf", "/mnt/Applications/Jailbreak.app/MazzardM-Bold.otf", 0, 80, 0755);
        if (ret < 0) return ret;
    ret = install("/files/Jailbreak.app/MazzardM-Medium.otf", "/mnt/Applications/Jailbreak.app/MazzardM-Medium.otf", 0, 80, 0755);
    if (ret < 0) return ret;
#endif
	return 0;
}

int main(int argc, char* argv[], char* env[]) {
	int ret = 0;
	int device = 0;
	struct stat status;

	console = open("/dev/console", O_WRONLY);
	dup2(console, 1);
	dup2(console, 2);
	envp = env;
	device = DEVICE_NEW;
	puts("Searching for disk...\n");
	while (stat("/dev/disk0s1s1", &status) != 0) {
		puts("Waiting for disk...\n");
		sleep(1);
	}
	puts("\n\n\n\n\n");
	puts("Deca5 Jailbreak - by @zzanehip\n");

	puts("Mounting filesystem...\n");
	ret = hfs_mount("/dev/disk0s1s1", "/mnt", 0);
	if(ret != 0) {
		puts("Failed to mount filesystem r/w\n");
	}
	puts("Main filesystem mounted\n");
	puts("Mounting user filesystem...\n");
	mkdir("/mnt/private/var2", 0755);
    #ifdef NotiOS9
	ret = hfs_mount("/dev/disk0s1s2", "/mnt/private/var", 0);
	if(ret != 0) {
		puts("Failed to mount filesystem r/w\n");
	}
	puts("User Filesystem mounted\n");
    #endif
	puts("Mounting devices...\n");
	if (mount("devfs", "/mnt/dev", 0, NULL) != 0) {
		puts("Unable to mount devices!\n");
		unmount("/mnt", 0);
		return -1;
	}
	puts("Devices mounted\n");
	#ifdef NotiOS9
	puts("Checking root filesystem...\n");
	ret = fsexec(fsck_hfs, env);
	if (ret != 0) {
		puts("Unable to check root filesystem!\n");
		unmount("/mnt/dev", 0);
		unmount("/mnt", 0);
		return -1;
	}
	puts("Root filesystem checked\n");
	puts("Checking user filesystem...\n");
	ret = fsexec(fsck_hfs2, env);
	puts("User filesystem checked\n");
	#endif
	if (install_files(device) != 0) {
		puts("Failed to install files!\n");
		unmount("/mnt/dev", 0);
		unmount("/mnt", 0);
		return -1;
	}
    puts("Patching fstab...\n");
    ret = unlink("/mnt/private/etc/fstab");
    ret = install("/files/fstab", "/mnt/private/etc/fstab", 0, 0, 0755);
    puts("Patching SpringBoard...\n");
	ret = unlink("/mnt/private/var/mobile/Library/Preferences/com.apple.springboard.plist");
    ret = install("/files/com.apple.springboard.plist", "/mnt/private/var/mobile/Library/Preferences/com.apple.springboard.plist", 0, 0, 0755);
	#ifdef NotiOS9
	ret = install("/files/capable", "/mnt/capable", 0, 80, 0755);
	ret = fsexec(capable, cache_env);
	ret = unlink("/mnt/capable");
	#endif
	#ifdef sach9
	unlink("/mnt/usr/libexec/rtbuddyd");
	ret = install("/files/sachet", "/mnt/usr/libexec/rtbuddyd", 0, 80, 0755);
	#endif
	puts("Installation complete\n");
	sync();

	puts("Unmounting disks...\n");
	rmdir("/mnt/private/var2");
	unmount("/mnt/private/var", 0);
	unmount("/mnt/dev", 0);
	unmount("/mnt", 0);

	puts("Flushing buffers...\n");
	sync();
	puts("Rebooting device...\n");
	close(console);
	reboot(1);

	return 0;
}
