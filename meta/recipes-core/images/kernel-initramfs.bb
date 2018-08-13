SUMMARY = "Initramfs kernel boot"
DESCRIPTION = "This package includes the initramfs for the kernel boot. \
"
LICENSE = "MIT"

DEFAULT_PREFERENCE = "-1"

DEPENDS = "virtual/kernel"

PROVIDES = "virtual/kernel-initramfs"

ALLOW_EMPTY_${PN} = "1"

B = "${WORKDIR}/${BPN}-${PV}"

inherit linux-kernel-base kernel-arch

INITRAMFS_NAME = "${KERNEL_IMAGETYPE}-initramfs-${PV}-${PR}-${MACHINE}-${DATETIME}"
INITRAMFS_NAME[vardepsexclude] = "DATETIME"
INITRAMFS_EXT_NAME = "-${@oe.utils.read_file('${STAGING_KERNEL_BUILDDIR}/kernel-abiversion')}"

BUNDLE = "${@'1' if d.getVar('INITRAMFS_IMAGE', True) and \
                    d.getVar('INITRAMFS_IMAGE_BUNDLE', True) == '1' \
                 else '0'}"

python() {
    image = d.getVar('INITRAMFS_IMAGE', True)
    if image:
        d.appendVarFlag('do_install', 'depends', ' ${INITRAMFS_IMAGE}:do_rootfs')
}

do_unpack[depends] += "virtual/kernel:do_deploy"
do_populate_lic[depends] += "virtual/kernel:do_deploy"

do_install() {
    [ -z "${INITRAMFS_IMAGE}" ] && exit 0

    install -d "${D}/boot"
    if [ "${BUNDLE}" = "0" ]; then
        for suffix in ${INITRAMFS_FSTYPES}; do
            img="${DEPLOY_DIR_IMAGE}/${INITRAMFS_IMAGE}-${MACHINE}.$suffix"

            install -m 0644 "$img" \
                "${D}/boot/${INITRAMFS_IMAGE}${INITRAMFS_EXT_NAME}.$suffix"
            ln -sf  "${INITRAMFS_IMAGE}${INITRAMFS_EXT_NAME}.$suffix" "${D}/boot/initrd"
	done
    else
	if [ -e "${DEPLOY_DIR_IMAGE}/${KERNEL_IMAGETYPE}-initramfs-${MACHINE}.bin" ]; then
            install -m 0644 "${DEPLOY_DIR_IMAGE}/${KERNEL_IMAGETYPE}-initramfs-${MACHINE}.bin" \
                "${D}/boot/${KERNEL_IMAGETYPE}-initramfs${INITRAMFS_EXT_NAME}"
            ln -sf  "${KERNEL_IMAGETYPE}-initramfs${INITRAMFS_EXT_NAME}" "${D}/boot/initrd"
	fi
    fi
}

inherit update-alternatives

ALTERNATIVES_${PN} = ""

PACKAGE_ARCH = "${MACHINE_ARCH}"

FILES_${PN} = "/boot/*"
