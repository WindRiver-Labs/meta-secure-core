#
# Copyright (C) 2017 Wind River Systems, Inc.
#

require ${@bb.utils.contains('DISTRO_FEATURES', 'ima', 'wrlinux-image-initramfs-integrity.inc', '', d)}
