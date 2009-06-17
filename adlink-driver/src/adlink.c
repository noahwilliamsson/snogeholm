/*
 * adlink.c - (c) 2000-2001 noah williamsson [noah@hd.se]
 *
 * FreeBSD 4.x driver for Adlink PCI 7250
 *
 * TODO:
 * - The code should be style(9) compliant.
 * - Add support for PCI7250 addon cards.
 *
 */


#include <sys/param.h>
#include <sys/systm.h>
#include <sys/bus.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <pci/pcireg.h>
#include <pci/pcivar.h>
#include <sys/sysctl.h>
#include <sys/conf.h>
#include <sys/uio.h>
#include <sys/ioccom.h>
#include <machine/bus.h>
#include <machine/resource.h>
#include <sys/rman.h>
#include "adlink.h"



static int adlink_probe __P((device_t));
static int adlink_attach __P((device_t));
static int adlink_detach __P((device_t));

static d_open_t adlink_open;
static d_close_t adlink_close;
static d_ioctl_t adlink_ioctl;


enum { ADLINK_CLOSED, ADLINK_OPENED, ADLINK_BUSY };
struct adlink_softc {
	int num;
	int state;
	u_long addr;
	struct resource *irq;
	device_t dev;
	dev_t adlink_dev; /* devfs entry */
};

static struct adlink_softc adlink_resources[MAX_CARDS];


static device_method_t adlink_methods[] = {
	DEVMETHOD(device_probe, adlink_probe),
	DEVMETHOD(device_attach, adlink_attach),
	DEVMETHOD(device_detach, adlink_detach),
	{ 0, 0 }
};


static struct cdevsw adlink_cdevsw = {
	adlink_open,
	adlink_close,
	noread,
	nowrite,
	adlink_ioctl,
	nopoll,
	nommap,
	nostrategy,
	"adlink",
	42,
	nodump,
	nopsize,
	0,
	-1
};


static int adlink_probe (device_t dev) {
#ifdef DEBUG
        uprintf("adlink: probe (v=%x, dev=%x)\n", pci_get_vendor(dev), 
		pci_get_device(dev));
#endif

	if(pci_get_vendor(dev) == ADLINK_PCI_V_ID) {
		if(pci_get_device(dev) == ADLINK_PCI_ID_7250) {
			return 0;
		}
	}

        return ENXIO; 
}


static int adlink_attach (device_t dev) {
	int unit, vendor, did; 
	u_long addr;
	struct adlink_softc *softc;

	unit = device_get_unit(dev);
	did = pci_get_device(dev);
	vendor = pci_get_vendor(dev);

#ifdef DEBUG
        uprintf("adlink_attach(): v=%x, dev=%x.\n", vendor, 
		did);
#endif

	if(vendor != ADLINK_PCI_V_ID || did != ADLINK_PCI_ID_7250)
		return ENXIO;

	uprintf("adlink_attach(): ADLINK PCI-7250.\n");

	softc = &adlink_resources[unit];
	memset(softc, 0, sizeof(struct adlink_softc));

	addr = pci_read_config(dev, 0x18, 4);
	uprintf("adlink_attach(): ownreg@0x%lx ", addr);

	addr = pci_read_config(dev, 0x14, 4);
	uprintf("lcr@0x%lx\n", addr);

	device_set_desc(dev, "ADLink PCI-7250");

	addr = pci_read_config(dev, 0x18, 4) - 1; /* Bug? */
	softc->addr = addr;

	/* Reset all relays */
	outb(addr, 0);

	softc->adlink_dev = make_dev(&adlink_cdevsw, 0, UID_ROOT,
			  GID_WHEEL, 0666, "adlink%d", 0);

	return 0;
}


static int adlink_detach (device_t dev) {
	int unit;
	struct adlink_softc *softc;

	unit = device_get_unit(dev);
	softc = &adlink_resources[unit];

#ifdef DEBUG
	uprintf("adlink_detach().\n");
#endif
	if(softc->state & ADLINK_OPENED) {
		return EBUSY;
	}

	destroy_dev(softc->adlink_dev);
	outb(softc->addr, 0);

	return 0;
}


int adlink_open(dev_t dev, int flags, int fmt, struct proc *p) {
	int unit;
	struct adlink_softc *softc;

	unit = minor(dev);
	softc = &adlink_resources[unit];

	if(softc->state != ADLINK_CLOSED) {
		uprintf("adlink_open(): Sorry, dev already open [state=0x%x]!\n", softc->state);
		return EBUSY;
	}

	softc->state |= ADLINK_OPENED;

#ifdef DEBUG
	uprintf("adlink_open().\n");
#endif

	return 0;
}


int adlink_close(dev_t dev, int flags, int fmt, struct proc *p) {
	int unit;
	struct adlink_softc *softc;

	unit = minor(dev);
	softc = &adlink_resources[unit];


	if(softc->state != ADLINK_OPENED) {
		uprintf("adlink_close(): Must open first!\n");
		return ENXIO;
	}

	
	softc->state &= ~ADLINK_OPENED;

#ifdef DEBUG
	uprintf("adlink_close().\n");
#endif

	return 0;
}


int adlink_ioctl(dev_t dev, u_long cmd, caddr_t arg, int flags, struct proc *p) {
	int unit;
	struct adlink_softc *softc;
	u_char val;
	static u_char save = 0;

	unit = minor(dev);
	softc = &adlink_resources[unit];

	if(softc->state != ADLINK_OPENED) {
		uprintf("adlink_close(): Must open first!\n");
		return ENXIO;
	}

	softc->state |= ADLINK_BUSY;
	switch(cmd) {
		case ADLINK_IOCTL_STATUS_OUT:
			val =  inb(softc->addr);
#ifdef DEBUG
			uprintf("adlink_ioctl(): statusreg[0x%lx]=0x%x\n",
				softc->addr, val);
#endif
			*(u_char *)arg = (u_char)val&0xff;
			break;

		case ADLINK_IOCTL_STATUS_IN:
			val =  inb(softc->addr+1);
#ifdef DEBUG
			uprintf("adlink_ioctl(): statusreg[0x%lx]=0x%x\n",
				softc->addr+1, val);
#endif
			/* Hack to make SET_IN ioctl work */
			val |= save;
			*(u_char *)arg = (u_char)val&0xff;
			break;

		case ADLINK_IOCTL_SET_IN:
			save = *((u_char *)arg) & 0xff;
			break;

		case ADLINK_IOCTL_SET_OUT:
			val = *((u_char *)arg) & 0xff;
#ifdef DEBUG
			uprintf("adlink_ioctl(SET_OUT): val=%x cmd=%lx flag=%x\n", val, cmd, flags);
#endif
			outb(softc->addr, val);

			break;
		default: 
			uprintf("adlink_ioctl(): unknown ioctl cmd: %lx\n", cmd);
			break;
	}

	softc->state &= ~ADLINK_BUSY;
	return 0;
}


static driver_t adlink_driver = {
	"adlink", adlink_methods, sizeof(struct adlink_softc)
};

static devclass_t adlink_devclass;
DRIVER_MODULE(adlink, pci, adlink_driver, adlink_devclass, 0, 0);
