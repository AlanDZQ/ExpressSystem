QT += quick \
 sql \
qml quick charts\
printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)

SOURCES += \
        main.cpp \
    dbconnection.cpp \
    dboperator.cpp \
    user.cpp \
    warehouse.cpp \
    supplier.cpp \
    import.cpp \
    good.cpp \
    importgood.cpp \
    export.cpp \
    exportgood.cpp \
    exportstatus.cpp \
    excelconnection.cpp\
        qrcode/bitstream.c \
        qrcode/mask.c \
        qrcode/mmask.c \
        qrcode/mqrspec.c \
        qrcode/qrencode.c \
        qrcode/qrspec.c \
        qrcode/rscode.c \
        qrcode/split.c \
        qrcode/qrinput.c \
    pdfgenerate.cpp \
    exportpricetime.cpp

RESOURCES += qml.qrc \
user.png \
logout.png \
plus.png \
reduce.png \
save.png \
redo.png \
undo.png \
view.png \
default.png \
in.png\
out.png\
chart.png\
list.png

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    dbconnection.h \
    dboperator.h \
    user.h \
    warehouse.h \
    supplier.h \
    import.h \
    good.h \
    importgood.h \
    export.h\
    exportgood.h \
    exportstatus.h \
    excelconnection.h\
        qrcode/bitstream.h \
        qrcode/mask.h \
        qrcode/mmask.h \
        qrcode/mqrspec.h \
        qrcode/qrencode.h \
        qrcode/qrencode_inner.h \
        qrcode/qrinput.h \
        qrcode/qrspec.h \
        qrcode/rscode.h \
        qrcode/split.h \
        qrcode/config.h \
    pdfgenerate.h \
    exportpricetime.h

OTHER_FILES += \
    qrcode/config.h.in
