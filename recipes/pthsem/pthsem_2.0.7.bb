DESCRIPTION = "GNU Portable Threads replacement with semaphore support"
SECTION = "libs"
PRIORITY = "optional"
LICENSE = "GPL LGPL FDL"
PR = "r0"

SRC_URI = "https://www.auto.tuwien.ac.at/~mkoegler/pth/pthsem-${PV}.tar.gz \
           file://ldflags.patch;patch=1 \
          "

inherit autotools binconfig

do_configure() {
        gnu-configize
        oe_runconf
}
do_install_prepend() {
        cp ${S}/pth-config ${S}/pthsem-config
}
do_stage() {
        oe_libinstall -so libpthsem ${STAGING_LIBDIR}
        install -d ${STAGING_INCDIR}/
        install -m 0644 ${S}/pth.h ${STAGING_INCDIR}/pthsem.h
        install -d ${STAGING_BINDIR}/
        install -d ${STAGING_DATADIR}/aclocal
        install pth.m4 ${STAGING_DATADIR}/aclocal/pthsem.m4
}

BINCONFIG_GLOB = "pthsem-config"

PARALLEL_MAKE = ""
