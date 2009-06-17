/*
 * adlink.h, part of slim - (c) 2001 noah williamsson [noah@hd.se]
 *
 *
 */


#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioccom.h>
#include <sys/ioctl.h>

#define ADLINK_IOCTL_STATUS_IN     _IOR(42, 1, u_char)
#define ADLINK_IOCTL_STATUS_OUT     _IOR(42, 2, u_char)
#define ADLINK_IOCTL_SET_IN     _IOW(42, 3, u_char)
#define ADLINK_IOCTL_SET_OUT     _IOW(42, 4, u_char)
