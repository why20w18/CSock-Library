CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(CSOCK)

#CXX STANDARTLARI VE COMPILE MODLARINI YAPILANDIRMA
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wextra -Wall -g")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wextra -Wall -O3")


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()


#DIZINLERIN YAPILANDIRILMASI
SET(DIZIN_SRC ${CMAKE_SOURCE_DIR}/src)
SET(DIZIN_INCLUDE ${CMAKE_SOURCE_DIR}/include)

SET(PROGRAM_SRC
    ${DIZIN_SRC}/server.cpp
    #${DIZIN_SRC}/client.cpp
    ${DIZIN_SRC}/csock.cpp
    ${DIZIN_SRC}/csockManuel.cpp
    
)

SET(PROGRAM_INCLUDE
    ${DIZIN_INCLUDE}/csockDefines.hpp
    ${DIZIN_INCLUDE}/csockPlatform.hpp
    ${DIZIN_INCLUDE}/csock.hpp
    ${DIZIN_INCLUDE}/csockManuel.hpp
)



#COMPILE ADIMININ YAPILANDIRILMASI
if(WIN32)
    add_executable(
        ${PROJECT_NAME} 
        ${PROGRAM_SRC}
        )

    target_link_libraries(
        ${PROJECT_NAME}
        ws2_32
    )

elseif(UNIX)
    include_directories(
        ${PROGRAM_INCLUDE}
    )

    add_executable(
            ${PROJECT_NAME} 
            ${PROGRAM_SRC}
)
endif()