#pragma once
/* This file is not generated (Not yet!) 
 * it's manually configured to drive dronity build process
 * for bionic. place here paramenters to include or exclude features
 * --- note: do not use the trinity config generation, this file would be overwritted!!
 */

#define VERSION "0.7 alpha - community"

//#define USE_KVM 1 (we don't want to use kvm at the moment, it's not compatible with platform 19)
#define USE_SECCOMP 1
//#define USE_VHOST 1 we don't want to support vhost, not compatible with platform 19
#define CONFIG_COMPAT 1
//are you compiling for platform 21 or above? uncomment this
#define P21 1
//are you compiling for aarch64 64bit armv8? uncommen this
#define AARCH64 1
/* very important, affinity is not supported in android platform <20, depending where you compile, check it */
//#define AFFINITY_SUPPORT 1

/* backtrace is taken out since no support on bionic 
#define USE_BACKTRACE 0
*/

/* the suff below here from the original config.h from trinity!! be carefull
#define USE_IPV6 0
#define USE_PPPOL2TPIN6 0
#define USE_PPPOL2TPV3 0
#define USE_PPPOX_PPTP
#define USE_LLC_OPT_PKTINFO 1
#define USE_CAIF 1
#define USE_IF_ALG 1
#define USE_RDS 1
#define USE_VFIO 1
#define USE_BTRFS 1
#define USE_DRM
#define USE_DRM_EXYNOS 0
#define USE_SNDDRV_COMPRESS_OFFLOAD 0
#define USE_BACKTRACE 0
#define USE_APPLETALK 0
#define USE_NETROM 0
#define USE_ROSE 0
*/
