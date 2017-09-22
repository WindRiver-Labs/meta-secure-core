#
# Copyright (C) 2017 Wind River Systems, Inc.
#

require ${@bb.utils.contains('DISTRO_FEATURES', 'luks', 'wrlinux-image-initramfs-encrypted-storage.inc', '', d)}
