cmake_minimum_required(VERSION 3.16)

project(School_Management_System_Completed LANGUAGES C)

add_executable(School_Management_System_Completed main.c
    admin.h
    student.h
    faculty.h
    fees.h
    section.h
    fileoperation.h
    main1.h
    admin.c
    faculty.c
    fees.c
    fileoperation.c
    main1.c
    section.c
    student.c
    README.md)

include(GNUInstallDirs)
install(TARGETS School_Management_System_Completed
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
