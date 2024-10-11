QT       += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admincomptedialog.cpp \
    administrateur.cpp \
    administrateurdao.cpp \
    adresse.cpp \
    adressedao.cpp \
    annuleresadialog.cpp \
    chambre.cpp \
    chambredao.cpp \
    client.cpp \
    clientcomptedialog.cpp \
    clientdao.cpp \
    clientinscriptiondialog.cpp \
    dao.cpp \
    demandemodifresadialog.cpp \
    demanderesadialog.cpp \
    empcomptedialog.cpp \
    employe.cpp \
    employedao.cpp \
    emprespcomptedialog.cpp \
    emprespstatsdialog.cpp \
    homepagedialog.cpp \
    hotel.cpp \
    hoteldao.cpp \
    listechambresdialog.cpp \
    listechambresrespdialog.cpp \
    listeclientsdialog.cpp \
    listeemployesdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    modifresadialog.cpp \
    reservation.cpp \
    reservationavaliderdialog.cpp \
    reservationdao.cpp \
    singleconnection.cpp


HEADERS += \
    admincomptedialog.h \
    administrateur.h \
    administrateurdao.h \
    adresse.h \
    adressedao.h \
    annuleresadialog.h \
    chambre.h \
    chambredao.h \
    client.h \
    clientcomptedialog.h \
    clientdao.h \
    clientinscriptiondialog.h \
    dao.h \
    demandemodifresadialog.h \
    demanderesadialog.h \
    empcomptedialog.h \
    employe.h \
    employedao.h \
    emprespcomptedialog.h \
    emprespstatsdialog.h \
    homepagedialog.h \
    hotel.h \
    hoteldao.h \
    listechambresdialog.h \
    listechambresrespdialog.h \
    listeclientsdialog.h \
    listeemployesdialog.h \
    mainwindow.h \
    modifresadialog.h \
    reservation.h \
    reservationavaliderdialog.h \
    reservationdao.h \
    singleconnection.h


FORMS += \
    admincomptedialog.ui \
    annuleresadialog.ui \
    clientcomptedialog.ui \
    clientinscriptiondialog.ui \
    demandemodifresadialog.ui \
    demanderesadialog.ui \
    empcomptedialog.ui \
    emprespcomptedialog.ui \
    emprespstatsdialog.ui \
    homepagedialog.ui \
    listechambresdialog.ui \
    listechambresrespdialog.ui \
    listeclientsdialog.ui \
    listeemployesdialog.ui \
    mainwindow.ui \
    modifresadialog.ui \
    reservationavaliderdialog.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    RessourcesHotel.qrc \

DISTFILES += \
    FeuilleDeStyle.css \
    README.md \
    ReservationHotel.pro.user \
    logoProjet_petit.png \
    logoProjet_petit_petit.png \


