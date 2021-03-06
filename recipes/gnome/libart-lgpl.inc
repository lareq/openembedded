DESCRIPTION = "Library of functions for 2D graphics"
SECTION = "x11/gnome"
LICENSE = "LGPL"

ART_CONFIG = "${HOST_ARCH}/art_config.h"

INC_PR = "r4"

# can't use gnome.oeclass due to _ in filename
SRC_URI = "http://ftp.gnome.org/pub/GNOME/sources/libart_lgpl/2.3/libart_lgpl-${PV}.tar.bz2 \
       file://${ART_CONFIG} \
       file://Makefile.am.patch;patch=1"

inherit autotools pkgconfig

FILES_${PN} = "${libdir}/*.so.*"
FILES_${PN}-dev += "${bindir}/libart2-config"

S = "${WORKDIR}/libart_lgpl-${PV}"

do_configure_prepend() {
	cp ${WORKDIR}/${ART_CONFIG} ${S}/art_config.h
}

EXTRA_OECONF = "--disable-gtk-doc"

# With automake-native 1.10.2 the configure and m4 scripts are confused
# and detect the following stuff wrong. Correct programs are hereby
# enforced.
export MKDIR_P = "mkdir -p"
export mkdir_p = "mkdir -p"

do_stage() {
	autotools_stage_includes
	oe_libinstall -a -so libart_lgpl_2 ${STAGING_LIBDIR}
}
