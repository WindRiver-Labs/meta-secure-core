#
# Copyright (C) 2016-2017 Wind River Systems, Inc.
#

# BUNDLE is used by kernel-initramfs-efi-secure-boot.inc
BUNDLE = "${INSTALL_BUNDLE}"

require ${@bb.utils.contains('DISTRO_FEATURES', 'efi-secure-boot', 'kernel-initramfs-efi-secure-boot.inc', '', d)}
