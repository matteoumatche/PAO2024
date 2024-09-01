QT       += core gui charts
QT += charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Model/fotocellula.cpp \
    src/View/editsensordialog.cpp \
    src/View/optionsWidget.cpp \
    src/View/sensorinfowidget.cpp \
    src/View/sensorlistwidget.cpp \
    src/View/widgetfotocellula.cpp \
    src/View/widgettemperatura.cpp \
    src/View/widgettempercepita.cpp \
    src/View/widgetumidita.cpp \
    src/View/widgetvento.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/Model/sensore.cpp \
    src/Model/temperatura.cpp \
    src/Model/tempercepita.cpp \
    src/Model/umidita.cpp \
    src/Model/vento.cpp \
    src/View/toolBar.cpp \
    src/View/widgetgrafico.cpp

HEADERS += \
    src/Model/fotocellula.h \
    src/View/editsensordialog.h \
    src/View/optionsWidget.h \
    src/View/sensorinfowidget.h \
    src/View/sensorlistwidget.h \
    src/View/widgetfotocellula.h \
    src/View/widgettemperatura.h \
    src/View/widgettempercepita.h \
    src/View/widgetumidita.h \
    src/View/widgetvento.h \
    src/mainwindow.h \
    src/Model/sensore.h \
    src/Model/temperatura.h \
    src/Model/tempercepita.h \
    src/Model/umidita.h \
    src/Model/vento.h \
    src/View/toolBar.h \
    src/View/widgetgrafico.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
