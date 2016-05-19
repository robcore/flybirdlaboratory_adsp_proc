adb root
adb wait-for-device
adb shell cd data; chmod 777 amdb_mgr; ./amdb_mgr print_all_capi
