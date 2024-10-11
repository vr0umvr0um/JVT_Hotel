# JVT_HOTEL

## DESCRIPTION
JVT Hotel is an application that manages the interfaces between administrators, general employees, managers and customers.

Depending on the user type, we can view hotel statistics, employees, hotels and customers in the database.

Whatever the user type, we can make/modify/cancel a reservation.

We have access to our profile, which we can modify, and we have a summary of all reservations made, whether validated by the establishment or not.

This project was carried out by 3 people (including myself).

Beware, this project was coded on QTCREATOR6.7.

## MY PART
Here's a list of all the files I have coded :

- annuleresadialog.h
- annuleresadialog.cpp
- annuleresadialog.ui
- chambredao.h
- client.cpp
- client.h
- client.ui
- clientcomptedialog.cpp
- clientcomptedialog.h
- clientcomptedialog.ui
- clientdao.cpp
- clientdao.h
- clientinscriptiondialog.cpp
- clientinscriptiondialog.h
- clientinscriptiondialog.ui
- dao.cpp
- dao.h
- demandemodifresadialog.cpp
- demandemodifresadialog.h
- demandemodifresadialog.ui
- demanderesadialog.cpp
- demanderesadialog.h
- demanderesadialog.ui
- homepagedialog.h
- homepagedialog.cpp
- homepagedialog.ui
- mainwindow.cpp
- mainwindow.h
- modifresadialog.cpp
- modifresadialog.h
- modifresadialog.ui
- reservationdao.h
- singleconnection.h
- singleconnection.cpp
  
## SET-UP GUIDE
### For database files
1. Got to PHPMyAdmin and create a database called "reservationhotel".
2. First, import "CreationBase.sql" and then "DonnéesBase.sql" into your database.
### For QT&MYSQL Connector files
/!\ ALWAYS CHECK THAT THE FOLLOWING FILES ARE UP TO DATE WITH THE CURRENT VERSION OF QTCREATOR. It won't work otherwise. See [Credits](## CREDITS) for more informations /!\
1. Select "qsqlmysql.dll" and put it there "C:\\Qt\6.7.0\mingw_64\plugins\sqldrivers"
2. Select the 3 others dll files and put them there "C:\ReservationHotel\build\Desktop_Qt_6_7_0_MinGW_64_bit-Debug\debug"

And now the project is all set ! Don't forget to run your SQLserver.
## SCREENSHOTS
### SIGN IN
![image](https://github.com/user-attachments/assets/a08aa9da-d42c-4d6b-bb34-b7813f3a1dec)
### SIGN UP
![image](https://github.com/user-attachments/assets/d63db084-a4d7-466c-b169-be622f90ca13)
### HOMEPAGE
![image](https://github.com/user-attachments/assets/f9a9baac-468c-4397-a5bc-04d66946557a)
### BOOK A RESERVATION
![image](https://github.com/user-attachments/assets/bd6442d8-205e-4bc0-a6fd-e0cdce2ad906)
### MODIFY A RESERVATION
![image](https://github.com/user-attachments/assets/fe099361-223c-44bf-bb52-1237c6ee62d7)
![image](https://github.com/user-attachments/assets/8efba158-61fa-49b8-9255-7a67002b0771)
### CANCEL A RESERVATION
![image](https://github.com/user-attachments/assets/466f464f-efc4-4ffc-8bb8-6da044b3e148)
### CLIENT ACCOUNT
![image](https://github.com/user-attachments/assets/041b3eef-f44e-4b83-9037-a506456dff02)
### EMPLOYEE
#### ACCOUNT
![image](https://github.com/user-attachments/assets/c4e3f3a7-e8d6-4336-8d15-8cccc80702aa)
#### VALIDATE RESERVATION
![image](https://github.com/user-attachments/assets/9e9efffd-a7ea-40a8-a876-bef6c5dabbac)
#### HOTEL ROOM LIST
![image](https://github.com/user-attachments/assets/065310ec-c06d-423e-974e-8cdcf54b0e63)
### MANAGERS
#### ACCOUNT
![image](https://github.com/user-attachments/assets/767ab4f5-46b7-4135-a409-97bc0c84fa59)
#### HOTEL EMPLOYEE LIST
![image](https://github.com/user-attachments/assets/207f540f-a2e1-4935-b901-2c2ca4f00f22)
#### HOTEL CLIENT LIST
![image](https://github.com/user-attachments/assets/2cdc865f-d6d7-417d-8775-99215061556e)
#### HOTEL ROOM LIST
![image](https://github.com/user-attachments/assets/63b623d4-80d2-43ec-836f-bfae6c41fa9d)
#### HOTEL STATISTICS
![image](https://github.com/user-attachments/assets/7d5b39a2-cbb3-4e0e-8893-e1a954a62e8a)
### ADMIN
#### HOTEL STATISTICS
![image](https://github.com/user-attachments/assets/bc3cb7da-761f-465e-8c38-dd53a0d3bf2a)
#### MODIFY PROFILE
![image](https://github.com/user-attachments/assets/9058ac10-4c34-4b0e-9b33-b3605615bc35)
#### ADMIN LIST
![image](https://github.com/user-attachments/assets/d680ed81-24ac-44d1-a931-43406b2fbe75)
#### HOTEL LIST
![image](https://github.com/user-attachments/assets/b259699d-6cc4-4d95-86f0-b1aa98ad3e64)
#### EMPLOYEE FROM A SPECIFIC HOTEL LIST
![image](https://github.com/user-attachments/assets/fa84361a-bbba-4988-a44b-b5da1d33ace5)
#### CLIENT LIST
![image](https://github.com/user-attachments/assets/dc38f2e7-6e86-4af1-ac9f-1becde9546f0)
## CREDITS
[The Code Monkey on Github](https://github.com/thecodemonkey86/qt_mysql_driver) for sql drivers and all the explanation on its setup.
[QTCreator](https://www.qt.io/) for IDE.
And my group project mates.
