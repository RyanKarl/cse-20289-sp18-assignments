Homework 08
===========

By Ryan Karl

## Strace Output 

### `duplicate`

After using strace on my own duplicate (strace -c ./duplicate if=/etc/passwd > /dev/null) I received the following output:

% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
100.00    0.000021           1        16        12 stat
0.00    0.000000           0         9           read
0.00    0.000000           0         7           write
0.00    0.000000           0        20        16 open
0.00    0.000000           0         4           close
0.00    0.000000           0         2           fstat
0.00    0.000000           0         8           mmap
0.00    0.000000           0         3           mprotect
0.00    0.000000           0         1           munmap
0.00    0.000000           0         3           brk
0.00    0.000000           0         1         1 access
0.00    0.000000           0         1           execve
0.00    0.000000           0         1           archprctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.000021                    76        29 total

### `dd`

After using strace on the dd command (strace -c dd if=/etc/passwd > /dev/null) I received the following output:

6+1 records in
6+1 records out
3148 bytes (3.1 kB) copied, 0.000523602 s, 6.0 MB/s
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
60.00    0.000021           1        16        12 stat
40.00    0.000014           7         2         1 futex
0.00    0.000000           0        13           read
0.00    0.000000           0        10           write
0.00    0.000000           0        37        29 open
0.00    0.000000           0        11           close
0.00    0.000000           0         7           fstat
0.00    0.000000           0         1           lseek
0.00    0.000000           0        17           mmap
0.00    0.000000           0         7           mprotect
0.00    0.000000           0         2           munmap
0.00    0.000000           0         3           brk
0.00    0.000000           0         6           rtsigaction
0.00    0.000000           0         1           rtsigprocmask
0.00    0.000000           0         1         1 access
0.00    0.000000           0         1           dup2
0.00    0.000000           0         1           execve
0.00    0.000000           0         1           getrlimit
0.00    0.000000           0         1           archprctl
0.00    0.000000           0         1           settidaddress
0.00    0.000000           0         1           setrobustlist
------ ----------- ----------- --------- --------- ----------------
100.00    0.000035                   140        43 total



### `search`

After using strace on my own search (strace -c ./search /etc -type d -name '*conf*') I received the following output:

% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
55.79    0.000443           0      3751           lstat
31.74    0.000252           0       700           getdents
10.83    0.000086           0       384        32 open
1.64    0.000013           0       352           close
0.00    0.000000           0         1           read
0.00    0.000000           0        45           write
0.00    0.000000           0        16        12 stat
0.00    0.000000           0         3           fstat
0.00    0.000000           0         9           mmap
0.00    0.000000           0         3           mprotect
0.00    0.000000           0         1           munmap
0.00    0.000000           0         4           brk
0.00    0.000000           0         1         1 access
0.00    0.000000           0         1           execve
0.00    0.000000           0         1           fcntl
0.00    0.000000           0         1           archprctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.000794                  5273        45 total




### `find`

After using strace on the find command (strace -c find /etc -type d -name '*conf*') I received the following output:

% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
31.62    0.000184           0       700           getdents
20.45    0.000119           0       716           newfstatat
16.32    0.000095           0       776        64 open
11.51    0.000067           0       703           fchdir
10.48    0.000061           0       714           close
4.98    0.000029           2        16        12 stat
2.41    0.000014           0       361           fstat
2.23    0.000013           7         2           rtsigaction
0.00    0.000000           0        10           read
0.00    0.000000           0        93           write
0.00    0.000000           0        26           mmap
0.00    0.000000           0        13           mprotect
0.00    0.000000           0         4           munmap
0.00    0.000000           0         5           brk
0.00    0.000000           0         1           rtsigprocmask
0.00    0.000000           0         2           ioctl
0.00    0.000000           0         1         1 access
0.00    0.000000           0         1           execve
0.00    0.000000           0         1           uname
0.00    0.000000           0         1           fcntl
0.00    0.000000           0         1           getrlimit
0.00    0.000000           0         1           statfs
0.00    0.000000           0         1           archprctl
0.00    0.000000           0         3         1 futex
0.00    0.000000           0         1           settidaddress
0.00    0.000000           0         1           setrobustlist
------ ----------- ----------- --------- --------- ----------------
100.00    0.000582                  4154        78 total


## Questions

1. Describe the differences you see between the number and type of system calls
   used by your utilities as compared to the standard Unix programs.

        Upon closer inspection, it seems that my duplicate program makes fewer system calls than the corresponding dd
        command (it calls read, write, open and close, 9, 7, 20, and 4 times respectively vs. 13, 10, 37, and 11 times for dd).  
        Interestingly, my search program also makes more system calls than the find command (it calls lstat, getdents, open and close, 
        3751, 700, 384, and 352 times respectively vs. 0, 700, 776, and 714 times for find).  Note that the Unix syscalls will do the 
        same basic operation (opening files to read there contents, perform an action, and then close) as the hand written programs 
        in different manners.  For instance both duplicate and dd make repeated calls to stat, read, write, open, and close.  
        Similarly, both search and find make repeated calls to getdents, open, close, and some form of stat.



2. Did you notice anything surprising about the trace of your utilities or the
   trace of the standard Unix programs? Which implementations are faster or
   more efficient?  Explain.

        My duplicate program is faster than the dd program, as it finishes in 0.000021 seconds vs. 0.000035 seconds for dd.  However, 
        my search program is slower than the find command, as it takes 0.000794 seconds vs. 0.000582 seconds for the find program.  
        Also, it is interesting that some calls are executed the same number of times i.e. duplicate and dd both make 16 calls to
        stat, and search and find both make 700 calls to getdents, but other commands are called at much different rates.  Also,
        the Unix utilities sometimes make system calls frequently that are never made by my programs, as the find utility makes
        over 700 calls each to newfstatat and fchdir even though my search progarm never references these calls.


