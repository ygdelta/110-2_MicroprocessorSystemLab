#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/gpio.h>

#define LED1 396
#define LED2 397
#define LED3 429
#define LED4 393

#define MAJOR_NUM 60
#define MODULE_NAME "demo"

static char userChar[100];

int gpioPin[4] = {LED1, LED2, LED3, LED4};
int ledStatus[4] = {0, 0, 0, 0};
static int gpio;
static int status;

static ssize_t drv_read(struct file *filp,char *buf, size_t count, loff_t *ppos){
	printk("Enter Read function\n");
	printk("device read\n");
	return 0;
}

static ssize_t drv_write(struct file *filp, const char *buf, size_t count, loff_t *ppos)
{
	printk("Enter Write function\n");
	printk("device write\n");
	printk("W_buf_size: %d\n", (int)count);
	if(copy_from_user(userChar, buf, count) == 0) {
		userChar[count - 1] = '\0';
		printk("userChar: %s\n", userChar);
		
		//Turn userChar to GPIO input
		gpio = (userChar[0] - '0') * 100 + (userChar[1] - '0') * 10 + (userChar[2] - '0');
		status = (userChar[3] - '0');
		printk("gpio: %d", gpio);
		
		//excute
		if(status == 2) {
			char r[100] = {'\0'};
			switch(gpio) {
			case LED1:
				snprintf(r, sizeof(r), "LED1(GPIO=%d) Status: %d", gpio, ledStatus[0]);
				copy_to_user(buf, r, strlen(r) + 1);
				printk("%s", r);
				break;
			case LED2:
				snprintf(r, sizeof(r), "LED2(GPIO=%d) Status: %d", gpio, ledStatus[1]);
                                copy_to_user(buf, r, strlen(r) + 1);
                                printk("%s", r);
				break;
			case LED3:
				snprintf(r, sizeof(r), "LED3(GPIO=%d) Status: %d", gpio, ledStatus[2]);
                                copy_to_user(buf, r, strlen(r) + 1);
                                printk("%s", r);
				break;
			case LED4:
				snprintf(r, sizeof(r), "LED4(GPIO=%d) Status: %d", gpio, ledStatus[3]);
                                copy_to_user(buf, r, strlen(r) + 1);
                                printk("%s", r);
				break;
			}
		}
		else {
			switch(gpio) {
			case LED1:
				ledStatus[0] = status;
				gpio_set_value(LED1, status);
				break;
			case LED2:
				ledStatus[1] = status;
				gpio_set_value(LED2, status);
				break;
			case LED3:
				ledStatus[2] = status;
				gpio_set_value(LED3, status);
				break;
			case LED4:
				ledStatus[3] = status;
				gpio_set_value(LED4, status);
				break;
			}
		}
	}
	return count;
}

long drv_ioctl(struct file *filp, unsigned int cmd,unsigned long arg)
{
	printk("Enter I/O Control function\n");
	printk("device ioctl\n");
	return 0;
}

static int drv_open(struct inode *inode, struct file *filp)
{
	printk("Enter Open function\n");
	printk("device open\n");
	return 0;
}

static int drv_release(struct inode *inode, struct file *filp)
{
	printk("Enter Release function\n");
	printk("device close\n");
	return 0;
}

struct file_operations drv_fops =
{
		read: drv_read,
		write: drv_write,
		unlocked_ioctl: drv_ioctl,
		open: drv_open,
		release: drv_release,
};

static int demo_init(void)
{		
	char* ledName[4] = {"LED1", "LED2", "LED3", "LED4"};
	//Initialize GPIO pins
	int i = 0;
	for(i = 0; i < 4; i++) {
		if(gpio_is_valid(gpioPin[i]) == 0) {
			printk("gpio%d is invaild", gpioPin[i]);
			return (-EBUSY);
		}
		if(gpio_request(gpioPin[i], ledName[i]) < 0) {
			printk("gpio%d request failed", gpioPin[i]);
			return (-EBUSY);
		}

		//Turn off gpio
		gpio_direction_output(gpioPin[i], 0);
		gpio_export(gpioPin[i], false);
	}
	//regist driver
	if(register_chrdev(MAJOR_NUM, "demo", &drv_fops)<0)
	{
		printk("<1>%s: can't get major %d\n", MODULE_NAME, MAJOR_NUM);
		return (-EBUSY);
	}
	printk("<1>%s: started\n", MODULE_NAME);
	return 0;
}


static void demo_exit(void)
{
	//Free GPIO pins
	int i = 0;
	for(i = 0; i < 4; i++) {
		gpio_free(gpioPin[i]);
	}
	unregister_chrdev(MAJOR_NUM,"demo");
	printk("<1>%s: removed\n", MODULE_NAME);
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("Dual BSD/GPL");
