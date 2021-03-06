require xorg-proto-common.inc

DESCRIPTION = "Touchscreen calibration protocol"

PR = "r0"
PV = "0.0+${PR}+gitr${SRCREV}"
PE = "2"

SRC_URI = "git://anongit.freedesktop.org/git/xorg/proto/calibrateproto;protocol=git"
S = "${WORKDIR}/git"

do_stage() {
	autotools_stage_all
	#make it compatible with the old package from cvs
	ln -sf ${PKG_CONFIG_DIR}/xcalibrateproto.pc ${PKG_CONFIG_DIR}/xcalibrateext.pc
}
