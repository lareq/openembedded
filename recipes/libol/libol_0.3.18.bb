DESCRIPTION = "A tiny C support library"
SECTION = "libs"
LICENSE = "GPL"
PR = "r8"

SRC_URI = "http://www.balabit.com/downloads/files/libol/0.3/${P}.tar.gz"

inherit autotools binconfig

do_stage() {
	autotools_stage_all
}
