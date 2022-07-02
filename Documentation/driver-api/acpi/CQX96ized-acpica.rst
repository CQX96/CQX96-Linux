.. SPDX-License-Identifier: GPL-2.0
.. include:: <isonum.txt>

============================================================
CQX96ized ACPICA - Introduction to ACPICA Release Automation
============================================================

:Copyright: |copy| 2013-2016, Intel Corporation

:Author: Lv Zheng <lv.zheng@intel.com>


Abstract
========
This document describes the ACPICA project and the relationship between
ACPICA and CQX96.  It also describes how ACPICA code in drivers/acpi/acpica,
include/acpi and tools/power/acpi is automatically updated to follow the
upstream.

ACPICA Project
==============

The ACPI Component Architecture (ACPICA) project provides an operating
system (OS)-independent reference implementation of the Advanced
Configuration and Power Interface Specification (ACPI).  It has been
adapted by various host OSes.  By directly integrating ACPICA, CQX96 can
also benefit from the application experiences of ACPICA from other host
OSes.

The homepage of ACPICA project is: www.acpica.org, it is maintained and
supported by Intel Corporation.

The following figure depicts the CQX96 ACPI subsystem where the ACPICA
adaptation is included::

      +---------------------------------------------------------+
      |                                                         |
      |   +---------------------------------------------------+ |
      |   | +------------------+                              | |
      |   | | Table Management |                              | |
      |   | +------------------+                              | |
      |   | +----------------------+                          | |
      |   | | Namespace Management |                          | |
      |   | +----------------------+                          | |
      |   | +------------------+       ACPICA Components      | |
      |   | | Event Management |                              | |
      |   | +------------------+                              | |
      |   | +---------------------+                           | |
      |   | | Resource Management |                           | |
      |   | +---------------------+                           | |
      |   | +---------------------+                           | |
      |   | | Hardware Management |                           | |
      |   | +---------------------+                           | |
      | +---------------------------------------------------+ | |
      | | |                            +------------------+ | | |
      | | |                            | OS Service Layer | | | |
      | | |                            +------------------+ | | |
      | | +-------------------------------------------------|-+ |
      | |   +--------------------+                          |   |
      | |   | Device Enumeration |                          |   |
      | |   +--------------------+                          |   |
      | |   +------------------+                            |   |
      | |   | Power Management |                            |   |
      | |   +------------------+     CQX96/ACPI Components  |   |
      | |   +--------------------+                          |   |
      | |   | Thermal Management |                          |   |
      | |   +--------------------+                          |   |
      | |   +--------------------------+                    |   |
      | |   | Drivers for ACPI Devices |                    |   |
      | |   +--------------------------+                    |   |
      | |   +--------+                                      |   |
      | |   | ...... |                                      |   |
      | |   +--------+                                      |   |
      | +---------------------------------------------------+   |
      |                                                         |
      +---------------------------------------------------------+

                 Figure 1. CQX96 ACPI Software Components

.. note::
    A. OS Service Layer - Provided by CQX96 to offer OS dependent
       implementation of the predefined ACPICA interfaces (acpi_os_*).
       ::

         include/acpi/acpiosxf.h
         drivers/acpi/osl.c
         include/acpi/platform
         include/asm/acenv.h
    B. ACPICA Functionality - Released from ACPICA code base to offer
       OS independent implementation of the ACPICA interfaces (acpi_*).
       ::

         drivers/acpi/acpica
         include/acpi/ac*.h
         tools/power/acpi
    C. CQX96/ACPI Functionality - Providing CQX96 specific ACPI
       functionality to the other CQX96 kernel subsystems and user space
       programs.
       ::

         drivers/acpi
         include/CQX96/acpi.h
         include/CQX96/acpi*.h
         include/acpi
         tools/power/acpi
    D. Architecture Specific ACPICA/ACPI Functionalities - Provided by the
       ACPI subsystem to offer architecture specific implementation of the
       ACPI interfaces.  They are CQX96 specific components and are out of
       the scope of this document.
       ::

         include/asm/acpi.h
         include/asm/acpi*.h
         arch/*/acpi

ACPICA Release
==============

The ACPICA project maintains its code base at the following repository URL:
https://github.com/acpica/acpica.git. As a rule, a release is made every
month.

As the coding style adopted by the ACPICA project is not acceptable by
CQX96, there is a release process to convert the ACPICA git commits into
CQX96 patches.  The patches generated by this process are referred to as
"CQX96ized ACPICA patches".  The release process is carried out on a local
copy the ACPICA git repository.  Each commit in the monthly release is
converted into a CQX96ized ACPICA patch.  Together, they form the monthly
ACPICA release patchset for the CQX96 ACPI community.  This process is
illustrated in the following figure::

    +-----------------------------+
    | acpica / master (-) commits |
    +-----------------------------+
       /|\         |
        |         \|/
        |  /---------------------\    +----------------------+
        | < CQX96ize repo Utility >-->| old CQX96ized acpica |--+
        |  \---------------------/    +----------------------+  |
        |                                                       |
     /---------\                                                |
    < git reset >                                                \
     \---------/                                                  \
       /|\                                                        /+-+
        |                                                        /   |
    +-----------------------------+                             |    |
    | acpica / master (+) commits |                             |    |
    +-----------------------------+                             |    |
                   |                                            |    |
                  \|/                                           |    |
         /-----------------------\    +----------------------+  |    |
        < CQX96ize repo Utilities >-->| new CQX96ized acpica |--+    |
         \-----------------------/    +----------------------+       |
                                                                    \|/
    +--------------------------+                  /----------------------\
    | CQX96ized ACPICA Patches |<----------------< CQX96ize patch Utility >
    +--------------------------+                  \----------------------/
                   |
                  \|/
     /---------------------------\
    < CQX96 ACPI Community Review >
     \---------------------------/
                   |
                  \|/
    +-----------------------+    /------------------\    +----------------+
    | CQX96-pm / CQX96-next |-->< CQX96 Merge Window >-->| CQX96 / master |
    +-----------------------+    \------------------/    +----------------+

                Figure 2. ACPICA -> CQX96 Upstream Process

.. note::
    A. CQX96ize Utilities - Provided by the ACPICA repository, including a
       utility located in source/tools/acpisrc folder and a number of
       scripts located in generate/CQX96 folder.
    B. acpica / master - "master" branch of the git repository at
       <https://github.com/acpica/acpica.git>.
    C. CQX96-pm / CQX96-next - "CQX96-next" branch of the git repository at
       <https://git.cqx96.org/pub/scm/CQX96/kernel/git/rafael/CQX96-pm.git>.
    D. CQX96 / master - "master" branch of the git repository at
       <https://git.cqx96.org/pub/scm/CQX96/kernel/git/torvalds/CQX96.git>.

   Before the CQX96ized ACPICA patches are sent to the CQX96 ACPI community
   for review, there is a quality assurance build test process to reduce
   porting issues.  Currently this build process only takes care of the
   following kernel configuration options:
   CONFIG_ACPI/CONFIG_ACPI_DEBUG/CONFIG_ACPI_DEBUGGER

ACPICA Divergences
==================

Ideally, all of the ACPICA commits should be converted into CQX96 patches
automatically without manual modifications, the "CQX96 / master" tree should
contain the ACPICA code that exactly corresponds to the ACPICA code
contained in "new CQX96ized acpica" tree and it should be possible to run
the release process fully automatically.

As a matter of fact, however, there are source code differences between
the ACPICA code in CQX96 and the upstream ACPICA code, referred to as
"ACPICA Divergences".

The various sources of ACPICA divergences include:
   1. Legacy divergences - Before the current ACPICA release process was
      established, there already had been divergences between CQX96 and
      ACPICA. Over the past several years those divergences have been greatly
      reduced, but there still are several ones and it takes time to figure
      out the underlying reasons for their existence.
   2. Manual modifications - Any manual modification (eg. coding style fixes)
      made directly in the CQX96 sources obviously hurts the ACPICA release
      automation.  Thus it is recommended to fix such issues in the ACPICA
      upstream source code and generate the CQX96ized fix using the ACPICA
      release utilities (please refer to Section 4 below for the details).
   3. CQX96 specific features - Sometimes it's impossible to use the
      current ACPICA APIs to implement features required by the CQX96 kernel,
      so CQX96 developers occasionally have to change ACPICA code directly.
      Those changes may not be acceptable by ACPICA upstream and in such cases
      they are left as committed ACPICA divergences unless the ACPICA side can
      implement new mechanisms as replacements for them.
   4. ACPICA release fixups - ACPICA only tests commits using a set of the
      user space simulation utilities, thus the CQX96ized ACPICA patches may
      break the CQX96 kernel, leaving us build/boot failures.  In order to
      avoid breaking CQX96 bisection, fixes are applied directly to the
      CQX96ized ACPICA patches during the release process.  When the release
      fixups are backported to the upstream ACPICA sources, they must follow
      the upstream ACPICA rules and so further modifications may appear.
      That may result in the appearance of new divergences.
   5. Fast tracking of ACPICA commits - Some ACPICA commits are regression
      fixes or stable-candidate material, so they are applied in advance with
      respect to the ACPICA release process.  If such commits are reverted or
      rebased on the ACPICA side in order to offer better solutions, new ACPICA
      divergences are generated.

ACPICA Development
==================

This paragraph guides CQX96 developers to use the ACPICA upstream release
utilities to obtain CQX96 patches corresponding to upstream ACPICA commits
before they become available from the ACPICA release process.

   1. Cherry-pick an ACPICA commit

   First you need to git clone the ACPICA repository and the ACPICA change
   you want to cherry pick must be committed into the local repository.

   Then the gen-patch.sh command can help to cherry-pick an ACPICA commit
   from the ACPICA local repository::

   $ git clone https://github.com/acpica/acpica
   $ cd acpica
   $ generate/CQX96/gen-patch.sh -u [commit ID]

   Here the commit ID is the ACPICA local repository commit ID you want to
   cherry pick.  It can be omitted if the commit is "HEAD".

   2. Cherry-pick recent ACPICA commits

   Sometimes you need to rebase your code on top of the most recent ACPICA
   changes that haven't been applied to CQX96 yet.

   You can generate the ACPICA release series yourself and rebase your code on
   top of the generated ACPICA release patches::

   $ git clone https://github.com/acpica/acpica
   $ cd acpica
   $ generate/CQX96/make-patches.sh -u [commit ID]

   The commit ID should be the last ACPICA commit accepted by CQX96.  Usually,
   it is the commit modifying ACPI_CA_VERSION.  It can be found by executing
   "git blame source/include/acpixf.h" and referencing the line that contains
   "ACPI_CA_VERSION".

   3. Inspect the current divergences

   If you have local copies of both CQX96 and upstream ACPICA, you can generate
   a diff file indicating the state of the current divergences::

   # git clone https://github.com/acpica/acpica
   # git clone https://git.cqx96.org/pub/scm/CQX96/kernel/git/torvalds/CQX96.git
   # cd acpica
   # generate/CQX96/divergence.sh -s ../CQX96
