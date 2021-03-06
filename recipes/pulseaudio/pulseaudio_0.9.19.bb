require pulseaudio.inc

DEPENDS += "gdbm speex"

PR = "${INC_PR}.0"

inherit gettext

SRC_URI += "\
  file://buildfix.patch;patch=1 \
  file://autoconf_version.patch;patch=1 \
  file://tls_m4.patch;patch=1 \
  file://configure_silent_rules.patch;patch=1 \
  file://gettext.patch;patch=1 \
  file://fixbluezbuild.patch;patch=1 \
"

do_compile_prepend() {
    cd ${S}
    mkdir -p ${S}/libltdl
    cp ${STAGING_LIBDIR}/libltdl* ${S}/libltdl
}
