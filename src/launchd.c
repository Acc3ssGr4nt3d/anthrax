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


#include <dirent.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/wait.h>

#include <fcntl.h>

#include "utils.h"
#include "syscalls.h"
#include "hfs_mount.h"

/*
char* cache_env[] = {
		"DYLD_SHARED_CACHE_DONT_VALIDATE=1",
		"DYLD_SHARED_CACHE_DIR=/System/Library/Caches/com.apple.dyld",
		"DYLD_SHARED_REGION=private"
};
*/

static char** envp = NULL;

void log_file(char *path, char *str) {
	int fh;

	if(access(path, 0) != 0) 
		fh = open(path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	else 
		fh = open(path, O_WRONLY | O_APPEND);

	int size = strlen(str);

	write(fh, str, size);
	close(fh);

	chown(path, 501, 20);
	chmod(path, 0755);
}

void jb_log(char *str) {
	char *path = "/mnt/var/mobile/Media/blackb0x_install.log";
	log_file(path, str);
}

void create_directory(char *path, int chmdd, int uid, int gid) {
	mkdir(path, chmod);
	chown(path, uid, gid);
}

void create_directories() {

	create_directory("/mnt/Library/LaunchDaemons", 755, 501, 20);
	create_directory("/mnt/private/etc/alternatives", 755, 501, 20);
	create_directory("/mnt/private/etc/apt", 755, 501, 20);
	create_directory("/mnt/private/etc/apt/apt.conf.d", 755, 501, 20);
	create_directory("/mnt/private/etc/apt/preferences.d", 755, 501, 20);
	create_directory("/mnt/private/etc/apt/sources.list.d", 755, 501, 20);
	create_directory("/mnt/private/etc/apt/trusted.gpg.d", 755, 501, 20);
	create_directory("/mnt/private/etc/default", 755, 501, 20);
	create_directory("/mnt/private/etc/dpkg", 755, 501, 20);
	create_directory("/mnt/private/etc/dpkg/origins", 755, 501, 20);
	create_directory("/mnt/private/etc/pam.d", 755, 501, 20);
	create_directory("/mnt/private/etc/profile.d", 755, 501, 20);
	create_directory("/mnt/private/etc/ssh", 755, 501, 20);
	create_directory("/mnt/private/etc/ssl", 755, 501, 20);
	create_directory("/mnt/private/etc/ssl/certs", 755, 501, 20);
	create_directory("/mnt/private/etc/ssl/private", 755, 501, 20);
	create_directory("/mnt/private/var/backups", 755, 501, 20);
	create_directory("/mnt/private/var/cache", 755, 501, 20);
	create_directory("/mnt/private/var/cache/apt", 755, 501, 20);
	create_directory("/mnt/private/var/cache/apt/archives", 755, 501, 20);
	create_directory("/mnt/private/var/cache/apt/archives/partial", 755, 501, 20);
	create_directory("/mnt/private/var/cache/findutils", 755, 501, 20);
	create_directory("/mnt/private/var/lib", 755, 501, 20);
	create_directory("/mnt/private/var/lib/apt", 755, 501, 20);
	create_directory("/mnt/private/var/lib/apt/lists", 755, 501, 20);
	create_directory("/mnt/private/var/lib/apt/lists/partial", 755, 501, 20);
	create_directory("/mnt/private/var/lib/apt/periodic", 755, 501, 20);
	create_directory("/mnt/private/var/lib/cydia", 755, 501, 20);
	create_directory("/mnt/private/var/lib/dpkg", 755, 501, 20);
	create_directory("/mnt/private/var/lib/dpkg/alternatives", 755, 501, 20);
	create_directory("/mnt/private/var/lib/dpkg/info", 755, 501, 20);
	create_directory("/mnt/private/var/lib/dpkg/parts", 755, 501, 20);
	create_directory("/mnt/private/var/lib/dpkg/updates", 755, 501, 20);
	create_directory("/mnt/private/var/lib/misc", 755, 501, 20);
	create_directory("/mnt/private/var/local", 755, 501, 20);
	create_directory("/mnt/private/var/lock", 755, 501, 20);
	create_directory("/mnt/private/var/log/apt", 755, 501, 20);
	create_directory("/mnt/private/var/root/Media", 755, 501, 20);
	create_directory("/mnt/private/var/run", 755, 501, 20);
	create_directory("/mnt/usr/etc", 755, 501, 20);
	create_directory("/mnt/usr/games", 755, 501, 20);
	create_directory("/mnt/usr/include", 755, 501, 20);
	create_directory("/mnt/usr/include/apt-pkg", 755, 501, 20);
	create_directory("/mnt/usr/include/curl", 755, 501, 20);
	create_directory("/mnt/usr/include/ncursesw", 755, 501, 20);
	create_directory("/mnt/usr/include/openssl", 755, 501, 20);
	create_directory("/mnt/usr/include/pam", 755, 501, 20);
	create_directory("/mnt/usr/include/readline", 755, 501, 20);
	create_directory("/mnt/usr/lib/_ncurses", 755, 501, 20);
	create_directory("/mnt/usr/lib/apt", 755, 501, 20);
	create_directory("/mnt/usr/lib/apt/methods", 755, 501, 20);
	create_directory("/mnt/usr/lib/dpkg", 755, 501, 20);
	create_directory("/mnt/usr/lib/dpkg/methods", 755, 501, 20);
	create_directory("/mnt/usr/lib/dpkg/methods/apt", 755, 501, 20);
	create_directory("/mnt/usr/lib/engines", 755, 501, 20);
	create_directory("/mnt/usr/lib/gettext", 755, 501, 20);
	create_directory("/mnt/usr/lib/pam", 755, 501, 20);
	create_directory("/mnt/usr/lib/pkgconfig", 755, 501, 20);
	create_directory("/mnt/usr/lib/ssl", 755, 501, 20);
	create_directory("/mnt/usr/lib/ssl/misc", 755, 501, 20);
	create_directory("/mnt/usr/libexec/cydia", 755, 501, 20);
	create_directory("/mnt/usr/libexec/gnupg", 755, 501, 20);
	create_directory("/mnt/usr/share/bigboss", 755, 501, 20);
	create_directory("/mnt/usr/share/bigboss/icons", 755, 501, 20);
	create_directory("/mnt/usr/share/bigboss/icons/.svn", 755, 501, 20);
	create_directory("/mnt/usr/share/bigboss/icons/.svn/prop-base", 755, 501, 20);
	create_directory("/mnt/usr/share/bigboss/icons/.svn/props", 755, 501, 20);
	create_directory("/mnt/usr/share/bigboss/icons/.svn/text-base", 755, 501, 20);
	create_directory("/mnt/usr/share/bigboss/icons/.svn/tmp", 755, 501, 20);
	create_directory("/mnt/usr/share/bigboss/icons/.svn/tmp/prop-base", 755, 501, 20);
	create_directory("/mnt/usr/share/bigboss/icons/.svn/tmp/props", 755, 501, 20);
	create_directory("/mnt/usr/share/bigboss/icons/.svn/tmp/text-base", 755, 501, 20);
	create_directory("/mnt/usr/share/dict", 755, 501, 20);
	create_directory("/mnt/usr/share/dpkg", 755, 501, 20);
	create_directory("/mnt/usr/share/dpkg/origins", 755, 501, 20);
	create_directory("/mnt/usr/share/gnupg", 755, 501, 20);
	create_directory("/mnt/usr/share/keyrings", 755, 501, 20);
	create_directory("/mnt/usr/share/tabset", 755, 501, 20);
	create_directory("/mnt/usr/share/terminfo", 755, 501, 20);
	create_directory("/mnt/usr/share/terminfo/a", 755, 501, 20);
	create_directory("/mnt/usr/share/terminfo/c", 755, 501, 20);
	create_directory("/mnt/usr/share/terminfo/d", 755, 501, 20);
	create_directory("/mnt/usr/share/terminfo/E", 755, 501, 20);
	create_directory("/mnt/usr/share/terminfo/l", 755, 501, 20);
	create_directory("/mnt/usr/share/terminfo/m", 755, 501, 20);
	create_directory("/mnt/usr/share/terminfo/p", 755, 501, 20);
	create_directory("/mnt/usr/share/terminfo/r", 755, 501, 20);
	create_directory("/mnt/usr/share/terminfo/s", 755, 501, 20);
	create_directory("/mnt/usr/share/terminfo/v", 755, 501, 20);
	create_directory("/mnt/usr/share/terminfo/x", 755, 501, 20);

}

int clone_directory(char *src, char *dst, int uid, int gid, int chmod, int recursive) {

	char *ebuf, *cp; 
	long base;
	size_t bufsize;
	int fd, nbytes;
	struct stat sb;
	struct dirent *dp;

	jb_log("Cloning directory\n");

	if ((fd = open(src, 0)) < 0) {
		jb_log("cannot open src\n");
		return -1;
	}

	if (fstat(fd, &sb) < 0) {
		jb_log("fstat failed\n");
		return -1;
	}

	bufsize = sb.st_size;
	if (bufsize < sb.st_blksize) bufsize = sb.st_blksize;

	char buf[0x1000] = {};

	while ((nbytes = getdirentries(fd, buf, bufsize, &base)) > 0) {

		ebuf = buf + nbytes;
		cp = buf;
		while (cp < ebuf) {

			dp = (struct dirent *)cp;

			cp += dp->d_reclen;

			if(dp->d_type == DT_LNK) continue;
			if((dp->d_type != DT_REG) && (dp->d_type != DT_DIR)) continue;
			if(!strlen(dp->d_name)) continue;
			if(dp->d_name[0] == '.') continue;

			#define CONCAT(buf, str) memcpy(buf + strlen(buf), str, strlen(str)+1)

			char sPathBufSrc[0x1000] = {};
			char sPathBufDst[0x1000] = {};
			CONCAT(sPathBufSrc, src);
			CONCAT(sPathBufSrc, dp->d_name);

			CONCAT(sPathBufDst, dst);
			CONCAT(sPathBufDst, dp->d_name);

			if(dp->d_type == DT_DIR) {

				if(recursive == 1) {

					jb_log("Entering new directory\n");

					CONCAT(sPathBufSrc, "/");
					CONCAT(sPathBufDst, "/");

					jb_log(sPathBufSrc);
					jb_log(" -> ");
					jb_log(sPathBufDst);
					jb_log("\n");

					clone_directory(sPathBufSrc, sPathBufDst, uid, gid, chmod, recursive);

				}

				continue;
			}

			#undef CONCAT

			jb_log(sPathBufSrc);
			jb_log(" -> ");
			jb_log(sPathBufDst);
			jb_log("\n");

			install(sPathBufSrc, sPathBufDst, uid, gid, chmod);

		}
	}

	if (nbytes < 0) {
		jb_log("failed to get directories\n");
		return -1;
	}

	return 1;
}


void create_symlinks() {

	symlink("bzip2", "/mnt/bin/bunzip2");
	symlink("bzip2", "/mnt/bin/bzcat");
	symlink("/usr/bin/less", "/mnt/bin/more");
	symlink("/sbin/ping6", "/mnt/bin/ping6");
	symlink("bash", "/mnt/bin/sh");
	symlink("reboot", "/mnt/sbin/halt");
	symlink("/bin/ping", "/mnt/sbin/ping");
	symlink("tic", "/mnt/usr/bin/captoinfo");
	symlink("chpass", "/mnt/usr/bin/chfn");
	symlink("/bin/chown", "/mnt/usr/bin/chown");
	symlink("chpass", "/mnt/usr/bin/chsh");
	symlink("tic", "/mnt/usr/bin/infotocap");
	symlink("lzma", "/mnt/usr/bin/lzcat");
	symlink("lzdiff", "/mnt/usr/bin/lzcmp");
	symlink("lzgrep", "/mnt/usr/bin/lzegrep");
	symlink("lzgrep", "/mnt/usr/bin/lzfgrep");
	symlink("lzmore", "/mnt/usr/bin/lzless");
	symlink("/bin/mktemp", "/mnt/usr/bin/mktemp");
	symlink("less", "/mnt/usr/bin/more");
	symlink("/bin/ping", "/mnt/usr/bin/ping");
	symlink("tset", "/mnt/usr/bin/reset");
	symlink("./ssh", "/mnt/usr/bin/slogin");
	symlink("/bin/tar", "/mnt/usr/bin/tar");
	symlink("lzma", "/mnt/usr/bin/unlzma");
	symlink("curses.h", "/mnt/usr/include/ncurses.h");
	symlink("curses.h", "/mnt/usr/include/ncursesw/ncurses.h");
	symlink("libncurses.5.dylib", "/mnt/usr/lib/_ncurses/libcurses.dylib");
	symlink("libncurses.5.dylib", "/mnt/usr/lib/_ncurses/libncurses.dylib");
	symlink("gzip", "/mnt/usr/lib/apt/methods/bzip2");
	symlink("gzip", "/mnt/usr/lib/apt/methods/lzma");
	symlink("rsh", "/mnt/usr/lib/apt/methods/ssh");
	symlink("libapr-1.0.3.3.dylib", "/mnt/usr/lib/libapr-1.0.dylib");
	symlink("libapr-1.0.3.3.dylib", "/mnt/usr/lib/libapr-1.dylib");
	symlink("libapt-inst.dylib.1.1.0", "/mnt/usr/lib/libapt-inst.dylib");
	symlink("libapt-inst.dylib.1.1.0", "/mnt/usr/lib/libapt-inst.dylib.1.1");
	symlink("libapt-pkg.dylib.4.6.0", "/mnt/usr/lib/libapt-pkg.dylib");
	symlink("libapt-pkg.dylib.4.6.0", "/mnt/usr/lib/libapt-pkg.dylib.4.6");
	symlink("libasprintf.0.0.0.dylib", "/mnt/usr/lib/libasprintf.0.dylib");
	symlink("libasprintf.0.0.0.dylib", "/mnt/usr/lib/libasprintf.dylib");
	symlink("libcrypto.0.9.8.dylib", "/mnt/usr/lib/libcrypto.dylib");
	symlink("libcurl.4.dylib", "/mnt/usr/lib/libcurl.dylib");
	symlink("libdb-4.6.dylib", "/mnt/usr/lib/libdb-4.dylib");
	symlink("libdb-4.6.dylib", "/mnt/usr/lib/libdb.dylib");
	symlink("libform.5.dylib", "/mnt/usr/lib/libform.dylib");
	symlink("libformw.5.dylib", "/mnt/usr/lib/libformw.dylib");
	symlink("libgettextlib-0.17.dylib", "/mnt/usr/lib/libgettextlib.dylib");
	symlink("libgettextpo.0.4.0.dylib", "/mnt/usr/lib/libgettextpo.0.dylib");
	symlink("libgettextpo.0.4.0.dylib", "/mnt/usr/lib/libgettextpo.dylib");
	symlink("libgettextsrc-0.17.dylib", "/mnt/usr/lib/libgettextsrc.dylib");
	symlink("libhistory.6.0.dylib", "/mnt/usr/lib/libhistory.5.2.dylib");
	symlink("libhistory.5.2.dylib", "/mnt/usr/lib/libhistory.5.dylib");
	symlink("libhistory.6.0.dylib", "/mnt/usr/lib/libhistory.6.dylib");
	symlink("libhistory.6.0.dylib", "/mnt/usr/lib/libhistory.dylib");
	symlink("libintl.8.0.2.dylib", "/mnt/usr/lib/libintl.8.dylib");
	symlink("libintl.8.0.2.dylib", "/mnt/usr/lib/libintl.dylib");
	symlink("liblzmadec.0.0.0.dylib", "/mnt/usr/lib/liblzmadec.0.dylib");
	symlink("liblzmadec.0.0.0.dylib", "/mnt/usr/lib/liblzmadec.dylib");
	symlink("libmenu.5.dylib", "/mnt/usr/lib/libmenu.dylib");
	symlink("libmenuw.5.dylib", "/mnt/usr/lib/libmenuw.dylib");
	symlink("libncursesw.5.dylib", "/mnt/usr/lib/libncursesw.dylib");
	symlink("libpam.1.dylib", "/mnt/usr/lib/libpam.1.0.dylib");
	symlink("libpam.1.dylib", "/mnt/usr/lib/libpam.dylib");
	symlink("libpam.1.dylib", "/mnt/usr/lib/libpam_misc.1.dylib");
	symlink("libpam.1.dylib", "/mnt/usr/lib/libpam_misc.dylib");
	symlink("libpam.1.dylib", "/mnt/usr/lib/libpamc.1.dylib");
	symlink("libpam.1.dylib", "/mnt/usr/lib/libpamc.dylib");
	symlink("libpanel.5.dylib", "/mnt/usr/lib/libpanel.dylib");
	symlink("libpanelw.5.dylib", "/mnt/usr/lib/libpanelw.dylib");
	symlink("libpcre.0.0.1.dylib", "/mnt/usr/lib/libpcre.0.dylib");
	symlink("libpcre.0.0.1.dylib", "/mnt/usr/lib/libpcre.dylib");
	symlink("libpcrecpp.0.0.0.dylib", "/mnt/usr/lib/libpcrecpp.0.dylib");
	symlink("libpcrecpp.0.0.0.dylib", "/mnt/usr/lib/libpcrecpp.dylib");
	symlink("libpcreposix.0.0.0.dylib", "/mnt/usr/lib/libpcreposix.0.dylib");
	symlink("libpcreposix.0.0.0.dylib", "/mnt/usr/lib/libpcreposix.dylib");
	symlink("libreadline.6.0.dylib", "/mnt/usr/lib/libreadline.5.2.dylib");
	symlink("libreadline.5.2.dylib", "/mnt/usr/lib/libreadline.5.dylib");
	symlink("libreadline.6.0.dylib", "/mnt/usr/lib/libreadline.6.dylib");
	symlink("libreadline.6.0.dylib", "/mnt/usr/lib/libreadline.dylib");
	symlink("libssl.0.9.8.dylib", "/mnt/usr/lib/libssl.dylib");
	symlink("/etc/ssl/certs", "/mnt/usr/lib/ssl/certs");
	symlink("/etc/ssl/openssl.cnf", "/mnt/usr/lib/ssl/openssl.cnf");
	symlink("/etc/ssl/private", "/mnt/usr/lib/ssl/private");
	symlink("../share/terminfo", "/mnt/usr/lib/terminfo");
	symlink("/bin/chown", "/mnt/usr/sbin/chown");
	symlink("ansi-m", "/mnt/usr/share/terminfo/a/ansi-mono");
	symlink("cons25l1-m", "/mnt/usr/share/terminfo/c/cons25-iso-m");
	symlink("cons25l1", "/mnt/usr/share/terminfo/c/cons25-iso8859");
	symlink("cons25r", "/mnt/usr/share/terminfo/c/cons25-koi8-r");
	symlink("cons25r-m", "/mnt/usr/share/terminfo/c/cons25-koi8r-m");
	symlink("Eterm", "/mnt/usr/share/terminfo/E/Eterm-color");
	symlink("pcansi-m", "/mnt/usr/share/terminfo/p/pcansi-mono");
	symlink("sun-c", "/mnt/usr/share/terminfo/s/sun-cmd");
	symlink("sun-e", "/mnt/usr/share/terminfo/s/sun-nic");
	symlink("sun-e-s", "/mnt/usr/share/terminfo/s/sun-s-e");
	symlink("sun-cgsix", "/mnt/usr/share/terminfo/s/sun-ss5");
	symlink("vt100", "/mnt/usr/share/terminfo/v/vt100-am");
	symlink("../n/nwp512", "/mnt/usr/share/terminfo/v/vt100-bm");
	symlink("../n/nwp512-o", "/mnt/usr/share/terminfo/v/vt100-bm-o");
	symlink("vt100-s-bot", "/mnt/usr/share/terminfo/v/vt100-bot-s");
	symlink("vt100nam", "/mnt/usr/share/terminfo/v/vt100-nam");
	symlink("vt100-w-nam", "/mnt/usr/share/terminfo/v/vt100-nam-w");
	symlink("vt100-s", "/mnt/usr/share/terminfo/v/vt100-s-top");
	symlink("vt100-s", "/mnt/usr/share/terminfo/v/vt100-top-s");
	symlink("vt100-w", "/mnt/usr/share/terminfo/v/vt100-w-am");
	symlink("vt100-nav-w", "/mnt/usr/share/terminfo/v/vt100-w-nav");
	symlink("vt220-8bit", "/mnt/usr/share/terminfo/v/vt220-8");
	symlink("vt200-js", "/mnt/usr/share/terminfo/v/vt220-js");
	symlink("xterm-r6", "/mnt/usr/share/terminfo/x/xterm-old");

}

/*
void stash_files() {

	if(access("/mnt/var/stash/", 0) == 0) {
		puts("Already stashed\n");
		return;
	}

	create_directory("/mnt/var/stash", 0, 0, 0755);

	jb_log("Stashing directories\n");

	

		mv /Applications /var/stash/
		mv /usr/include /var/stash/
		mv /usr/share /var/stash/

		ln -s /var/stash/Applications /Applications
		ln -s /var/stash/include /usr/include
		ln -s /var/stash/share /usr/share

}
*/

void parseValue(char *key, int keySize, char *p, int size, char *value) {

	value[3] = '.';
	value[4] = '0';

	for(int i = 0; i < size; i++) {
		if(p[i] == '<' && p[i+1] == 'k' && p[i+2] == 'e' && p[i+3] == 'y') { //Found a key

			int j = i+5;
			int found = 1;

			for(int k = 0; k < keySize; k++) {
				if(p[j+k] == key[k]) continue;
				found = 0;
				break;
			}

			if(found) { //Found matching key

				int m = j + keySize;
				while(p[m] != '>') m++; //Find end of </key>
				m++;
				while(p[m] != '>') m++; //Find end of <string>
				m++;

				int a = 0;

				while(p[m] != '<') { 
					value[a] = p[m]; //Read value
					a++;
					m++;
				}

				return;
			}
		}
	}

	value = NULL;
	return;
	
}

void read_file(char *path, char **str, int *size) {
	int fh;
    
    fh = open(path, O_RDONLY, 0);

    if(fh < 0) {
    	jb_log("Failed to open file :(\n");
    	return;
    }

    *size = 500;

    char s[*size];
    char *p = s;

    int ret = read(fh, p, *size);
    if(ret == -1) {
    	jb_log("Failed to read file\n");
        return;
    }

    p[*size] = '\0';
    *str = p;
}

void install_posixspwn() {
	puts("Installing p0sixspwn\n");

	install("/files/fstab.atv", "/mnt/private/etc/fstab", 0, 0, 0644);

	mkdir("/mnt/private/var/untether", 755);
	chown("/mnt/private/var/untether", 0, 0);

	install("/files/p0sixspwn/private/etc/launchd.conf", "/mnt/private/etc/launchd.conf", 0, 0, 644);
	install("/files/p0sixspwn/private/var/lib/dpkg/info/com.ih8sn0w-squiffy-winocm.p0sixspwn.list", "/mnt/private/var/lib/dpkg/info/com.ih8sn0w-squiffy-winocm.p0sixspwn.list", 0, 20, 644);
	install("/files/p0sixspwn/private/var/lib/dpkg/info/com.ih8sn0w-squiffy-winocm.p0sixspwn.postinst", "/mnt/private/var/lib/dpkg/info/com.ih8sn0w-squiffy-winocm.p0sixspwn.postinst", 0, 0, 644);
	install("/files/p0sixspwn/private/var/lib/dpkg/info/com.ih8sn0w-squiffy-winocm.p0sixspwn.prerm", "/mnt/private/var/lib/dpkg/info/com.ih8sn0w-squiffy-winocm.p0sixspwn.prerm", 0, 0, 644);
	install("/files/p0sixspwn/private/var/untether/_.dylib", "/mnt/private/var/untether/_.dylib", 0, 0, 644);
	install("/files/p0sixspwn/private/var/untether/untether", "/mnt/private/var/untether/untether", 0, 0, 755);
	install("/files/p0sixspwn/usr/libexec/dirhelper", "/mnt/usr/libexec/dirhelper", 0, 0, 755);
}

void install_etason_untether() {

	jb_log("Installing etasonATV\n");
	
	mkdir("/mnt/private/etc/rc.d", 755);
	chown("/mnt/private/etc/rc.d", 0, 0);

	install("/files/etasonATV/etc/rc.d/daemonload", "/mnt/private/etc/rc.d/daemonload", 0, 0, 0755);
	install("/files/etasonATV/usr/bin/orphan_commander", "/mnt/usr/bin/orphan_commander", 0, 0, 0755);

	mkdir("/mnt/untether", 755);
	chown("/mnt/untether", 1000, 985);

	install("/files/etasonATV/untether/untether.bin", "/mnt/untether/untether.bin", 0, 0, 0644);
	install("/files/etasonATV/untether/expl.js", "/mnt/untether/expl.js", 0, 0, 0644);

	symlink("/System/Library/Frameworks/JavaScriptCore.framework/Resources/jsc", "/mnt/usr/libexec/rtbuddyd");
	symlink("/untether/expl.js", "/mnt/--early-boot");
}


void install_blackbox_tether() {
	puts("Installing blackb0x tether\n");

	install("/files/rtbuddyd.bin", "/mnt/usr/libexec/rtbuddyd", 0, 0, 0755);

	mkdir("/mnt/private/etc/rc.d", 755);

	install("/files/etasonATV/etc/rc.d/daemonload", "/mnt/private/etc/rc.d/daemonload", 0, 0, 0755);
	install("/files/etasonATV/usr/bin/orphan_commander", "/mnt/usr/bin/orphan_commander", 0, 0, 0755);

}

void install_ios7_tether() {
	install("/usr/bin/dirhelper", "/mnt/usr/libexec/dirhelper", 501, 20, 0755);
}

int install_files(int device) {

    char *log_path = "/mnt/var/mobile/Media/blackb0x_install.log";
	char *path = "/mnt/System/Library/CoreServices/SystemVersion.plist";

	int installed = 0;

	if(access("/mnt/var/mobile/Media/.blackb0x", 0) == 0) {
		jb_log("Jailbreak already installed\n");
		installed = 1;
		//return 0;
	}


	if(access("/mnt/Applications/AppleTV.app/AppleTV", 0) != 0) {
		puts("Not an AppleTV...\n");
		return 0;
	}

	char v[5];
    char *version = v;

    //char b[6];
	//char *build = b;
	
    if(access(path, 0) == 0) {

		char *p = NULL;
		int size = 0;

		read_file(path, &p, &size);

	    parseValue("ProductVersion", 14, p, size, version);
	    version[5] = '\0';

	    //parseValue("ProductBuildVersion", 19, p, size, build);
	    //build[6] = '\0';

    }
    else {
    	jb_log("Version file doesn't exist!\n");
    	return 0;
    }

    jb_log("System Version:");
    jb_log(version);
    jb_log("\n");

    //jb_log("BuildID:");
    //jb_log(build);
    //jb_log("\n");


	install("/files/.blackb0x", "/mnt/var/mobile/Media/.blackb0x", 501, 20, 0755);
	install("/files/profile", "/mnt/private/var/root/.profile", 501, 20, 0755);

    jb_log("Moving SSH files\n");
    
    unlink("/mnt/private/etc/setup.sh");
	install("/files/setup.sh", "/mnt/private/etc/setup.sh", 501, 20, 0755);

	if(!installed) {
		mkdir("/mnt/private/etc/ssh", 0700);
		chown("/mnt/private/etc/ssh", 501, 20);
	}

    install("/bin/mount.sh", "/mnt/bin/mount.sh", 501, 20, 0755);
    install("/bin/bash", "/mnt/bin/bash", 501, 20, 0755);
    install("/bin/ls", "/mnt/bin/ls", 501, 20, 0755);
    install("/bin/sh", "/mnt/bin/sh", 501, 20, 0755);
    install("/mktar.sh", "/mnt/mktar.sh", 501, 20, 0755);
	install("/sbin/sshd", "/mnt/sbin/sshd", 501, 20, 0755);
	install("/usr/bin/device_infos", "/mnt/usr/bin/device_infos", 501, 20, 0755);
	install("/usr/bin/scp", "/mnt/usr/bin/scp", 501, 20, 0755);
	install("/usr/lib/libncurses.5.dylib", "/mnt/usr/lib/libncurses.5.dylib", 501, 20, 0755);
	install("/usr/lib/libncurses.5.4.dylib", "/mnt/usr/lib/libncurses.5.4.dylib", 501, 20, 0755);
	install("/usr/lib/libhistory.6.0.dylib", "/mnt/usr/lib/libhistory.6.0.dylib", 501, 20, 0755);
	install("/usr/lib/libreadline.6.0.dylib", "/mnt/usr/lib/libreadline.6.0.dylib", 501, 20, 0755);
	install("/usr/lib/libcrypto.0.9.8.dylib", "/mnt/usr/lib/libcrypto.0.9.8.dylib", 501, 20, 0755);
	install("/usr/libexec/sftp-server", "/mnt/usr/libexec/sftp-server", 501, 20, 0755);
	
    if(!installed) {

		jb_log("Creating Cydia directories\n");
		create_directories();

		jb_log("Installing OS specific files\n");
		
		if((version[0] == '8') && (version[2] == '4')) { //iOS 8.4.x
			jb_log("Installing iOS 8.4 untether\n");
			install_etason_untether();
			jb_log("Finished install\n");
			install("/files/com.openssh.sshd.plist", "/mnt/Library/LaunchDaemons/com.openssh.sshd.plist", 0, 0, 0644);
			install("/files/com.blackb0x.postinstall.plist", "/mnt/Library/LaunchDaemons/com.blackb0x.postinstall.plist", 0, 0, 0644);
		}
		else if((version[0] == '8') || (version[0] == '7')) { //iOS 8.x
			jb_log("Installing iOS 7 tether\n");
			install_ios7_tether();
			install("/files/com.openssh.sshd.plist", "/mnt/System/Library/LaunchDaemons/com.openssh.sshd.plist", 0, 0, 0644);
			install("/files/com.blackb0x.postinstall.plist", "/mnt/System/Library/LaunchDaemons/com.blackb0x.postinstall.plist", 0, 0, 0644);
		}
		else if((version[0] == '6') && (version[2] == '1') && (version[4] == '4')){
				jb_log("Installing 6.1.4 untether\n");
				install_posixspwn();
				install("/files/com.openssh.sshd.plist", "/mnt/System/Library/LaunchDaemons/com.openssh.sshd.plist", 0, 0, 0644);
				install("/files/com.blackb0x.postinstall.plist", "/mnt/System/Library/LaunchDaemons/com.blackb0x.postinstall.plist", 0, 0, 0644);
		}
		else if(version[0] == '6') {
			jb_log("unsupported version\n");
			return 0;
		}
		else {
			jb_log("unsupported version\n");
			return 0;
		}
		
		install("/usr/bin/ldid", "/mnt/usr/bin/ldid", 501, 20, 0755);
		install("/usr/bin/otool", "/mnt/usr/bin/otool", 501, 20, 0755);
		install("/usr/bin/plutil", "/mnt/usr/bin/plutil", 501, 20, 0755);
	}

	jb_log("Moving repositories\n");

	jb_log(" - [+] JoshTV\n");

	install("/files/joshtv.list", "/mnt/joshtv.list", 501, 20, 0644);
	install("/files/pubkey.key", "/mnt/pubkey.key", 501, 20, 0755);
	//install("/files/awkwardtv.gpg", "/mnt/private/etc/apt/trusted.gpg.d/awkwardtv.gpg", 501, 20, 0755);
	//install("/files/awkwardtv.list", "/mnt/private/etc/apt/sources.list.d/awkwardtv.list", 501, 20, 0644);
	install("/files/nito.png", "/mnt/nito.png", 501, 20, 0755);
	
	if(installed) return 0;
	
	jb_log(" - [+] Kodi\n");
	install("/files/xbmc.list", "/mnt/private/etc/apt/sources.list.d/xbmc.list", 501, 20, 0644);
	install("/files/kodi.png", "/mnt/kodi.png", 501, 20, 0755);


	jb_log(" - [+] Moving debs\n");

	install("/files/beigelist_2.2.6-30_iphoneos-arm.deb", "/mnt/beigelist_2.2.6-30_iphoneos-arm.deb", 501, 20, 0755);
	install("/files/com.nito.updatebegone_0.2-1_iphoneos-arm.deb", "/mnt/com.nito.updatebegone_0.2-1_iphoneos-arm.deb", 501, 20, 0755);
	install("/files/com.saurik.patcyh_1.2.0_iphoneos-arm-fixed.deb", "/mnt/com.saurik.patcyh_1.2.0_iphoneos-arm-fixed.deb", 501, 20, 0755);
	install("/files/ldid_1-1.2.1_iphoneos-arm.deb", "/mnt/ldid_1-1.2.1_iphoneos-arm.deb", 501, 20, 0755);
	install("/files/rtadvd_307.0.1-2_iphoneos-arm-fixed.deb", "/mnt/rtadvd_307.0.1-2_iphoneos-arm-fixed.deb", 501, 20, 0755);
	install("/files/sqlite3-dylib_3.5.9-1_iphoneos-arm-fixed.deb", "/mnt/sqlite3-dylib_3.5.9-1_iphoneos-arm-fixed.deb", 501, 20, 0755);
	install("/files/sqlite3-lib_3.5.9-2_iphoneos-arm-fixed.deb", "/mnt/sqlite3-lib_3.5.9-2_iphoneos-arm-fixed.deb", 501, 20, 0755);
	install("/files/uikittools_1.1.12_iphoneos-arm-fixed.deb", "/mnt/uikittools_1.1.12_iphoneos-arm-fixed.deb", 501, 20, 0755);
	//install("/files/com.nito.nitotv_0.8.7-33_iphoneos-arm.deb", "/mnt/com.nito.nitotv_0.8.7-33_iphoneos-arm.deb", 501, 20, 0755);
	//install("/files/cydia_1.1.30_iphoneos-arm.deb", "/mnt/cydia_1.1.30_iphoneos-arm.deb", 501, 20, 0755);

	jb_log(" - [+] Moving Cydia files\n");

	jb_log("** Installing Binaries\n");
	clone_directory("/files/cydia/bin/", "/mnt/bin/", 501, 20, 0755, 0);
	clone_directory("/files/cydia/sbin/", "/mnt/sbin/", 501, 20, 0755, 0);
	clone_directory("/files/cydia/usr/bin/", "/mnt/usr/bin/", 501, 20, 0755, 0);
	clone_directory("/files/cydia/usr/libexec/", "/mnt/usr/libexec/", 501, 20, 0755, 1);
	install("/files/cydia/usr/libexec/ssh-keysign", "/mnt/usr/libexec/ssh-keysign", 501, 20, 711);
	install("/files/cydia/usr/libexec/sshd-keygen-wrapper", "/mnt/usr/libexec/sshd-keygen-wrapper", 501, 20, 0555);
	clone_directory("/files/cydia/usr/sbin/", "/mnt/usr/sbin/", 501, 20, 0755, 0);


	jb_log("** Installing Headers\n");
	clone_directory("/files/cydia/usr/include/", "/mnt/usr/include/", 501, 20, 0644, 1);
	install("/files/cydia/usr/include/db.h", "/mnt/usr/include/db.h", 501, 20, 444);
	install("/files/cydia/usr/include/db_cxx.h", "/mnt/usr/include/db_cxx.h", 501, 20, 444);


	jb_log("** Installing Libraries\n");
	
	install("/files/cydia/usr/lib/apr.exp", "/mnt/usr/lib/apr.exp", 501, 20, 0644);
	clone_directory("/files/cydia/usr/lib/apt/methods/", "/mnt/usr/lib/apt/methods/", 501, 20, 0755, 0);
	clone_directory("/files/cydia/usr/lib/dpkg/methods/apt/", "/mnt/usr/lib/dpkg/methods/apt/", 501, 20, 0755, 0);
	install("/files/cydia/usr/lib/dpkg/methods/apt/desc.apt", "/mnt/usr/lib/dpkg/methods/apt/desc.apt", 501, 20, 0644);
	install("/files/cydia/usr/lib/dpkg/methods/apt/names", "/mnt/usr/lib/dpkg/methods/apt/names", 501, 20, 0644);
	clone_directory("/files/cydia/usr/lib/engines/", "/mnt/usr/lib/engines/", 501, 20, 0555, 0);
	clone_directory("/files/cydia/usr/lib/gettext/", "/mnt/usr/lib/gettext/", 501, 20, 0755, 0);
	clone_directory("/files/cydia/usr/lib/", "/mnt/usr/lib/", 501, 20, 0755, 0);
	install("/files/cydia/usr/lib/libintl.8.0.2.dylib", "/mnt/usr/lib/libintl.8.0.2.dylib", 501, 20, 0644);
	install("/files/cydia/usr/lib/libintl.la", "/mnt/usr/lib/libintl.la", 501, 20, 0644);
	clone_directory("/files/cydia/usr/lib/pam/", "/mnt/usr/lib/pam/", 501, 20, 0755, 0);
	clone_directory("/files/cydia/usr/lib/pkgconfig/", "/mnt/usr/lib/pkgconfig/", 501, 20, 0644, 0);
	clone_directory("/files/cydia/usr/lib/ssl/misc/", "/mnt/usr/lib/ssl/misc/", 501, 20, 0755, 0);

	jb_log("** Installing Other Files\n");

	install("/files/cydia/private/etc/alternatives/README", "/mnt/private/etc/alternatives/README", 501, 20, 0644);
	clone_directory("/files/cydia/private/etc/", "/mnt/private/etc/", 501, 20, 0644, 1);
	unlink("/mnt/private/etc/apt/sources.list.d/bigboss.list");
	unlink("/mnt/private/etc/apt/sources.list.d/modmyi.com.list");
	unlink("/mnt/private/etc/apt/sources.list.d/zodttd.list");
	install("/files/cydia/private/etc/profile.d/coreutils.sh", "/mnt/private/etc/profile.d/coreutils.sh", 501, 20, 0755);
	install("/files/cydia/private/etc/profile.d/less.sh", "/mnt/private/etc/profile.d/less.sh", 501, 20, 0755);
	clone_directory("/files/cydia/private/var/lib/", "/mnt/private/var/lib/", 501, 20, 0644, 1);
	install("/files/cydia/private/var/run/utmp", "/mnt/private/var/run/utmp", 501, 20, 0644);
	install("/files/cydia/System/Library/LaunchDaemons/com.saurik.Cydia.Startup.plist", "/mnt/System/Library/LaunchDaemons/com.saurik.Cydia.Startup.plist", 0, 0, 0644);
	clone_directory("/files/cydia/usr/share/bigboss/icons/", "/mnt/usr/share/bigboss/icons/", 501, 20, 0444, 1);
	unlink("/mnt/usr/share/bigboss/icons/bigboss.png");
	unlink("/mnt/usr/share/bigboss/icons/planetiphones.png");
	unlink("/mnt/usr/share/bigboss/icons/touchrev.png");
	clone_directory("/files/cydia/usr/share/dpkg/", "/mnt/usr/share/dpkg/", 501, 20, 0644, 0);
	install("/files/cydia/usr/share/gnupg/options.skel", "/mnt/usr/share/gnupg/options.skel", 501, 20, 0644);
	clone_directory("/files/cydia/usr/share/keyrings/", "/mnt/usr/share/keyrings/", 501, 20, 0644, 0);
	install("/files/cydia/usr/share/Ssh.bin", "/mnt/usr/share/Ssh.bin", 501, 20, 0644);
	clone_directory("/files/cydia/usr/share/tabset/", "/mnt/usr/share/tabset/", 501, 20, 0644, 0);
	clone_directory("/files/cydia/usr/share/terminfo/", "/mnt/usr/share/terminfo/", 501, 20, 0644, 1);
	install("/files/cydia/usr/share/terminfo/a/ansi-mono", "/mnt/usr/share/terminfo/a/ansi-mono", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/c/cons25-iso-m", "/mnt/usr/share/terminfo/c/cons25-iso-m", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/c/cons25-iso8859", "/mnt/usr/share/terminfo/c/cons25-iso8859", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/c/cons25-koi8-r", "/mnt/usr/share/terminfo/c/cons25-koi8-r", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/c/cons25-koi8r-m", "/mnt/usr/share/terminfo/c/cons25-koi8r-m", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/E/Eterm-color", "/mnt/usr/share/terminfo/E/Eterm-color", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/p/pcansi-mono", "/mnt/usr/share/terminfo/p/pcansi-mono", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/s/sun-cmd", "/mnt/usr/share/terminfo/s/sun-cmd", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/s/sun-nic", "/mnt/usr/share/terminfo/s/sun-nic", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/s/sun-s-e", "/mnt/usr/share/terminfo/s/sun-s-e", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/s/sun-ss5", "/mnt/usr/share/terminfo/s/sun-ss5", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/v/vt100-am", "/mnt/usr/share/terminfo/v/vt100-am", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/v/vt100-bm", "/mnt/usr/share/terminfo/v/vt100-bm", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/v/vt100-bm-o", "/mnt/usr/share/terminfo/v/vt100-bm-o", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/v/vt100-bot-s", "/mnt/usr/share/terminfo/v/vt100-bot-s", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/v/vt100-nam", "/mnt/usr/share/terminfo/v/vt100-nam", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/v/vt100-nam-w", "/mnt/usr/share/terminfo/v/vt100-nam-w", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/v/vt100-s-top", "/mnt/usr/share/terminfo/v/vt100-s-top", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/v/vt100-top-s", "/mnt/usr/share/terminfo/v/vt100-top-s", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/v/vt100-w-am", "/mnt/usr/share/terminfo/v/vt100-w-am", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/v/vt100-w-nav", "/mnt/usr/share/terminfo/v/vt100-w-nav", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/v/vt220-8", "/mnt/usr/share/terminfo/v/vt220-8", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/v/vt220-js", "/mnt/usr/share/terminfo/v/vt220-js", 501, 20, 0755);
	install("/files/cydia/usr/share/terminfo/x/xterm-old", "/mnt/usr/share/terminfo/x/xterm-old", 501, 20, 0755);


	//Install AFC2D
	//install("/files/afc2d", "/mnt/usr/libexec/afc2d", 0, 0, 0755);
	//install("/files/afc2dService.dylib", "/mnt/Library/MobileSubstrate/DynamicLibraries/afc2dService.dylib", 0, 0, 0755);
	//install("/files/afc2dService.plist", "/mnt/Library/MobileSubstrate/DynamicLibraries/afc2dService.plist", 0, 0, 0644);



	//Install SSH Config
	clone_directory("/private/etc/ssh/", "/mnt/private/etc/ssh/", 501, 20, 0644, 0);
	chmod("/mnt/private/etc/ssh/ssh_host_rsa_key", 0600);
	chmod("/mnt/private/etc/ssh/ssh_host_dsa_key", 0600);
	chmod("/mnt/private/etc/ssh/ssh_host_key", 0600);

	create_symlinks();
	
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
	device = 0;
	puts("Searching for disk...\n");
	while (stat("/dev/disk0s1s1", &status) != 0) {
		puts("Waiting for disk...\n");
		sleep(1);
	}
	puts("\n\n\n\n\n");
	puts("blackb0x Jailbreak - by @NSSpiral\n");

	puts("Mounting filesystem...\n");
	ret = hfs_mount("/dev/disk0s1s1", "/mnt", 0);
	if(ret != 0) {
		puts("Failed to mount / r/w\n");
		return -1;
	}
	puts("Main filesystem mounted\n");


	puts("Mounting user filesystem...\n");
	mkdir("/mnt/private/var2", 0755);

	ret = hfs_mount("/dev/disk0s1s2", "/mnt/private/var", 0);
	if(ret != 0) {
		puts("Failed to mount /var r/w\n");
		return -1;
	}
	puts("User Filesystem mounted\n");

	puts("Mounting devices...\n");
	if (mount("devfs", "/mnt/dev", 0, NULL) != 0) {
		puts("Unable to mount devices!\n");
		unmount("/mnt", 0);
		reboot(1);
		return -1;
	}
	puts("Devices mounted\n");

	install_files(device);

	unmount("/mnt/dev", 0);
	unmount("/mnt", 0);

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
