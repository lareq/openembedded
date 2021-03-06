DESCRIPTION = "The Ace of Penguins is a set of Unix/X solitaire games based on the ones available for Windows(tm) but with a number of enhancements that my wife says make my versions better :-) \
The latest version includes clones of freecell, golf, mastermind, merlin, minesweeper, pegged, solitaire, taipei (with editor!), and thornq (by Martin Thornquist)."
AUTHOR = "dj@delorie.com"
HOMEPAGE = "http://www.delorie.com/store/ace/"
SECTION = "games"
DEPENDS = "libpng zlib libxpm"
PR = "r1"

SRC_URI = "\
  http://www.delorie.com/store/ace/ace-${PV}.tar.gz\
  file://gcc4.patch;patch=1\
"
S = "${WORKDIR}/ace-${PV}"

inherit autotools

# Workaround QA issue
TARGET_CC_ARCH += "${LDFLAGS}"