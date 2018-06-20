QT += core
QT -= gui

TARGET = hsv-segmenttation
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

CONFIG+=c++11
QMAKE_CFLAGS += -std=c++11
QMAKE_CXXFLAGS = $$QMAKE_CFLAGS



INCLUDEPATH +=  /usr/local/include\
                /usr/local/include/opencv\
                /usr/local/include/opencv2\
                /usr/local/include/ARToolKitPlus\


LIBS += /usr/local/lib/libopencv_highgui.so\
        /usr/local/lib/libopencv_core.so\
        /usr/local/lib/libopencv_imgproc.so\
        /usr/local/lib/libopencv_calib3d.so\
        /usr/local/lib/libopencv_features2d.so\
        /usr/local/lib/libopencv_flann.so\
        /usr/local/lib/libopencv_imgcodecs.so\
        /usr/local/lib/libopencv_ml.so\
        /usr/local/lib/libopencv_objdetect.so\
        /usr/local/lib/libopencv_photo.so\
        /usr/local/lib/libopencv_shape.so\
        /usr/local/lib/libopencv_stitching.so\
        /usr/local/lib/libopencv_superres.so\
        /usr/local/lib/libopencv_video.so\
        /usr/local/lib/libopencv_videoio.so\
        /usr/local/lib/libopencv_videostab.so\
        /usr/local/lib/libARToolKitPlus.so\
        /usr/lib/aarch64-linux-gnu/libglfw.so\
