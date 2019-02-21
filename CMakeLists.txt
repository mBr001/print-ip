cmake_minimum_required(VERSION 3.8.2)

project(print_ip VERSION 1.0.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(print_ip print_ip.cpp)

set_target_properties(print_ip PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

################################################################################

install(TARGETS print_ip RUNTIME DESTINATION bin)

################################################################################

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_NAME print_ip)
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE amd64)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Anton Sochnev <an.sochnev@yandex.ru>")
set(CPACK_DEBIAN_PACKAGE_SECTION "homework")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION 
"some description should be here
 And here."
)
set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION})

include(CPack)

