/**
 * This driver is a dummy driver for testing and developing kRopr.
 *
 * DO NOT USE THIS IN PRODUCTION GOD DAMN IT!
 *
 * @author Florian Marrero Liestmann
 * @email f.m.liestmann@fx-ttr.de
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>

#define MODULE_NAME "kropr"
#define DRV_DEV_NAME "kropr"
#define DRV_DEV_PATH "/dev/kropr"

static int device_open(struct inode*, struct file*);
static long device_ioctl(struct file*, unsigned int, unsigned long);
static int device_release(struct inode*, struct file*);

static struct class *class;
static int major_nr;
unsigned int *ops[3];
static struct file_operations fops = {
        .open = device_open,
        .release = device_release,
        .unlocked_ioctl = device_ioctl
};

static int device_open(struct inode *i, struct file *f) {
        printk(KERN_INFO "device opened!\n");
        return 0;
}

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long args) {
        struct drv_req *req;
        void (*fn)(void);

        switch(cmd) {
                case 0:      
                        // TODO
                        break;
                default:
                break;
        }

        return 0;
}

static int device_release(struct inode *i, struct file *f) {
        printk(KERN_INFO "device released!\n");
        return 0;
}

static int m_init(void) {
        printk(KERN_INFO "addr(ops) = %p\n", &ops);
        major_no = register_chrdev(0, DEVICE_NAME, &fops);
        class = class_create(THIS_MODULE, DEVICE_NAME);
        device_create(class, NULL, MKDEV(major_no, 0), NULL, DEVICE_NAME);
        
        return 0;
}

static void m_exit(void) {
        device_destroy(class, MKDEV(major_no, 0));
        class_unregister(class);
        class_destroy(class);
        unregister_chrdev(major_no, DEVICE_NAME);
        printk(KERN_INFO "Driver unloaded\n");
}

module_init(m_init);
module_exit(m_exit);

MODULE_LICENSE("GPL");
