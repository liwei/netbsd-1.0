/*
 * System call names.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from: NetBSD syscalls.master,v 1.22 1994/06/29 06:33:10
 */

char *syscallnames[] = {
	"syscall",			/* 0 = syscall */
	"exit",			/* 1 = exit */
	"fork",			/* 2 = fork */
	"read",			/* 3 = read */
	"write",			/* 4 = write */
	"open",			/* 5 = open */
	"close",			/* 6 = close */
	"wait4",			/* 7 = wait4 */
	"old.creat",		/* 8 = old creat */
	"link",			/* 9 = link */
	"unlink",			/* 10 = unlink */
	"obs_execv",			/* 11 = obsolete execv */
	"chdir",			/* 12 = chdir */
	"fchdir",			/* 13 = fchdir */
	"mknod",			/* 14 = mknod */
	"chmod",			/* 15 = chmod */
	"chown",			/* 16 = chown */
	"break",			/* 17 = break */
	"getfsstat",			/* 18 = getfsstat */
	"old.lseek",		/* 19 = old lseek */
	"getpid",			/* 20 = getpid */
	"mount",			/* 21 = mount */
	"unmount",			/* 22 = unmount */
	"setuid",			/* 23 = setuid */
	"getuid",			/* 24 = getuid */
	"geteuid",			/* 25 = geteuid */
	"ptrace",			/* 26 = ptrace */
	"recvmsg",			/* 27 = recvmsg */
	"sendmsg",			/* 28 = sendmsg */
	"recvfrom",			/* 29 = recvfrom */
	"accept",			/* 30 = accept */
	"getpeername",			/* 31 = getpeername */
	"getsockname",			/* 32 = getsockname */
	"access",			/* 33 = access */
	"chflags",			/* 34 = chflags */
	"fchflags",			/* 35 = fchflags */
	"sync",			/* 36 = sync */
	"kill",			/* 37 = kill */
	"old.stat",		/* 38 = old stat */
	"getppid",			/* 39 = getppid */
	"old.lstat",		/* 40 = old lstat */
	"dup",			/* 41 = dup */
	"pipe",			/* 42 = pipe */
	"getegid",			/* 43 = getegid */
	"profil",			/* 44 = profil */
#ifdef KTRACE
	"ktrace",			/* 45 = ktrace */
#else
	"#45",			/* 45 = ktrace */
#endif
	"sigaction",			/* 46 = sigaction */
	"getgid",			/* 47 = getgid */
	"sigprocmask",			/* 48 = sigprocmask */
	"getlogin",			/* 49 = getlogin */
	"setlogin",			/* 50 = setlogin */
	"acct",			/* 51 = acct */
	"sigpending",			/* 52 = sigpending */
	"sigaltstack",			/* 53 = sigaltstack */
	"ioctl",			/* 54 = ioctl */
	"reboot",			/* 55 = reboot */
	"revoke",			/* 56 = revoke */
	"symlink",			/* 57 = symlink */
	"readlink",			/* 58 = readlink */
	"execve",			/* 59 = execve */
	"umask",			/* 60 = umask */
	"chroot",			/* 61 = chroot */
	"old.fstat",		/* 62 = old fstat */
	"old.getkerninfo",		/* 63 = old getkerninfo */
	"old.getpagesize",		/* 64 = old getpagesize */
	"msync",			/* 65 = msync */
	"vfork",			/* 66 = vfork */
	"obs_vread",			/* 67 = obsolete vread */
	"obs_vwrite",			/* 68 = obsolete vwrite */
	"sbrk",			/* 69 = sbrk */
	"sstk",			/* 70 = sstk */
	"old.mmap",		/* 71 = old mmap */
	"vadvise",			/* 72 = vadvise */
	"munmap",			/* 73 = munmap */
	"mprotect",			/* 74 = mprotect */
	"madvise",			/* 75 = madvise */
	"obs_vhangup",			/* 76 = obsolete vhangup */
	"obs_vlimit",			/* 77 = obsolete vlimit */
	"mincore",			/* 78 = mincore */
	"getgroups",			/* 79 = getgroups */
	"setgroups",			/* 80 = setgroups */
	"getpgrp",			/* 81 = getpgrp */
	"setpgid",			/* 82 = setpgid */
	"setitimer",			/* 83 = setitimer */
	"old.wait",		/* 84 = old wait */
	"swapon",			/* 85 = swapon */
	"getitimer",			/* 86 = getitimer */
	"old.gethostname",		/* 87 = old gethostname */
	"old.sethostname",		/* 88 = old sethostname */
	"old.getdtablesize",		/* 89 = old getdtablesize */
	"dup2",			/* 90 = dup2 */
	"#91",			/* 91 = getdopt */
	"fcntl",			/* 92 = fcntl */
	"select",			/* 93 = select */
	"#94",			/* 94 = setdopt */
	"fsync",			/* 95 = fsync */
	"setpriority",			/* 96 = setpriority */
	"socket",			/* 97 = socket */
	"connect",			/* 98 = connect */
	"old.accept",		/* 99 = old accept */
	"getpriority",			/* 100 = getpriority */
	"old.send",		/* 101 = old send */
	"old.recv",		/* 102 = old recv */
	"sigreturn",			/* 103 = sigreturn */
	"bind",			/* 104 = bind */
	"setsockopt",			/* 105 = setsockopt */
	"listen",			/* 106 = listen */
	"obs_vtimes",			/* 107 = obsolete vtimes */
	"old.sigvec",		/* 108 = old sigvec */
	"old.sigblock",		/* 109 = old sigblock */
	"old.sigsetmask",		/* 110 = old sigsetmask */
	"sigsuspend",			/* 111 = sigsuspend */
	"old.sigstack",		/* 112 = old sigstack */
	"old.recvmsg",		/* 113 = old recvmsg */
	"old.sendmsg",		/* 114 = old sendmsg */
#ifdef TRACE
	"vtrace",			/* 115 = vtrace */
#else
	"obs_vtrace",			/* 115 = obsolete vtrace */
#endif
	"gettimeofday",			/* 116 = gettimeofday */
	"getrusage",			/* 117 = getrusage */
	"getsockopt",			/* 118 = getsockopt */
#ifdef vax
	"resuba",			/* 119 = resuba */
#else
	"#119",			/* 119 = nosys */
#endif
	"readv",			/* 120 = readv */
	"writev",			/* 121 = writev */
	"settimeofday",			/* 122 = settimeofday */
	"fchown",			/* 123 = fchown */
	"fchmod",			/* 124 = fchmod */
	"old.recvfrom",		/* 125 = old recvfrom */
	"old.setreuid",		/* 126 = old setreuid */
	"old.setregid",		/* 127 = old setregid */
	"rename",			/* 128 = rename */
	"old.truncate",		/* 129 = old truncate */
	"old.ftruncate",		/* 130 = old ftruncate */
	"flock",			/* 131 = flock */
	"mkfifo",			/* 132 = mkfifo */
	"sendto",			/* 133 = sendto */
	"shutdown",			/* 134 = shutdown */
	"socketpair",			/* 135 = socketpair */
	"mkdir",			/* 136 = mkdir */
	"rmdir",			/* 137 = rmdir */
	"utimes",			/* 138 = utimes */
	"obs_4.2",			/* 139 = obsolete 4.2 sigreturn */
	"adjtime",			/* 140 = adjtime */
	"old.getpeername",		/* 141 = old getpeername */
	"old.gethostid",		/* 142 = old gethostid */
	"old.sethostid",		/* 143 = old sethostid */
	"old.getrlimit",		/* 144 = old getrlimit */
	"old.setrlimit",		/* 145 = old setrlimit */
	"old.killpg",		/* 146 = old killpg */
	"setsid",			/* 147 = setsid */
	"quotactl",			/* 148 = quotactl */
	"old.quota",		/* 149 = old quota */
	"old.getsockname",		/* 150 = old getsockname */
	"#151",			/* 151 = nosys */
	"#152",			/* 152 = nosys */
	"#153",			/* 153 = nosys */
	"#154",			/* 154 = nosys */
#if defined(NFSCLIENT) || defined(NFSSERVER)
	"nfssvc",			/* 155 = nfssvc */
#else
	"#155",			/* 155 = nosys */
#endif
	"old.getdirentries",		/* 156 = old getdirentries */
	"statfs",			/* 157 = statfs */
	"fstatfs",			/* 158 = fstatfs */
	"#159",			/* 159 = nosys */
	"#160",			/* 160 = nosys */
#ifdef NFSCLIENT
	"getfh",			/* 161 = getfh */
#else
	"#161",			/* 161 = nosys */
#endif
	"old.getdomainname",		/* 162 = old getdomainname */
	"old.setdomainname",		/* 163 = old setdomainname */
	"old.uname",		/* 164 = old uname */
	"sysarch",			/* 165 = sysarch */
	"#166",			/* 166 = nosys */
	"#167",			/* 167 = nosys */
	"#168",			/* 168 = nosys */
#ifdef SYSVSEM
	"semsys",			/* 169 = semsys */
#else
	"#169",			/* 169 = nosys */
#endif
#ifdef SYSVMSG
	"msgsys",			/* 170 = msgsys */
#else
	"#170",			/* 170 = nosys */
#endif
#ifdef SYSVSHM
	"shmsys",			/* 171 = shmsys */
#else
	"#171",			/* 171 = nosys */
#endif
	"#172",			/* 172 = nosys */
	"#173",			/* 173 = nosys */
	"#174",			/* 174 = nosys */
	"#175",			/* 175 = nosys */
	"#176",			/* 176 = nosys */
	"#177",			/* 177 = nosys */
	"#178",			/* 178 = nosys */
	"#179",			/* 179 = nosys */
	"#180",			/* 180 = nosys */
	"setgid",			/* 181 = setgid */
	"setegid",			/* 182 = setegid */
	"seteuid",			/* 183 = seteuid */
#ifdef LFS
	"lfs_bmapv",			/* 184 = lfs_bmapv */
	"lfs_markv",			/* 185 = lfs_markv */
	"lfs_segclean",			/* 186 = lfs_segclean */
	"lfs_segwait",			/* 187 = lfs_segwait */
#else
	"#184",			/* 184 = nosys */
	"#185",			/* 185 = nosys */
	"#186",			/* 186 = nosys */
	"#187",			/* 187 = nosys */
#endif
	"stat",			/* 188 = stat */
	"fstat",			/* 189 = fstat */
	"lstat",			/* 190 = lstat */
	"pathconf",			/* 191 = pathconf */
	"fpathconf",			/* 192 = fpathconf */
	"#193",			/* 193 = nosys */
	"getrlimit",			/* 194 = getrlimit */
	"setrlimit",			/* 195 = setrlimit */
	"getdirentries",			/* 196 = getdirentries */
	"mmap",			/* 197 = mmap */
	"__syscall",			/* 198 = __syscall */
	"lseek",			/* 199 = lseek */
	"truncate",			/* 200 = truncate */
	"ftruncate",			/* 201 = ftruncate */
	"__sysctl",			/* 202 = __sysctl */
	"mlock",			/* 203 = mlock */
	"munlock",			/* 204 = munlock */
	"#205",			/* 205 = nosys */
	"#206",			/* 206 = nosys */
	"#207",			/* 207 = nosys */
	"#208",			/* 208 = nosys */
	"#209",			/* 209 = nosys */
#ifdef LKM
	"lkmnosys",			/* 210 = lkmnosys */
	"lkmnosys",			/* 211 = lkmnosys */
	"lkmnosys",			/* 212 = lkmnosys */
	"lkmnosys",			/* 213 = lkmnosys */
	"lkmnosys",			/* 214 = lkmnosys */
	"lkmnosys",			/* 215 = lkmnosys */
	"lkmnosys",			/* 216 = lkmnosys */
	"lkmnosys",			/* 217 = lkmnosys */
	"lkmnosys",			/* 218 = lkmnosys */
	"lkmnosys",			/* 219 = lkmnosys */
#else	/* !LKM */
	"#210",			/* 210 = nosys */
	"#211",			/* 211 = nosys */
	"#212",			/* 212 = nosys */
	"#213",			/* 213 = nosys */
	"#214",			/* 214 = nosys */
	"#215",			/* 215 = nosys */
	"#216",			/* 216 = nosys */
	"#217",			/* 217 = nosys */
	"#218",			/* 218 = nosys */
	"#219",			/* 219 = nosys */
#endif	/* !LKM */
};
