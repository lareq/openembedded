DEFAULT_PREFERENCE = "-1"
SECTION = "base"
PR = "r1"
HOMEPAGE = "http://www.freedesktop.org/Software/dbus"
DESCRIPTION = "message bus system for applications to talk to one another"
LICENSE = "GPL"
DEPENDS = "expat glib-2.0 virtual/libintl"
PROVIDES = "dbus-glib"

SRC_URI = "http://repository.maemo.org/pool/maemo/ossw/source/d/${PN}/${PN}_${PV}.tar.gz \
	   file://cross.patch;patch=1 \
	   file://tmpdir.patch;patch=1 \
	   file://gettext.patch;patch=1 \
           file://0.23.1.diff;patch=1 \
           file://dbus-monitor.patch;patch=1 \
           file://dbussend.patch;patch=1;pnum=0 \
           file://spawn-priority.diff;patch=1 \
           file://config.diff;patch=1;pnum=0 \
           file://dbus-quiesce-startup-errors.patch;patch=1 \
           file://tools.diff;patch=1;pnum=0 \
	   file://dbus-1.init"

inherit autotools pkgconfig update-rc.d gettext

S = "${WORKDIR}/dbus-0.23.1"

INITSCRIPT_NAME = "dbus-1"
INITSCRIPT_PARAMS = "defaults"

CONFFILES_${PN} = "${sysconfdir}/dbus-1/system.conf ${sysconfdir}/dbus-1/session.conf"

FILES_${PN} = "${bindir}/dbus-daemon-1 ${bindir}/dbus-launch ${bindir}/dbus-cleanup-sockets ${bindir}/dbus-send ${bindir}/dbus-monitor ${sysconfdir} ${datadir}/dbus-1/services ${libdir}/lib*.so.*"
FILES_${PN}-dev += "${libdir}/dbus-1.0/include ${bindir}/dbus-glib-tool"

pkg_postinst_dbus() {
#!/bin/sh

# can't do adduser stuff offline
if [ "x$D" != "x" ]; then
  exit 1
fi

MESSAGEUSER=messagebus
MESSAGEHOME=/var/run/dbus

mkdir -p $MESSAGEHOME || true
chgrp "$MESSAGEUSER" "$MESSAGEHOME" 2>/dev/null || addgroup "$MESSAGEUSER"
chown "$MESSAGEUSER"."$MESSAGEUSER" "$MESSAGEHOME" 2>/dev/null || adduser --system --home "$MESSAGEHOME" --no-create-home --disabled-password --ingroup "$MESSAGEUSER" "$MESSAGEUSER"
}

EXTRA_OECONF = "--disable-qt --disable-gtk --disable-tests \
		--disable-checks --disable-xml-docs --disable-doxygen-docs \
		--with-xml=expat --without-x"

do_stage () {
	oe_libinstall -so -C dbus libdbus-1 ${STAGING_LIBDIR}
	oe_libinstall -so -C glib libdbus-glib-1 ${STAGING_LIBDIR}

	autotools_stage_includes

	mkdir -p ${STAGING_LIBDIR}/dbus-1.0/include/dbus/
	install -m 0644 dbus/dbus-arch-deps.h ${STAGING_LIBDIR}/dbus-1.0/include/dbus/
}

do_install_append () {
	install -d ${D}${sysconfdir}/init.d
	install -m 0755 ${WORKDIR}/dbus-1.init ${D}${sysconfdir}/init.d/dbus-1
}

python populate_packages_prepend () {
	if (bb.data.getVar('DEBIAN_NAMES', d, 1)):
		bb.data.setVar('PKG_dbus', 'dbus-1', d)
}
