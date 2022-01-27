##Process this file with automake to create Makefile.in

bin_PROGRAMS = makerscanner
AUTOMAKE_OPTIONS = subdir-objects
makerscanner_SOURCES = src/ActiveStereoApp.cpp  src/CaptureThread.h  src/ScanStatus.h  src/ActiveStereoApp.h  src/DistanceToReferenceDialog.cpp  src/ScanThread.cpp  src/ActiveStereoMain.cpp  src/DistanceToReferenceDialog.h  src/ScanThread.h  src/ActiveStereoMain.h  src/IndividualPixels.h  src/Cameras.cpp  src/PointCloud.cpp  src/Cameras.h  src/PointCloud.h  src/camview.cpp  src/PointCloudPoint.cpp  src/camview.h  src/PointCloudPoint.h  src/SetHorz.h  src/CaptureThread.cpp  src/ScanStatus.cpp  src/

EXTRA_DIST = laserIcon.png
pixmapdir = $(datadir)/pixmaps
pixmap_DATA = laserIcon.png



##AM_CPPFLAGS = $(DEPS_CFLAGS) -DPIXMAPS_DIR=\""$(datadir)/pixmaps"\"

## Add the OpenCV flags that we got from PKG_CHECK_MODULES([OPENCV], [opencv >= 2.0]) in configure.ac
AM_CPPFLAGS = $(OPENCV_CFLAGS) $(DEPS_CFLAGS) -DPIXMAPS_DIR=\""$(datadir)/pixmaps"\"

## Add the OpenCV linking libraries that we got from PKG_CHECK_MODULES([OPENCV], [opencv >= 2.0]) in configure.ac
makerscanner_LDADD = $(OPENCV_LIBS)
##libfoo_la_LDFLAGS = -version-info @version_info@

