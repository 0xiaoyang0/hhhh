#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */

#define RT_NAME_MAX 10
#define RT_ALIGN_SIZE 8
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_USING_OVERFLOW_CHECK
#define RT_USING_HOOK
#define RT_IDEL_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 1024
#define RT_DEBUG

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE
#define RT_USING_SIGNALS

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_MEMHEAP
#define RT_USING_SMALL_MEM
#define RT_USING_HEAP

/* Kernel Device Object */

#define RT_USING_DEVICE
#define RT_USING_INTERRUPT_INFO
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart2"

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 2048
#define RT_MAIN_THREAD_PRIORITY 10

/* C++ features */


/* Command shell */

#define RT_USING_FINSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 4096
#define FINSH_CMD_SIZE 80
#define FINSH_USING_MSH
#define FINSH_USING_MSH_DEFAULT
#define FINSH_ARG_MAX 10

/* Device virtual file system */

#define RT_USING_DFS
#define DFS_USING_WORKDIR
#define DFS_FILESYSTEMS_MAX 2
#define DFS_FILESYSTEM_TYPES_MAX 2
#define DFS_FD_MAX 4
#define RT_USING_DFS_ELMFAT

/* elm-chan's FatFs, Generic FAT Filesystem Module */

#define RT_DFS_ELM_CODE_PAGE 936
#define RT_DFS_ELM_WORD_ACCESS
#define RT_DFS_ELM_USE_LFN_0
#define RT_DFS_ELM_USE_LFN 0
#define RT_DFS_ELM_MAX_LFN 64
#define RT_DFS_ELM_DRIVES 2
#define RT_DFS_ELM_MAX_SECTOR_SIZE 512
#define RT_DFS_ELM_REENTRANT

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_PIPE_BUFSZ 512
#define RT_USING_SERIAL
#define RT_USING_CAN
#define RT_CAN_USING_HDR
#define RT_USING_I2C
#define RT_USING_I2C_BITOPS
#define RT_USING_PIN
#define RT_USING_PWM
#define RT_USING_RTC
#define RT_USING_SPI
#define RT_USING_SPI_MSD

/* Using USB */


/* POSIX layer and C standard library */

#define RT_USING_LIBC
#define RT_USING_PTHREADS

/* Network */

/* Socket abstraction layer */


/* light weight TCP/IP stack */

#define RT_USING_LWIP
#define RT_USING_LWIP141
#define RT_LWIP_IGMP
#define RT_LWIP_ICMP
#define RT_LWIP_DNS

/* Static IPv4 Address */

#define RT_LWIP_IPADDR "193.169.2.254"
#define RT_LWIP_GWADDR "193.169.2.1"
#define RT_LWIP_MSKADDR "255.255.255.0"
#define RT_LWIP_UDP
#define RT_LWIP_TCP
#define RT_MEMP_NUM_NETCONN 8
#define RT_LWIP_PBUF_NUM 4
#define RT_LWIP_RAW_PCB_NUM 4
#define RT_LWIP_UDP_PCB_NUM 4
#define RT_LWIP_TCP_PCB_NUM 3
#define RT_LWIP_TCP_SEG_NUM 40
#define RT_LWIP_TCP_SND_BUF 4096
#define RT_LWIP_TCP_WND 2048
#define RT_LWIP_TCPTHREAD_PRIORITY 12
#define RT_LWIP_TCPTHREAD_MBOX_SIZE 8
#define RT_LWIP_TCPTHREAD_STACKSIZE 4096
#define RT_LWIP_ETHTHREAD_PRIORITY 14
#define RT_LWIP_ETHTHREAD_STACKSIZE 512
#define RT_LWIP_ETHTHREAD_MBOX_SIZE 8
#define LWIP_NETIF_STATUS_CALLBACK 1
#define SO_REUSE 1
#define LWIP_SO_RCVTIMEO 1
#define LWIP_SO_SNDTIMEO 1
#define LWIP_SO_RCVBUF 1
#define LWIP_NETIF_LOOPBACK 0

/* Modbus master and slave stack */


/* AT commands */


/* VBUS(Virtual Software BUS) */


/* Utilities */


/* RT-Thread online packages */

/* IoT - internet of things */


/* Wi-Fi */

/* Marvell WiFi */


/* Wiced WiFi */


/* IoT Cloud */


/* security packages */


/* language packages */

#define PKG_USING_MICROPYTHON

/* Hardware Module */


/* System Module */


/* Tools Module */


/* Network Module */

#define PKG_MICROPYTHON_HEAP_SIZE 8192
#define PKG_USING_MICROPYTHON_LATEST_VERSION

/* multimedia packages */


/* tools packages */


/* system packages */


/* peripheral libraries and drivers */


/* miscellaneous packages */


/* sample package */

/* samples: kernel and components samples */

#define PKG_USING_KERNEL_SAMPLES
#define PKG_USING_KERNEL_SAMPLES_LATEST_VERSION
#define KERNEL_SAMPLES_USING_THREAD
#define KERNEL_SAMPLES_USING_SEMAPHORE
#define KERNEL_SAMPLES_USING_MUTEX
#define KERNEL_SAMPLES_USING_MAILBOX
#define KERNEL_SAMPLES_USING_EVENT
#define KERNEL_SAMPLES_USING_MESSAGEQUEUE
#define KERNEL_SAMPLES_USING_TIMER
#define KERNEL_SAMPLES_USING_HEAP
#define KERNEL_SAMPLES_USING_MEMHEAP
#define KERNEL_SAMPLES_USING_MEMPOOL
#define KERNEL_SAMPLES_USING_IDLEHOOK
#define KERNEL_SAMPLES_USING_SIGNAL
#define KERNEL_SAMPLES_USING_INTERRUPT
#define PKG_USING_FILESYSTEM_SAMPLES
#define PKG_USING_FILESYSTEM_SAMPLES_LATEST_VERSION
#define FILESYSTEM_SAMPLES_USING_READWRITE
#define FILESYSTEM_SAMPLES_USING_STAT
#define FILESYSTEM_SAMPLES_USING_RENAME
#define FILESYSTEM_SAMPLES_USING_MKDIR
#define FILESYSTEM_SAMPLES_USING_OPENDIR
#define FILESYSTEM_SAMPLES_USING_READDIR
#define FILESYSTEM_SAMPLES_USING_TELL_SEEK_DIR
#define PKG_USING_PERIPHERAL_SAMPLES
#define PKG_USING_PERIPHERAL_SAMPLES_LATEST_VERSION
#define PERIPHERAL_SAMPLES_USING_I2C
#define PERIPHERAL_SAMPLES_USING_PIN
#define PERIPHERAL_SAMPLES_USING_SERIAL
#define PERIPHERAL_SAMPLES_USING_SPI

/* example package: hello */

#define PKG_USING_HELLO
#define PKG_USING_HELLO_LATEST_VERSION
#define RT_USING_UART2
#define RT_UART_RX_BUFFER_SIZE 64
#define RT_USING_GMAC_INT_MODE
#define RT_USING_FPU
#define RT_USING_SPI0
#define RT_USING_SPI1
#define RT_USING_I2C1
#define RT_USING_I2C2
#define USING_BXCAN0
#define USING_BXCAN1
#define TINA_USING_TOUCH
#define RT_USING_RTGUI
#define RT_RTC_NAME "rtc"

// <section name="RT_USING_RTGUI" description="RTGUI, a graphic user interface" default="true" >
 #define RT_USING_RTGUI
// <integer name="RTGUI_NAME_MAX" description="Maximal size of RTGUI object name length" default="16" />
#define RTGUI_NAME_MAX	16
// <bool name="RTGUI_USING_FONT16" description="Support 16 weight font" default="true" />
#define RTGUI_USING_FONT16
// <bool name="RTGUI_USING_FONT12" description="Support 12 weight font" default="true" />
#define RTGUI_USING_FONT12
// <bool name="RTGUI_USING_FONTHZ" description="Support Chinese font" default="true" />
#define RTGUI_USING_FONTHZ
// <bool name="RTGUI_USING_DFS_FILERW" description="Using DFS as file interface " default="true" />
#define RTGUI_DEFAULT_FONT_SIZE	16
// <bool name="RTGUI_USING_DFS_FILERW" description="use RT-Thread/DFS as file interface" default="true" />
#define RTGUI_USING_DFS_FILERW
// <bool name="RTGUI_USING_HZ_FILE" description="Using font file as Chinese font" default="false" />
 #define RTGUI_USING_HZ_FILE
// <bool name="RTGUI_USING_HZ_BMP" description="Using Chinese bitmap font" default="true" />
//#define RTGUI_USING_HZ_BMP
// <bool name="RTGUI_USING_SMALL_SIZE" description="Using small size in RTGUI" default="false" />
#define RTGUI_USING_SMALL_SIZE
// <bool name="RTGUI_USING_MOUSE_CURSOR" description="Using mouse cursor in RTGUI" default="false" />
// #define RTGUI_USING_MOUSE_CURSOR
// <bool name="RTGUI_IMAGE_XPM" description="Using xpm image in RTGUI" default="true" />
#define RTGUI_IMAGE_XPM
// <bool name="RTGUI_IMAGE_JPEG" description="Using jpeg image in RTGUI" default="true" />
// #define RTGUI_IMAGE_JPEG
// <bool name="RTGUI_IMAGE_PNG" description="Using png image in RTGUI" default="true" />
// #define RTGUI_IMAGE_PNG
// <bool name="RTGUI_IMAGE_BMP" description="Using bmp image in RTGUI" default="true" />
#define RTGUI_IMAGE_BMP
// </section>

#endif
