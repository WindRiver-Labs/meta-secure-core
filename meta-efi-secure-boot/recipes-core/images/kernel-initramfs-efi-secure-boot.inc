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

    if [ "${BUNDLE}" = "0" ]; then
        for compr in ${INITRAMFS_FSTYPES}; do
            if [ -e "${D}/boot/${INITRAMFS_IMAGE}${INITRAMFS_EXT_NAME}.${compr}.p7b" ]; then
                ln -sf "${INITRAMFS_IMAGE}${INITRAMFS_EXT_NAME}.${compr}.p7b" "${D}/boot/initrd.p7b"
                install -m 0644 "${D}/boot/${INITRAMFS_IMAGE}${INITRAMFS_EXT_NAME}.${compr}.p7b" \
                                               "${DEPLOYDIR}/${INITRAMFS_IMAGE}-${MACHINE}.${compr}.p7b"
            fi
        done
    else
        if [ -e "${KERNEL_IMAGETYPE}-initramfs${INITRAMFS_EXT_NAME}.p7b" ]; then
            ln -sf "${KERNEL_IMAGETYPE}-initramfs${INITRAMFS_EXT_NAME}.p7b" "${D}/boot/initrd.p7b"
            install -m 0644 "${D}/boot/${KERNEL_IMAGETYPE}-initramfs${INITRAMFS_EXT_NAME}.p7b" \
                                               "${DEPLOYDIR}/${INITRAMFS_IMAGE}-${MACHINE}.${INITRAMFS_FSTYPES}.p7b"
        fi
    fi
}
addtask deploy after do_install before do_build

