inherit user-key-store deploy

# Always fetch the latest initramfs image
do_install[nostamp] = "1"

fakeroot python do_sign() {
    if d.getVar('BUNDLE', True) == '0':
        for compr in d.getVar('INITRAMFS_FSTYPES').split():
            uks_sel_sign(d.expand('${D}/boot/${INITRAMFS_IMAGE}${INITRAMFS_EXT_NAME}.') + compr, d)
    else:
        uks_sel_sign(d.expand('${D}/boot/${KERNEL_IMAGETYPE}-initramfs${INITRAMFS_EXT_NAME}'), d)
}
addtask sign after do_install before do_deploy do_package
do_sign[prefuncs] += "check_deploy_keys"

do_deploy() {
    install -d "${DEPLOYDIR}"
    for SIG in ${D}/boot/*.p7b; do
        install -m 0644 ${SIG} ${DEPLOYDIR}

    done

    for compr in ${INITRAMFS_FSTYPES}; do
        if [ -e "${D}/boot/${INITRAMFS_IMAGE}${INITRAMFS_EXT_NAME}.${compr}.p7b" -a "${BUNDLE}" = "0" ]; then
            ln -sf "${INITRAMFS_IMAGE}${INITRAMFS_EXT_NAME}.${INITRAMFS_FSTYPES}.p7b" "${D}/boot/initrd.p7b"
        fi

        if [ -e "${KERNEL_IMAGETYPE}-initramfs${INITRAMFS_EXT_NAME}.p7b" -a "${BUNDLE}" = "1"]; then
            ln -sf "${KERNEL_IMAGETYPE}-initramfs${INITRAMFS_EXT_NAME}.p7b" "${D}/boot/initrd.p7b"
        fi

    done
}
addtask deploy after do_install before do_build

