/*
 * System call names.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from: NetBSD syscalls.master,v 1.2 1994/06/29 06:30:37
 */

char *svr4_syscallnames[] = {
	"syscall",			/* 0 = syscall */
	"exit",			/* 1 = exit */
	"fork",			/* 2 = fork */
	"read",			/* 3 = read */
	"write",			/* 4 = write */
	"svr4_open",			/* 5 = svr4_open */
	"close",			/* 6 = close */
	"svr4_wait",			/* 7 = svr4_wait */
	"svr4_creat",			/* 8 = svr4_creat */
	"link",			/* 9 = link */
	"unlink",			/* 10 = unlink */
	"svr4_execv",			/* 11 = svr4_execv */
	"chdir",			/* 12 = chdir */
	"time",			/* 13 = time */
	"svr4_mknod",			/* 14 = svr4_mknod */
	"chmod",			/* 15 = chmod */
	"chown",			/* 16 = chown */
	"break",			/* 17 = break */
	"svr4_stat",			/* 18 = svr4_stat */
	"lseek",			/* 19 = lseek */
	"getpid",			/* 20 = getpid */
	"#21",			/* 21 = svr4_old_mount */
	"#22",			/* 22 = System V umount */
	"setuid",			/* 23 = setuid */
	"getuid",			/* 24 = getuid */
	"#25",			/* 25 = svr4_stime */
	"#26",			/* 26 = svr4_ptrace */
	"#27",			/* 27 = svr4_alarm */
	"svr4_fstat",			/* 28 = svr4_fstat */
	"#29",			/* 29 = svr4_pause */
	"#30",			/* 30 = svr4_utime */
	"#31",			/* 31 = was stty */
	"#32",			/* 32 = was gtty */
	"access",			/* 33 = access */
	"#34",			/* 34 = svr4_nice */
	"#35",			/* 35 = svr4_statfs */
	"sync",			/* 36 = sync */
	"kill",			/* 37 = kill */
	"#38",			/* 38 = svr4_fstatfs */
	"#39",			/* 39 = svr4_pgrpsys */
	"#40",			/* 40 = svr4_xenix */
	"dup",			/* 41 = dup */
	"pipe",			/* 42 = pipe */
	"#43",			/* 43 = svr4_times */
	"profil",			/* 44 = profil */
	"#45",			/* 45 = svr4_plock */
	"#46",			/* 46 = svr4_setgid */
	"getgid",			/* 47 = getgid */
	"#48",			/* 48 = svr4_signal */
#ifdef SYSVMSG
	"msgsys",			/* 49 = msgsys */
#else
	"#49",			/* 49 = nosys */
#endif
	"svr4_syssun",			/* 50 = svr4_syssun */
	"acct",			/* 51 = acct */
#ifdef SYSVSHM
	"shmsys",			/* 52 = shmsys */
#else
	"#52",			/* 52 = nosys */
#endif
#ifdef SYSVSEM
	"semsys",			/* 53 = semsys */
#else
	"#53",			/* 53 = nosys */
#endif
	"svr4_ioctl",			/* 54 = svr4_ioctl */
	"#55",			/* 55 = svr4_uadmin */
	"#56",			/* 56 = svr4_exch */
	"#57",			/* 57 = svr4_utssys */
	"fsync",			/* 58 = fsync */
	"execve",			/* 59 = execve */
	"umask",			/* 60 = umask */
	"chroot",			/* 61 = chroot */
	"#62",			/* 62 = svr4_fcntl */
	"#63",			/* 63 = nosys */
	"#64",			/* 64 = reserved for unix/pc */
	"#65",			/* 65 = reserved for unix/pc */
	"#66",			/* 66 = reserved for unix/pc */
	"#67",			/* 67 = reserved for unix/pc */
	"#68",			/* 68 = reserved for unix/pc */
	"#69",			/* 69 = reserved for unix/pc */
	"obs_svr4_advfs",			/* 70 = obsolete svr4_advfs */
	"obs_svr4_unadvfs",			/* 71 = obsolete svr4_unadvfs */
	"obs_svr4_rmount",			/* 72 = obsolete svr4_rmount */
	"obs_svr4_rumount",			/* 73 = obsolete svr4_rumount */
	"obs_svr4_rfstart",			/* 74 = obsolete svr4_rfstart */
	"obs_svr4_sigret",			/* 75 = obsolete svr4_sigret */
	"obs_svr4_rdebug",			/* 76 = obsolete svr4_rdebug */
	"obs_svr4_rfstop",			/* 77 = obsolete svr4_rfstop */
	"#78",			/* 78 = svr4_rfsys */
	"rmdir",			/* 79 = rmdir */
	"mkdir",			/* 80 = mkdir */
	"#81",			/* 81 = svr4_getdents */
	"obs_svr4_libattach",			/* 82 = obsolete svr4_libattach */
	"obs_svr4_libdetach",			/* 83 = obsolete svr4_libdetach */
	"#84",			/* 84 = svr4_sysfs */
	"#85",			/* 85 = getmsg */
	"#86",			/* 86 = putmsg */
	"#87",			/* 87 = poll */
	"svr4_lstat",			/* 88 = svr4_lstat */
	"symlink",			/* 89 = symlink */
	"readlink",			/* 90 = readlink */
	"setgroups",			/* 91 = setgroups */
	"getgroups",			/* 92 = getgroups */
	"fchmod",			/* 93 = fchmod */
	"fchown",			/* 94 = fchown */
	"sigprocmask",			/* 95 = sigprocmask */
	"sigaltstack",			/* 96 = sigaltstack */
	"sigsuspend",			/* 97 = sigsuspend */
	"sigaction",			/* 98 = sigaction */
	"svr4_sigpending",			/* 99 = svr4_sigpending */
	"#100",			/* 100 = svr4_context */
	"#101",			/* 101 = svr4_evsys */
	"#102",			/* 102 = svr4_evtrapret */
	"#103",			/* 103 = svr4_statvfs */
	"#104",			/* 104 = svr4_fstatvfs */
	"#105",			/* 105 = svr4 reserved */
#ifdef NFSSERVER
	"#106",			/* 106 = svr4_nfssvc */
#else
	"#106",			/* 106 = nosys */
#endif
	"#107",			/* 107 = svr4_waitsys */
	"#108",			/* 108 = svr4_sigsendsys */
	"#109",			/* 109 = svr4_hrtsys */
	"#110",			/* 110 = svr4_acancel */
	"#111",			/* 111 = svr4_async */
	"#112",			/* 112 = svr4_priocntlsys */
	"pathconf",			/* 113 = pathconf */
	"mincore",			/* 114 = mincore */
	"svr4_mmap",			/* 115 = svr4_mmap */
	"mprotect",			/* 116 = mprotect */
	"munmap",			/* 117 = munmap */
	"fpathconf",			/* 118 = fpathconf */
	"vfork",			/* 119 = vfork */
	"fchdir",			/* 120 = fchdir */
	"readv",			/* 121 = readv */
	"writev",			/* 122 = writev */
	"#123",			/* 123 = svr4_xstat */
	"#124",			/* 124 = svr4_lxstat */
	"#125",			/* 125 = svr4_fxstat */
	"#126",			/* 126 = svr4_xmknod */
	"#127",			/* 127 = svr4_clocal */
	"svr4_setrlimit",			/* 128 = svr4_setrlimit */
	"svr4_getrlimit",			/* 129 = svr4_getrlimit */
	"#130",			/* 130 = svr4_lchown */
	"#131",			/* 131 = svr4_memcntl */
	"#132",			/* 132 = svr4_getpmsg */
	"#133",			/* 133 = svr4_putpmsg */
	"rename",			/* 134 = rename */
	"svr4_uname",			/* 135 = svr4_uname */
	"setegid",			/* 136 = setegid */
	"svr4_sysconfig",			/* 137 = svr4_sysconfig */
	"adjtime",			/* 138 = adjtime */
	"#139",			/* 139 = svr4_systeminfo */
	"#140",			/* 140 = reserved */
	"seteuid",			/* 141 = seteuid */
	"#142",			/* 142 = vtrace */
	"#143",			/* 143 = svr4_fork1 */
	"#144",			/* 144 = svr4_sigwait */
	"#145",			/* 145 = svr4_lwp_info */
	"#146",			/* 146 = svr4_yield */
	"#147",			/* 147 = svr4_lwp_sema_p */
	"#148",			/* 148 = svr4_lwp_sema_v */
	"#149",			/* 149 = reserved */
	"#150",			/* 150 = reserved */
	"#151",			/* 151 = reserved */
	"#152",			/* 152 = svr4_modctl */
	"svr4_fchroot",			/* 153 = svr4_fchroot */
	"#154",			/* 154 = svr4_utimes */
	"svr4_vhangup",			/* 155 = svr4_vhangup */
	"gettimeofday",			/* 156 = gettimeofday */
	"getitimer",			/* 157 = getitimer */
	"setitimer",			/* 158 = setitimer */
	"#159",			/* 159 = svr4_lwp_create */
	"#160",			/* 160 = svr4_lwp_exit */
	"#161",			/* 161 = svr4_lwp_suspend */
	"#162",			/* 162 = svr4_lwp_continue */
	"#163",			/* 163 = svr4_lwp_kill */
	"#164",			/* 164 = svr4_lwp_self */
	"#165",			/* 165 = svr4_lwp_getprivate */
	"#166",			/* 166 = svr4_lwp_setprivate */
	"#167",			/* 167 = svr4_lwp_wait */
	"#168",			/* 168 = svr4_lwp_mutex_unlock */
	"#169",			/* 169 = svr4_lwp_mutex_lock */
	"#170",			/* 170 = svr4_lwp_cond_wait */
	"#171",			/* 171 = svr4_lwp_cond_signal */
	"#172",			/* 172 = svr4_lwp_cond_broadcast */
	"#173",			/* 173 = svr4_pread */
	"#174",			/* 174 = svr4_pwrite */
	"#175",			/* 175 = svr4_llseek */
	"#176",			/* 176 = svr4_inst_sync */
	"#177",			/* 177 = reserved */
	"#178",			/* 178 = reserved */
	"#179",			/* 179 = reserved */
	"#180",			/* 180 = reserved */
	"#181",			/* 181 = reserved */
	"#182",			/* 182 = reserved */
	"#183",			/* 183 = reserved */
	"#184",			/* 184 = reserved */
	"#185",			/* 185 = reserved */
	"#186",			/* 186 = svr4_auditsys */
};