DESCRIPTION = "NetworkManager"
SECTION = "net/misc"
LICENSE = "GPL"
PRIORITY = "optional"
DEPENDS = "libnl dbus dbus-glib hal wireless-tools ppp policykit gnutls"
RDEPENDS = "hal wpa-supplicant iproute2 dhcp-client dhcdbd"

# Providers that require this file MUST append the source to SRC_URI
# These are just the common patches
SRC_URI = " \
	  file://25NetworkManager \
	  file://99_networkmanager"

S = "${WORKDIR}/git"


EXTRA_OECONF = " \
		--with-distro=debian \
		--with-wpa_supplicant=/usr/sbin/wpa_supplicant \
		--with-dhcdbd=/sbin/dhcdbd \
		--with-ip=/sbin/ip.iproute2 \
		--with-crypto=gnutls \
		--disable-more-warnings"

inherit autotools pkgconfig

do_stage () {
	autotools_stage_all
}

do_install_append () {
        install -d ${D}/etc/default/volatiles
        install -m 0644 ${WORKDIR}/99_networkmanager ${D}/etc/default/volatiles
        install -d ${D}/etc/dbus-1/event.d
        install -m 0755 ${WORKDIR}/25NetworkManager ${D}/etc/dbus-1/event.d
        sed -i s,/sbin/ip,/sbin/ip.iproute2, ${D}/etc/init.d/NetworkManager
        # Test binaries
        install -d ${D}/usr/bin
        install -m 0755 ${S}/test/.libs/nm-tool ${D}/usr/bin
        install -m 0755 ${S}/test/.libs/libnm_glib_test ${D}/usr/bin
        install -m 0755 ${S}/test/.libs/nm-online ${D}/usr/bin
        install -m 0755 ${S}/test/.libs/nmtestdevices ${D}/usr/bin
}

pkg_postinst_${PN} () {
	if [ "x$D" != "x" ]; then
		exit 1
	fi
	/etc/init.d/populate-volatile.sh update
}

PACKAGES =+ "libnmutil libnmglib libnmglib-vpn ${PN}-tests" 

FILES_libnmutil += "${libdir}/libnm-util.so.*"
FILES_libnmglib += "${libdir}/libnm_glib.so.*"
FILES_libnmglib-vpn += "${libdir}/libnm_glib_vpn.so.*"

FILES_${PN} += " \
		${libexecdir} \
		${libdir}/pppd/*/nm-pppd-plugin.so \
		${libdir}/NetworkManager/*.so \
		${datadir}/PolicyKit \
		${datadir}/dbus-1"

FILES_${PN}-dbg += "${libdir}/NetworkManager/.debug/ \
		    ${libdir}/pppd/*/.debug/ "

FILES_${PN}-dev += "${datadir}/NetworkManager/gdb-cmd \
                    ${libdir}/pppd/*/*.a \
                    ${libdir}/pppd/*/*.la \
                    ${libdir}/NetworkManager/*.a \
                    ${libdir}/NetworkManager/*.la"

FILES_${PN}-tests = "${bindir}/nm-tool \
                     ${bindir}/libnm_glib_test \
                     ${bindir}/nminfotest \
                     ${bindir}/nm-online \
                     ${bindir}/nm-supplicant \
                     ${bindir}/nm-testdevices"
