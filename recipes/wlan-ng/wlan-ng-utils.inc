# FIXME, consider using kernel staging directory instead of KERNEL_SOURCE which is
# located in the work directory. see module.bbclass

DESCRIPTION = "linux-wlan-ng userland utilities"
HOMEPAGE = "http://www.linux-wlan.org"
SECTION = "kernel/userland"
LICENSE = "GPL"
DEPENDS = "virtual/kernel"

SRC_URI = "file://only-the-utils.patch;patch=1 \
	file://wlan-ng.modutils \
	file://wlan.agent \
	file://resume \
	file://pre-up \
	file://post-down \
	file://config.in"
SRC_URI_append_arm = " file://usbctl"

# yeah, it's kind of backwards, but otherwise the config step will fail
inherit module

do_configure() {
	install -m 0655 ${WORKDIR}/config.in ${S}/config.in
	oe_runmake LINUX_SRC=${KERNEL_SOURCE} auto_config

        if grep CONFIG_PCMCIA=[ym] ${STAGING_KERNEL_DIR}/kernel-config; then
                echo "PRISM2_PCMCIA=y"          >> config.mk
                echo "WLAN_KERN_PCMCIA=y"       >> config.mk
        fi
        echo "TARGET_ROOT_ON_HOST=${D}/"		>> config.mk
	echo "FIRMWARE_DIR=/etc/wlan"		>> config.mk
        echo "TARGET_MODDIR=${D}/lib/modules/${KERNEL_VERSION}/wlan-ng" >> config.mk
	echo "TARGET_INST_EXEDIR=${D}/sbin"			>> config.mk
        echo "RC_DIR=${sysconfdir}/"             >> config.mk
	echo "CC=${CC}"			>> config.mk
	echo "LD=${LD}"			>> config.mk

	# Shut up, you broken buildsystem
	install -m 0655 config.mk src/prism2/config.mk
	install -d src/prism2/driver/include
	ln -sf ${S}/src/include/wlan 		src/prism2/driver/include/wlan
	ln -sf ${S}/src/prism2/include/prism2	src/prism2/driver/include/prism2
}

do_compile() {
	oe_runmake all
}

do_install() {
	oe_runmake install
	mkdir -p ${D}${sysconfdir}/modutils/
	mkdir -p ${D}${sysconfdir}/hotplug/
	mkdir -p ${D}${base_sbindir}/
	install -m 0644 ${WORKDIR}/wlan-ng.modutils ${D}${sysconfdir}/modutils/wlan-ng.conf
	install -m 0755 ${WORKDIR}/wlan.agent ${D}${sysconfdir}/hotplug/wlan.agent
	install -d ${D}${sysconfdir}/network/if-pre-up.d
	install -m 0755 ${WORKDIR}/pre-up ${D}${sysconfdir}/network/if-pre-up.d/wlan-ng
	install -d ${D}${sysconfdir}/network/if-post-down.d
	install -m 0755 ${WORKDIR}/post-down ${D}${sysconfdir}/network/if-post-down.d/wlan-ng
	install -d ${D}${sysconfdir}/apm/resume.d
	install -m 0755 ${WORKDIR}/resume ${D}${sysconfdir}/apm/resume.d/wlan-ng
	install -d ${D}${mandir}/man1
	install -m 0644 ${S}/man/*.1 ${D}${mandir}/man1/
	rm -rf ${D}/usr/local/man
}

do_install_append_arm() {
	install -m 0755 ${WORKDIR}/usbctl ${D}${base_sbindir}/usbctl
}

FILES_${PN}-dbg += "/sbin/.debug"
FILES_${PN} = "/etc /sbin"
