adb root
adb wait-for-device
adb remount
adb shell mount -o remount,rw /system
adb shell mkdir -p /system/lib/rfsa/adsp/
adb push libadsp_amdb_skel.so /system/lib/rfsa/adsp/
adb push ../../../../install_dir/avs_shared_libs/qdsp6/AAAAAAAA /system/lib/rfsa/adsp/
adb push amdb_mgr /data
