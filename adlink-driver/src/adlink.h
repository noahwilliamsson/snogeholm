/*
 * adlink.h - (c) 2000-2001 noah williamsson [noah@hd.se]
 *
 */



#define ADLINK_OFFSET_LCR_BASE	0x14
#define ADLINK_OFFSET_IO_BASE	0x18

#define MAX_CARDS		4
#define ADLINK_PCI_V_ID		0x144a
#define ADLINK_PCI_ID_7250	0x7250


/* IOCTLs for reading status */
#define ADLINK_IOCTL_STATUS_IN		_IOR(42, 1, u_char)
#define ADLINK_IOCTL_STATUS_OUT		_IOR(42, 2, u_char)

/* IOCTLs for setting status */
#define ADLINK_IOCTL_SET_IN		_IOW(42, 3, u_char)
#define ADLINK_IOCTL_SET_OUT		_IOW(42, 4, u_char)

