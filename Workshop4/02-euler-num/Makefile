NDK=/opt/android-ndk-r20/ndk-build

SRC_PDIR=euler-num-parallel
SRC_SDIR=euler-num-serial
FILE_P=euler_num_parallel
FILE_S=euler_num_serial

BUILDP_PATH=$(SRC_PDIR)/libs/armeabi-v7a
BUILDS_PATH=$(SRC_SDIR)/libs/armeabi-v7a
CELLPHONE_PATH=/data/local/tmp


run-parallel:
		@export NDK_PROJECT_PATH="." && cd $(SRC_PDIR) && $(NDK)
		@adb push $(BUILDP_PATH)/$(FILE_P) $(CELLPHONE_PATH)
		@adb shell $(CELLPHONE_PATH)/$(FILE_P)


run-serial:
		@export NDK_PROJECT_PATH="." && cd $(SRC_SDIR) && $(NDK)
		@adb push $(BUILDS_PATH)/$(FILE_S) $(CELLPHONE_PATH)
		@adb shell $(CELLPHONE_PATH)/$(FILE_S)
