#!/bin/sh

set -eu

cd "$(dirname "$0")"

JOBS=${JOBS:-$(nproc)}

release=$(sed -n 's/^VERSION_NUMBER:=.*,\([^,)]*\))$/\1/p' include/version.mk)
kmods=https://downloads.openwrt.org/releases/$release/targets/kirkwood/generic/kmods/
if [ -z "${VERMAGIC:-}" ]; then
	VERMAGIC=$( (curl -fsSL "$kmods" || wget -qO- "$kmods") 2>/dev/null |
		grep -o '[0-9.]*-[0-9]*-[0-9a-f]\{32\}' | head -n1 | sed 's/.*-//')
fi
[ -n "$VERMAGIC" ] || {
	echo "no vermagic for $release at $kmods" >&2
	exit 1
}

./scripts/feeds update -a
./scripts/feeds install -a

[ -f .config ] && cp .config .config.prev
cp wtplug-tc.diffconfig .config
make defconfig

for sym in TARGET_kirkwood_generic_DEVICE_promwad_wtplug-tc ALL_KMODS \
	PACKAGE_u-boot-wtplug_tc PACKAGE_kmod-xgi-fb PACKAGE_kmscon \
	PACKAGE_kmod-sound-soc-wtplug-tc PACKAGE_wtplug-tc-sound \
	PACKAGE_kmod-usb251xb PACKAGE_kmod-usb-hid PACKAGE_alsa-utils; do
	grep -qx "CONFIG_$sym=y" .config || {
		echo "CONFIG_$sym is not set after defconfig" >&2
		exit 1
	}
done

make download -j"$JOBS"
make -j"$JOBS" || make -j1 V=s

vermagic=$(sed 's/.*~\(.*\)-r.*/\1/' staging_dir/target-*/kernel.version)
[ "$vermagic" = "$VERMAGIC" ] || {
	echo "kernel vermagic is $vermagic, the $release repository has $VERMAGIC" >&2
	exit 1
}

ls -l bin/targets/kirkwood/generic/*promwad_wtplug-tc* \
	bin/targets/kirkwood/generic/u-boot-wtplug_tc/u-boot.kwb
