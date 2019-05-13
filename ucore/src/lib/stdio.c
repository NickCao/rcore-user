#include <defs.h>
#include <stdio.h>
#include <syscall.h>
#include <file.h>
#include <ulib.h>
#include <unistd.h>

static void
fputch(char c, int *cnt, int fd) {
    write(fd, &c, sizeof(char));
    (*cnt) ++;
}

/* *
 * cputch - writes a single character @c to stdout, and it will
 * increace the value of counter pointed by @cnt.
 * */
static void
cputch(int c, int *cnt) {
    fputch(c, cnt, stdout);
}

/* *
 * vcprintf - format a string and writes it to stdout
 *
 * The return value is the number of characters which would be
 * written to stdout.
 *
 * Call this function if you are already dealing with a va_list.
 * Or you probably want cprintf() instead.
 * */
int
vcprintf(const char *fmt, va_list ap) {
    int cnt = 0;
    vprintfmt((void*)cputch, NO_FD, &cnt, fmt, ap);
    return cnt;
}

/* *
 * cprintf - formats a string and writes it to stdout
 *
 * The return value is the number of characters which would be
 * written to stdout.
 * */
int
cprintf(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    int cnt = vcprintf(fmt, ap);
    va_end(ap);

    return cnt;
}

/* *
 * cputs- writes the string pointed by @str to stdout and
 * appends a newline character.
 * */
int
cputs(const char *str) {
    int cnt = 0;
    char c;
    while ((c = *str ++) != '\0') {
        cputch(c, &cnt);
    }
    cputch('\n', &cnt);
    return cnt;
}

int
vfprintf(int fd, const char *fmt, va_list ap) {
    int cnt = 0;
    vprintfmt((void*)fputch, fd, &cnt, fmt, ap);
    return cnt;
}

int
fprintf(int fd, const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    int cnt = vfprintf(fd, fmt, ap);
    va_end(ap);

    return cnt;
}

int
getchar(void) {
    char c;
    long result = read(stdin, &c, sizeof(char));
    if (result < 0) {
        return -1;
    } else {
        return c;
    }
}