#include <usb_names.h>

#define MANUFACTURER_NAME	{'c','a','n','t','g','e','t','n','o','s','l','e','e','p'}
#define MANUFACTURER_NAME_LEN	14
#define PRODUCT_NAME		{'d','j','b','o','o','t','h','3'}
#define PRODUCT_NAME_LEN	8

struct usb_string_descriptor_struct usb_string_manufacturer_name = {
  2 + MANUFACTURER_NAME_LEN * 2,
  3,
  MANUFACTURER_NAME
};
struct usb_string_descriptor_struct usb_string_product_name = {
  2 + PRODUCT_NAME_LEN * 2,
  3,
  PRODUCT_NAME
};
struct usb_string_descriptor_struct usb_string_serial_number = {
  12,
  3,
  {
    0,0,7,0,0,0,7,0,0,7  }
};
