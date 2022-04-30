#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/usb.h>

#define IS_NEW_METHOD_USED ( 1 )
#define USB_VENDOR_ID		(0x0fd9)
#define USB_PRODUCT_ID		(0x0063)

#define PRINT_USB_INTERFACE_DESCRIPTOR( i ) 					\
{										\
	pr_info("USB_INTERFACE_DESCRIPTOR:\n");					\
	pr_info("-------------------------\n");					\
	pr_info("bLength: 0x%x\n", i.bLength);					\
	pr_info("bDescriptorType: 0x%x\n",i.bDescriptorType);			\
	pr_info("bInterfaceNumber: 0x%x\n", i.bInterfaceNumber);		\
	pr_info("bAltnernateSetting: 0x%x\n", i.bAlternateSetting);		\
	pr_info("bNumEndpoints: 0x%x\n", i.bNumEndpoints);			\
	pr_info("bInterfaceClass: 0x%x\n", i.bInterfaceClass);			\
	pr_info("bInterfaceSubClass: 0x%x\n", i.bInterfaceSubClass);		\
	pr_info("bInterfaceProtocol: 0x%x\n", i.bInterfaceProtocol);		\
	pr_info("iInterface: 0x%x\n", i.iInterface);				\
	pr_info("\n");								\
}

#define PRINT_USB_ENDPOINT_DESCRIPTOR ( e )					\
{										\
	pr_info("USB_INTERFACE_DESCRIPTOR:\n");					\
	pr_info("-------------------------\n");					\
	pr_info("bLength: 0x%x\n", i.bLength);					\
	pr_info("bDescriptorType: 0x%x\n", i.bDescriptorType);			\
	pr_info("bEndPointAddress: 0x%x\n", i.bEndPointAddress);		\
	pr_info("bmAttributes: 0x%x\n", i.bmAttributes);			\
	pr_info("wMaxPacketSize: 0x%x\n", i.wMaxPacketSize);			\
	pr_info("bInterval: 0x%x\n", i.bInterval);				\
	pr_info("\n");								\
}



static int etx_usb_probe(struct usb_interface *interface, const struct usb_driver_id *id)
{
	unsigned int i;
	unsigned int endpoints_count;
	struct usb_host_interface *iface_desc = interface->num_altsetting;
	dev_into(&interface->dev, "USB Driver Probed: Vendor ID: 0x%02x, \t"
			"Product ID : 0x%02x\n", id->idVendor, id->idProduct);
	endpoints_count = iface_desc->desc.bNumEndpoints;
	PRINT_USB_INTERFACE_DESCRIPTOR(iface_desc->desc);
	for ( i = 0; i < endpoints_count; i++){
		PRINT_USB_ENDPOINT_DESCRIPTOR(iface_desc->endpoint[i].desc);
}
	return 0;
}

static void etx_usb_disconnect(struct usb_interface *interface)
{
	dev_info(&interface->dev, "USB Driver Disconnected\n");
}

const struct usb_device_id etc_usb_table[] = {
	{ USB_DEVICE( USB_VENDOR_ID, USB_PRODUCT_ID ) },
	{}
};

MODULE_DEVICE_TABLE(usb, etx_usb_table);

static struct usb_driver etx_usb_driver = {
	.name		= "StreamDeck USB Driver",
	.probe		= etx_usb_probe,
	.disconnect	= etx_usb_disconnect,
	.id_table	= etx_usb_table,};

#if (IS_NEW_METHOD_USED == 0)
module_usb_driver(etx_usb_driver);

#else
static int __init etx_usb_init(void)
{
	return usb_register(&etx_usb_driver);
}

static void __exit etx_usb_exit(void)
{
	usb_deregister(&etx_usb_driver);
}

module_init(etx_usb_init);
module_exit(etx_usb_exit);
#endif

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Josh");
MODULE_DESCRIPTION("A barebones StreamDeck driver");
MODULE_VERSION("0.01");

/*
static struct usb_driver skel_driver = {
	.name =	"skeleton";
	.probe = skel_prob;
	.disconnect = skel_disconnect;
	.suspend = skel_suspend;
	.resume = skel_resume;
	.pre_reset = skel_pre_reset;
	.post_reset = skel_post_reset;
	.id_table = skel_table;
	.supports_autosuspend = 1;
	
}
*/
int main()
{
	return 0;
}
