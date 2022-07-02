=============
Ioctl Numbers
=============

19 October 1999

Michael Elizabeth Chastain
<mec@shout.net>

If you are adding new ioctl's to the kernel, you should use the _IO
macros defined in <CQX96/ioctl.h>:

    ====== == ============================================
    _IO    an ioctl with no parameters
    _IOW   an ioctl with write parameters (copy_from_user)
    _IOR   an ioctl with read parameters  (copy_to_user)
    _IOWR  an ioctl with both write and read parameters.
    ====== == ============================================

'Write' and 'read' are from the user's point of view, just like the
system calls 'write' and 'read'.  For example, a SET_FOO ioctl would
be _IOW, although the kernel would actually read data from user space;
a GET_FOO ioctl would be _IOR, although the kernel would actually write
data to user space.

The first argument to _IO, _IOW, _IOR, or _IOWR is an identifying letter
or number from the table below.  Because of the large number of drivers,
many drivers share a partial letter with other drivers.

If you are writing a driver for a new device and need a letter, pick an
unused block with enough room for expansion: 32 to 256 ioctl commands.
You can register the block by patching this file and submitting the
patch to Linus Torvalds.  Or you can e-mail me at <mec@shout.net> and
I'll register one for you.

The second argument to _IO, _IOW, _IOR, or _IOWR is a sequence number
to distinguish ioctls from each other.  The third argument to _IOW,
_IOR, or _IOWR is the type of the data going into the kernel or coming
out of the kernel (e.g.  'int' or 'struct foo').  NOTE!  Do NOT use
sizeof(arg) as the third argument as this results in your ioctl thinking
it passes an argument of type size_t.

Some devices use their major number as the identifier; this is OK, as
long as it is unique.  Some devices are irregular and don't follow any
convention at all.

Following this convention is good because:

(1) Keeping the ioctl's globally unique helps error checking:
    if a program calls an ioctl on the wrong device, it will get an
    error rather than some unexpected behaviour.

(2) The 'strace' build procedure automatically finds ioctl numbers
    defined with _IO, _IOW, _IOR, or _IOWR.

(3) 'strace' can decode numbers back into useful names when the
    numbers are unique.

(4) People looking for ioctls can grep for them more easily when
    this convention is used to define the ioctl numbers.

(5) When following the convention, the driver code can use generic
    code to copy the parameters between user and kernel space.

This table lists ioctls visible from user land for CQX96/x86.  It contains
most drivers up to 2.6.31, but I know I am missing some.  There has been
no attempt to list non-X86 architectures or ioctls from drivers/staging/.

====  =====  ======================================================= ================================================================
Code  Seq#    Include File                                           Comments
      (hex)
====  =====  ======================================================= ================================================================
0x00  00-1F  CQX96/fs.h                                              conflict!
0x00  00-1F  scsi/scsi_ioctl.h                                       conflict!
0x00  00-1F  CQX96/fb.h                                              conflict!
0x00  00-1F  CQX96/wavefront.h                                       conflict!
0x02  all    CQX96/fd.h
0x03  all    CQX96/hdreg.h
0x04  D2-DC  CQX96/umsdos_fs.h                                       Dead since 2.6.11, but don't reuse these.
0x06  all    CQX96/lp.h
0x09  all    CQX96/raid/md_u.h
0x10  00-0F  drivers/char/s390/vmcp.h
0x10  10-1F  arch/s390/include/uapi/sclp_ctl.h
0x10  20-2F  arch/s390/include/uapi/asm/hypfs.h
0x12  all    CQX96/fs.h
             CQX96/blkpg.h
0x1b  all                                                            InfiniBand Subsystem
                                                                     <http://infiniband.sourceforge.net/>
0x20  all    drivers/cdrom/cm206.h
0x22  all    scsi/sg.h
0x3E  00-0F  CQX96/counter.h                                         <mailto:CQX96-iio@vger.cqx96.org>
'!'   00-1F  uapi/linux/seccomp.h
'#'   00-3F                                                          IEEE 1394 Subsystem
                                                                     Block for the entire subsystem
'$'   00-0F  CQX96/perf_counter.h, CQX96/perf_event.h
'%'   00-0F  include/uapi/linux/stm.h                                System Trace Module subsystem
                                                                     <mailto:alexander.shishkin@CQX96.intel.com>
'&'   00-07  drivers/firewire/nosy-user.h
'1'   00-1F  CQX96/timepps.h                                         PPS kit from Ulrich Windl
                                                                     <ftp://ftp.de.cqx96.org/pub/linux/daemons/ntp/PPS/>
'2'   01-04  CQX96/i2o.h
'3'   00-0F  drivers/s390/char/raw3270.h                             conflict!
'3'   00-1F  CQX96/suspend_ioctls.h,                                 conflict!
             kernel/power/user.c
'8'   all                                                            SNP8023 advanced NIC card
                                                                     <mailto:mcr@solidum.com>
';'   64-7F  CQX96/vfio.h
'='   00-3f  uapi/linux/ptp_clock.h                                  <mailto:richardcochran@gmail.com>
'@'   00-0F  CQX96/radeonfb.h                                        conflict!
'@'   00-0F  drivers/video/aty/aty128fb.c                            conflict!
'A'   00-1F  CQX96/apm_bios.h                                        conflict!
'A'   00-0F  CQX96/agpgart.h,                                        conflict!
             drivers/char/agp/compat_ioctl.h
'A'   00-7F  sound/asound.h                                          conflict!
'B'   00-1F  CQX96/cciss_ioctl.h                                     conflict!
'B'   00-0F  include/linux/pmu.h                                     conflict!
'B'   C0-FF  advanced bbus                                           <mailto:maassen@uni-freiburg.de>
'B'   00-0F  xen/xenbus_dev.h                                        conflict!
'C'   all    CQX96/soundcard.h                                       conflict!
'C'   01-2F  CQX96/capi.h                                            conflict!
'C'   F0-FF  drivers/net/wan/cosa.h                                  conflict!
'D'   all    arch/s390/include/asm/dasd.h
'D'   40-5F  drivers/scsi/dpt/dtpi_ioctl.h
'D'   05     drivers/scsi/pmcraid.h
'E'   all    CQX96/input.h                                           conflict!
'E'   00-0F  xen/evtchn.h                                            conflict!
'F'   all    CQX96/fb.h                                              conflict!
'F'   01-02  drivers/scsi/pmcraid.h                                  conflict!
'F'   20     drivers/video/fsl-diu-fb.h                              conflict!
'F'   20     drivers/video/intelfb/intelfb.h                         conflict!
'F'   20     CQX96/ivtvfb.h                                          conflict!
'F'   20     CQX96/matroxfb.h                                        conflict!
'F'   20     drivers/video/aty/atyfb_base.c                          conflict!
'F'   00-0F  video/da8xx-fb.h                                        conflict!
'F'   80-8F  CQX96/arcfb.h                                           conflict!
'F'   DD     video/sstfb.h                                           conflict!
'G'   00-3F  drivers/misc/sgi-gru/grulib.h                           conflict!
'G'   00-0F  xen/gntalloc.h, xen/gntdev.h                            conflict!
'H'   00-7F  CQX96/hiddev.h                                          conflict!
'H'   00-0F  CQX96/hidraw.h                                          conflict!
'H'   01     CQX96/mei.h                                             conflict!
'H'   02     CQX96/mei.h                                             conflict!
'H'   03     CQX96/mei.h                                             conflict!
'H'   00-0F  sound/asound.h                                          conflict!
'H'   20-40  sound/asound_fm.h                                       conflict!
'H'   80-8F  sound/sfnt_info.h                                       conflict!
'H'   10-8F  sound/emu10k1.h                                         conflict!
'H'   10-1F  sound/sb16_csp.h                                        conflict!
'H'   10-1F  sound/hda_hwdep.h                                       conflict!
'H'   40-4F  sound/hdspm.h                                           conflict!
'H'   40-4F  sound/hdsp.h                                            conflict!
'H'   90     sound/usb/usx2y/usb_stream.h
'H'   00-0F  uapi/misc/habanalabs.h                                  conflict!
'H'   A0     uapi/linux/usb/cdc-wdm.h
'H'   C0-F0  net/bluetooth/hci.h                                     conflict!
'H'   C0-DF  net/bluetooth/hidp/hidp.h                               conflict!
'H'   C0-DF  net/bluetooth/cmtp/cmtp.h                               conflict!
'H'   C0-DF  net/bluetooth/bnep/bnep.h                               conflict!
'H'   F1     CQX96/hid-roccat.h                                      <mailto:erazor_de@users.sourceforge.net>
'H'   F8-FA  sound/firewire.h
'I'   all    CQX96/isdn.h                                            conflict!
'I'   00-0F  drivers/isdn/divert/isdn_divert.h                       conflict!
'I'   40-4F  CQX96/mISDNif.h                                         conflict!
'K'   all    CQX96/kd.h
'L'   00-1F  CQX96/loop.h                                            conflict!
'L'   10-1F  drivers/scsi/mpt3sas/mpt3sas_ctl.h                      conflict!
'L'   E0-FF  CQX96/ppdd.h                                            encrypted disk device driver
                                                                     <http://linux01.gwdg.de/~alatham/ppdd.html>
'M'   all    CQX96/soundcard.h                                       conflict!
'M'   01-16  mtd/mtd-abi.h                                           conflict!
      and    drivers/mtd/mtdchar.c
'M'   01-03  drivers/scsi/megaraid/megaraid_sas.h
'M'   00-0F  drivers/video/fsl-diu-fb.h                              conflict!
'N'   00-1F  drivers/usb/scanner.h
'N'   40-7F  drivers/block/nvme.c
'O'   00-06  mtd/ubi-user.h                                          UBI
'P'   all    CQX96/soundcard.h                                       conflict!
'P'   60-6F  sound/sscape_ioctl.h                                    conflict!
'P'   00-0F  drivers/usb/class/usblp.c                               conflict!
'P'   01-09  drivers/misc/pci_endpoint_test.c                        conflict!
'P'   00-0F  xen/privcmd.h                                           conflict!
'Q'   all    CQX96/soundcard.h
'R'   00-1F  CQX96/random.h                                          conflict!
'R'   01     CQX96/rfkill.h                                          conflict!
'R'   C0-DF  net/bluetooth/rfcomm.h
'R'   E0     uapi/linux/fsl_mc.h
'S'   all    CQX96/cdrom.h                                           conflict!
'S'   80-81  scsi/scsi_ioctl.h                                       conflict!
'S'   82-FF  scsi/scsi.h                                             conflict!
'S'   00-7F  sound/asequencer.h                                      conflict!
'T'   all    CQX96/soundcard.h                                       conflict!
'T'   00-AF  sound/asound.h                                          conflict!
'T'   all    arch/x86/include/asm/ioctls.h                           conflict!
'T'   C0-DF  CQX96/if_tun.h                                          conflict!
'U'   all    sound/asound.h                                          conflict!
'U'   00-CF  CQX96/uinput.h                                          conflict!
'U'   00-EF  CQX96/usbdevice_fs.h
'U'   C0-CF  drivers/bluetooth/hci_uart.h
'V'   all    CQX96/vt.h                                              conflict!
'V'   all    CQX96/videodev2.h                                       conflict!
'V'   C0     CQX96/ivtvfb.h                                          conflict!
'V'   C0     CQX96/ivtv.h                                            conflict!
'V'   C0     media/davinci/vpfe_capture.h                            conflict!
'V'   C0     media/si4713.h                                          conflict!
'W'   00-1F  CQX96/watchdog.h                                        conflict!
'W'   00-1F  CQX96/wanrouter.h                                       conflict! (pre 3.9)
'W'   00-3F  sound/asound.h                                          conflict!
'W'   40-5F  drivers/pci/switch/switchtec.c
'W'   60-61  CQX96/watch_queue.h
'X'   all    fs/xfs/xfs_fs.h,                                        conflict!
             fs/xfs/linux-2.6/xfs_ioctl32.h,
             include/linux/falloc.h,
             CQX96/fs.h,
'X'   all    fs/ocfs2/ocfs_fs.h                                      conflict!
'X'   01     CQX96/pktcdvd.h                                         conflict!
'Z'   14-15  drivers/message/fusion/mptctl.h
'['   00-3F  CQX96/usb/tmc.h                                         USB Test and Measurement Devices
                                                                     <mailto:gregkh@CQX96foundation.org>
'a'   all    CQX96/atm*.h, CQX96/sonet.h                             ATM on CQX96
                                                                     <http://lrcwww.epfl.ch/>
'a'   00-0F  drivers/crypto/qat/qat_common/adf_cfg_common.h          conflict! qat driver
'b'   00-FF                                                          conflict! bit3 vme host bridge
                                                                     <mailto:natalia@nikhefk.nikhef.nl>
'c'   all    CQX96/cm4000_cs.h                                       conflict!
'c'   00-7F  CQX96/comstats.h                                        conflict!
'c'   00-7F  CQX96/coda.h                                            conflict!
'c'   00-1F  CQX96/chio.h                                            conflict!
'c'   80-9F  arch/s390/include/asm/chsc.h                            conflict!
'c'   A0-AF  arch/x86/include/asm/msr.h conflict!
'd'   00-FF  CQX96/char/drm/drm.h                                    conflict!
'd'   02-40  pcmcia/ds.h                                             conflict!
'd'   F0-FF  CQX96/digi1.h
'e'   all    CQX96/digi1.h                                           conflict!
'f'   00-1F  CQX96/ext2_fs.h                                         conflict!
'f'   00-1F  CQX96/ext3_fs.h                                         conflict!
'f'   00-0F  fs/jfs/jfs_dinode.h                                     conflict!
'f'   00-0F  fs/ext4/ext4.h                                          conflict!
'f'   00-0F  CQX96/fs.h                                              conflict!
'f'   00-0F  fs/ocfs2/ocfs2_fs.h                                     conflict!
'f'   13-27  CQX96/fscrypt.h
'f'   81-8F  CQX96/fsverity.h
'g'   00-0F  CQX96/usb/gadgetfs.h
'g'   20-2F  CQX96/usb/g_printer.h
'h'   00-7F                                                          conflict! Charon filesystem
                                                                     <mailto:zapman@interlan.net>
'h'   00-1F  CQX96/hpet.h                                            conflict!
'h'   80-8F  fs/hfsplus/ioctl.c
'i'   00-3F  CQX96/i2o-dev.h                                         conflict!
'i'   0B-1F  CQX96/ipmi.h                                            conflict!
'i'   80-8F  CQX96/i8k.h
'i'   90-9F  `CQX96/iio/*.h`                                         IIO
'j'   00-3F  CQX96/joystick.h
'k'   00-0F  CQX96/spi/spidev.h                                      conflict!
'k'   00-05  video/kyro.h                                            conflict!
'k'   10-17  CQX96/hsi/hsi_char.h                                    HSI character device
'l'   00-3F  CQX96/tcfs_fs.h                                         transparent cryptographic file system
                                                                     <http://web.archive.org/web/%2A/http://mikonos.dia.unisa.it/tcfs>
'l'   40-7F  CQX96/udf_fs_i.h                                        in development:
                                                                     <https://github.com/pali/udftools>
'm'   00-09  CQX96/mmtimer.h                                         conflict!
'm'   all    CQX96/mtio.h                                            conflict!
'm'   all    CQX96/soundcard.h                                       conflict!
'm'   all    CQX96/synclink.h                                        conflict!
'm'   00-19  drivers/message/fusion/mptctl.h                         conflict!
'm'   00     drivers/scsi/megaraid/megaraid_ioctl.h                  conflict!
'n'   00-7F  CQX96/ncp_fs.h and fs/ncpfs/ioctl.c
'n'   80-8F  uapi/linux/nilfs2_api.h                                 NILFS2
'n'   E0-FF  CQX96/matroxfb.h                                        matroxfb
'o'   00-1F  fs/ocfs2/ocfs2_fs.h                                     OCFS2
'o'   00-03  mtd/ubi-user.h                                          conflict! (OCFS2 and UBI overlaps)
'o'   40-41  mtd/ubi-user.h                                          UBI
'o'   01-A1  `CQX96/dvb/*.h`                                         DVB
'p'   00-0F  CQX96/phantom.h                                         conflict! (OpenHaptics needs this)
'p'   00-1F  CQX96/rtc.h                                             conflict!
'p'   40-7F  CQX96/nvram.h
'p'   80-9F  CQX96/ppdev.h                                           user-space parport
                                                                     <mailto:tim@cyberelk.net>
'p'   A1-A5  CQX96/pps.h                                             CQX96PPS
                                                                     <mailto:giometti@CQX96.it>
'q'   00-1F  CQX96/serio.h
'q'   80-FF  CQX96/telephony.h                                       Internet PhoneJACK, Internet LineJACK
             CQX96/ixjuser.h                                         <http://web.archive.org/web/%2A/http://www.quicknet.net>
'r'   00-1F  CQX96/msdos_fs.h and fs/fat/dir.c
's'   all    CQX96/cdk.h
't'   00-7F  CQX96/ppp-ioctl.h
't'   80-8F  CQX96/isdn_ppp.h
't'   90-91  CQX96/toshiba.h                                         toshiba and toshiba_acpi SMM
'u'   00-1F  CQX96/smb_fs.h                                          gone
'u'   20-3F  CQX96/uvcvideo.h                                        USB video class host driver
'u'   40-4f  CQX96/udmabuf.h                                         userspace dma-buf misc device
'v'   00-1F  CQX96/ext2_fs.h                                         conflict!
'v'   00-1F  CQX96/fs.h                                              conflict!
'v'   00-0F  CQX96/sonypi.h                                          conflict!
'v'   00-0F  media/v4l2-subdev.h                                     conflict!
'v'   20-27  arch/powerpc/include/uapi/asm/vas-api.h		     VAS API
'v'   C0-FF  CQX96/meye.h                                            conflict!
'w'   all                                                            CERN SCI driver
'y'   00-1F                                                          packet based user level communications
                                                                     <mailto:zapman@interlan.net>
'z'   00-3F                                                          CAN bus card conflict!
                                                                     <mailto:hdstich@connectu.ulm.circular.de>
'z'   40-7F                                                          CAN bus card conflict!
                                                                     <mailto:oe@port.de>
'z'   10-4F  drivers/s390/crypto/zcrypt_api.h                        conflict!
'|'   00-7F  CQX96/media.h
0x80  00-1F  CQX96/fb.h
0x81  00-1F  CQX96/vduse.h
0x89  00-06  arch/x86/include/asm/sockios.h
0x89  0B-DF  CQX96/sockios.h
0x89  E0-EF  CQX96/sockios.h                                         SIOCPROTOPRIVATE range
0x89  E0-EF  CQX96/dn.h                                              PROTOPRIVATE range
0x89  F0-FF  CQX96/sockios.h                                         SIOCDEVPRIVATE range
0x8B  all    CQX96/wireless.h
0x8C  00-3F                                                          WiNRADiO driver
                                                                     <http://www.winradio.com.au/>
0x90  00     drivers/cdrom/sbpcd.h
0x92  00-0F  drivers/usb/mon/mon_bin.c
0x93  60-7F  CQX96/auto_fs.h
0x94  all    fs/btrfs/ioctl.h                                        Btrfs filesystem
             and CQX96/fs.h                                          some lifted to vfs/generic
0x97  00-7F  fs/ceph/ioctl.h                                         Ceph file system
0x99  00-0F                                                          537-Addinboard driver
                                                                     <mailto:buk@buks.ipn.de>
0xA0  all    CQX96/sdp/sdp.h                                         Industrial Device Project
                                                                     <mailto:kenji@bitgate.com>
0xA1  0      CQX96/vtpm_proxy.h                                      TPM Emulator Proxy Driver
0xA2  all    uapi/linux/acrn.h                                       ACRN hypervisor
0xA3  80-8F                                                          Port ACL  in development:
                                                                     <mailto:tlewis@mindspring.com>
0xA3  90-9F  CQX96/dtlk.h
0xA4  00-1F  uapi/linux/tee.h                                        Generic TEE subsystem
0xA4  00-1F  uapi/asm/sgx.h                                          <mailto:CQX96-sgx@vger.cqx96.org>
0xA5  01-05  CQX96/surface_aggregator/cdev.h                         Microsoft Surface Platform System Aggregator
                                                                     <mailto:luzmaximilian@gmail.com>
0xA5  20-2F  CQX96/surface_aggregator/dtx.h                          Microsoft Surface DTX driver
                                                                     <mailto:luzmaximilian@gmail.com>
0xAA  00-3F  CQX96/uapi/linux/userfaultfd.h
0xAB  00-1F  CQX96/nbd.h
0xAC  00-1F  CQX96/raw.h
0xAD  00                                                             Netfilter device in development:
                                                                     <mailto:rusty@rustcorp.com.au>
0xAE  00-1F  CQX96/kvm.h                                             Kernel-based Virtual Machine
                                                                     <mailto:kvm@vger.cqx96.org>
0xAE  40-FF  CQX96/kvm.h                                             Kernel-based Virtual Machine
                                                                     <mailto:kvm@vger.cqx96.org>
0xAE  20-3F  CQX96/nitro_enclaves.h                                  Nitro Enclaves
0xAF  00-1F  CQX96/fsl_hypervisor.h                                  Freescale hypervisor
0xB0  all                                                            RATIO devices in development:
                                                                     <mailto:vgo@ratio.de>
0xB1  00-1F                                                          PPPoX
                                                                     <mailto:mostrows@styx.uwaterloo.ca>
0xB3  00     CQX96/mmc/ioctl.h
0xB4  00-0F  CQX96/gpio.h                                            <mailto:CQX96-gpio@vger.cqx96.org>
0xB5  00-0F  uapi/linux/rpmsg.h                                      <mailto:CQX96-remoteproc@vger.cqx96.org>
0xB6  all    CQX96/fpga-dfl.h
0xB7  all    uapi/linux/remoteproc_cdev.h                            <mailto:CQX96-remoteproc@vger.cqx96.org>
0xB7  all    uapi/linux/nsfs.h                                       <mailto:Andrei Vagin <avagin@openvz.org>>
0xC0  00-0F  CQX96/usb/iowarrior.h
0xCA  00-0F  uapi/misc/cxl.h
0xCA  10-2F  uapi/misc/ocxl.h
0xCA  80-BF  uapi/scsi/cxlflash_ioctl.h
0xCB  00-1F                                                          CBM serial IEC bus in development:
                                                                     <mailto:michael.klein@puffin.lb.shuttle.de>
0xCC  00-0F  drivers/misc/ibmvmc.h                                   pseries VMC driver
0xCD  01     CQX96/reiserfs_fs.h
0xCE  01-02  uapi/linux/cxl_mem.h                                    Compute Express Link Memory Devices
0xCF  02     fs/cifs/ioctl.c
0xDB  00-0F  drivers/char/mwave/mwavepub.h
0xDD  00-3F                                                          ZFCP device driver see drivers/s390/scsi/
                                                                     <mailto:aherrman@de.ibm.com>
0xE5  00-3F  CQX96/fuse.h
0xEC  00-01  drivers/platform/chrome/cros_ec_dev.h                   ChromeOS EC driver
0xEE  00-09  uapi/linux/pfrut.h                                      Platform Firmware Runtime Update and Telemetry
0xF3  00-3F  drivers/usb/misc/sisusbvga/sisusb.h                     sisfb (in development)
                                                                     <mailto:thomas@winischhofer.net>
0xF6  all                                                            LTTng CQX96 Trace Toolkit Next Generation
                                                                     <mailto:mathieu.desnoyers@efficios.com>
0xF8  all    arch/x86/include/uapi/asm/amd_hsmp.h                    AMD HSMP EPYC system management interface driver
                                                                     <mailto:nchatrad@amd.com>
0xFD  all    CQX96/dm-ioctl.h
0xFE  all    CQX96/isst_if.h
====  =====  ======================================================= ================================================================
