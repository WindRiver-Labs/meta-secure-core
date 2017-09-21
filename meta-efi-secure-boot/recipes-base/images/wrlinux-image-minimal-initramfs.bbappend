#
# Copyright (C) 2017 Wind River Systems, Inc.
#

require ${@bb.utils.contains('DISTRO_FEATURES', 'efi-secure-boot', 'wrlinux-image-minimal-initramfs-efi-secure-boot.inc', '', d)}
