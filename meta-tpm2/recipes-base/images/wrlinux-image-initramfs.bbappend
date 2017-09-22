#
# Copyright (C) 2017 Wind River Systems, Inc.
#

require ${@bb.utils.contains('DISTRO_FEATURES', 'tpm2', 'wrlinux-image-initramfs-tpm2.inc', '', d)}
