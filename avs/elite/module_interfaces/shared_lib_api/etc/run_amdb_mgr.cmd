adb root
adb wait-for-device
adb shell cd data; chmod 777 amdb_mgr; ./amdb_mgr add_capi_v2 1 0x10BE9 0 1 HpMp3DecoderModule.so.2.9 hp_mp3_capi_v2_get_static_properties hp_mp3_capi_v2_init
