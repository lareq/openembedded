LICENSE = "GPL"

DEPENDS = "klibc"
RDEPENDS_${PN} = "kexec-klibc-static"

inherit autotools

# You can create your own *-img.h by doing
# ./make-image-header.sh <file>.png HAND

SRC_URI += "file://logo-img.h \
	    file://logo.png \
	    "

export CC=${TARGET_PREFIX}klcc

# for output on serial console: --enable-debug
EXTRA_OECONF_akita = "--with-zaurus"
EXTRA_OECONF_c7x0 = "--with-zaurus"
EXTRA_OECONF_spitz = "--with-zaurus"
EXTRA_OECONF_poodle = "--with-zaurus"
EXTRA_OECONF_tosa = "--with-zaurus"

EXTRA_OECONF_omap3 = "--with-uimage"

do_configure_prepend () {
    install -m 0644 ${WORKDIR}/logo-img.h ${S}/res/
    install -m 0644 ${WORKDIR}/logo.png ${S}/res/
}

do_install () {
	install -d ${D}${bindir}
	install -m 0755 kexecboot ${D}${bindir}/

	install -d ${D}/proc
	install -d ${D}/mnt
}

FILES_${PN} += " ${bindir}/kexecboot /init /proc /mnt"

pkg_postinst_${PN} () {
	ln -sf ${bindir}/kexecboot $D/init
}
