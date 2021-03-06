DESCRIPTION = "Portable ftp daemon"
HOMEPAGE = "http://bftpd.sourceforge.net/"
SECTION = "console/network"
PR = "r2"
LICENSE = "GPL"

SRC_URI = "${SOURCEFORGE_MIRROR}/${PN}/${PN}-${PV}.tar.gz \
	   file://bftpd.conf \
		"

S = "${WORKDIR}/${PN}"

inherit autotools

do_install() {
	install -d ${D}${sbindir}
	install -d ${D}${mandir}/man8
	install -d ${D}${sysconfdir}

	install -m 0755 ${S}/bftpd      ${D}${sbindir}/bftpd
	install -m 0755 ${S}/bftpd.8    ${D}${mandir}/man8/bftpd.8
	install -m 0644 ${WORKDIR}/bftpd.conf ${D}${sysconfdir}/bftpd.conf
}
