#include "qpcpp.hpp"

extern "C"
{
    int _close(int file)
    {
        Q_UNUSED_PAR(file);
        return -1;  // Not implemented, always fails
    }

    int _fstat(int file, struct stat *st)
    {
        Q_UNUSED_PAR(file);
        Q_UNUSED_PAR(st);

        return 0;
    }

    int _isatty(int file)
    {
        Q_UNUSED_PAR(file);
        return 1;
    }

    int _lseek(int file, int *ptr, int dir)
    {
        Q_UNUSED_PAR(file);
        Q_UNUSED_PAR(ptr);
        Q_UNUSED_PAR(dir);
        return 0;  // Always successful as we're not implementing a filesystem
    }

    int _read(int file, char *ptr, int len)
    {
        Q_UNUSED_PAR(file);
        Q_UNUSED_PAR(ptr);
        Q_UNUSED_PAR(len);
        return 0;  // Not implemented, always returns EOF
    }

    int _write(int file, char *ptr, int len)
    {
        Q_UNUSED_PAR(file);
        Q_UNUSED_PAR(ptr);
        Q_UNUSED_PAR(len);

        // Implement your write function here
        // For example, you could write to UART or any other peripheral
        return len;  // Return the number of bytes written
    }

    void _exit(int status)
    {
        Q_UNUSED_PAR(status);

        while (1)
        {
        }  // Infinite loop
    }

    void _kill(int pid, int sig)
    {
        Q_UNUSED_PAR(pid);
        Q_UNUSED_PAR(sig);

        return;  // Not implemented
    }

    int _getpid(void)
    {
        return 1;  // Return a dummy PID
    }

}  // extern "C"