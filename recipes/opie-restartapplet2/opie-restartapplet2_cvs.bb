require ${PN}.inc

PV = "${OPIE_CVS_PV}"

SRC_URI = "${HANDHELDS_CVS};module=opie/core/applets/restartapplet2 \
           ${HANDHELDS_CVS};module=opie/apps"
