INCLUDEPATH += $$ROOT_PATH/include

BUILD_PATH = $$ROOT_PATH/out

CONFIG(debug,debug|release){
BUILD_PATH = $$BUILD_PATH/debug
}
CONFIG(release,debug|release){
BUILD_PATH = $$BUILD_PATH/release
}

BIN_PATH = $$BUILD_PATH/bin
LIB_PATH = $$BUILD_PATH/lib

contains(TEMPLATE, app) {
DESTDIR = $$BIN_PATH
} else {
DLLDESTDIR = $$BIN_PATH
DESTDIR = $$LIB_PATH
}
