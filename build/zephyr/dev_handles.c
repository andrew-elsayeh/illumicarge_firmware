#include <zephyr/device.h>
#include <zephyr/toolchain.h>

/* 1 : /soc/rcc@40021000:
 * Supported:
 *    - /soc/pin-controller@48000000/gpio@48001400
 *    - /soc/pin-controller@48000000/gpio@48001000
 *    - /soc/pin-controller@48000000/gpio@48000c00
 *    - /soc/pin-controller@48000000/gpio@48000800
 *    - /soc/pin-controller@48000000/gpio@48000400
 *    - /soc/pin-controller@48000000/gpio@48000000
 *    - /soc/rcc@40021000/reset-controller
 *    - /soc/serial@40004400
 *    - /soc/serial@40013800
 *    - /soc/adc@50000500
 *    - /soc/adc@50000400
 *    - /soc/adc@50000000
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_9[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, DEVICE_HANDLE_ENDS };

/* 2 : /soc/interrupt-controller@40010400:
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_44[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 3 : /soc/pin-controller@48000000/gpio@48001400:
 * Direct Dependencies:
 *    - /soc/rcc@40021000
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_78[] = { 1, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 4 : /soc/pin-controller@48000000/gpio@48001000:
 * Direct Dependencies:
 *    - /soc/rcc@40021000
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_77[] = { 1, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 5 : /soc/pin-controller@48000000/gpio@48000c00:
 * Direct Dependencies:
 *    - /soc/rcc@40021000
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_76[] = { 1, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 6 : /soc/pin-controller@48000000/gpio@48000800:
 * Direct Dependencies:
 *    - /soc/rcc@40021000
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_29[] = { 1, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 7 : /soc/pin-controller@48000000/gpio@48000400:
 * Direct Dependencies:
 *    - /soc/rcc@40021000
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_75[] = { 1, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 8 : /soc/pin-controller@48000000/gpio@48000000:
 * Direct Dependencies:
 *    - /soc/rcc@40021000
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_32[] = { 1, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 9 : /soc/rcc@40021000/reset-controller:
 * Direct Dependencies:
 *    - /soc/rcc@40021000
 * Supported:
 *    - /soc/serial@40004400
 *    - /soc/serial@40013800
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_47[] = { 1, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, 10, 11, DEVICE_HANDLE_ENDS };

/* 10 : /soc/serial@40004400:
 * Direct Dependencies:
 *    - /soc/rcc@40021000
 *    - /soc/rcc@40021000/reset-controller
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_48[] = { 1, 9, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 11 : /soc/serial@40013800:
 * Direct Dependencies:
 *    - /soc/rcc@40021000
 *    - /soc/rcc@40021000/reset-controller
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_54[] = { 1, 9, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 12 : /soc/adc@50000500:
 * Direct Dependencies:
 *    - /soc/rcc@40021000
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_21[] = { 1, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 13 : /soc/adc@50000400:
 * Direct Dependencies:
 *    - /soc/rcc@40021000
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_19[] = { 1, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 14 : /soc/adc@50000000:
 * Direct Dependencies:
 *    - /soc/rcc@40021000
 */
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_13[] = { 1, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };
