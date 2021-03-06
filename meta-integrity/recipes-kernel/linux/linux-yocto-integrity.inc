FILESEXTRAPATHS_prepend := "${THISDIR}/linux-yocto:"

IMA_ENABLED = "${@bb.utils.contains('DISTRO_FEATURES', 'ima', '1', '0', d)}"

DEPENDS += "${@'key-store openssl-native' if d.getVar('IMA_ENABLED', True) == '1' else ''}"

SRC_URI += "\
    ${@'file://ima.scc file://ima.cfg file://integrity.scc file://integrity.cfg' \
       if d.getVar('IMA_ENABLED', True) == '1' else ''} \
"

do_configure_prepend() {
    cert="${STAGING_DIR_TARGET}${sysconfdir}/keys/system_trusted_key.crt"

    if [ -f "$cert" ]; then
        install -m 0644 "$cert" "${B}"
    else
        true
    fi
}
