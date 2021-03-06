LICENSE     = "LiPS"
DESCRIPTION = "LiPS voice call library."
SECTION = "gpe/libs"
PRIORITY    = "optional"
DEPENDS     = "gtk+ libglade libgsmd"
PV = "0.0+svnr-${SRCREV}"
PR          = "r0"

inherit gpephone pkgconfig autotools

SRC_URI = "${GPEPHONE_SVN}"

S = "${WORKDIR}/${PN}"

do_stage () {
	autotools_stage_all
}
