# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


SET(CPACK_BINARY_7Z "")
SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_IFW "")
SET(CPACK_BINARY_NSIS "")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_RPM "")
SET(CPACK_BINARY_STGZ "")
SET(CPACK_BINARY_TBZ2 "")
SET(CPACK_BINARY_TGZ "")
SET(CPACK_BINARY_TXZ "")
SET(CPACK_BINARY_TZ "")
SET(CPACK_BINARY_WIX "")
SET(CPACK_BINARY_ZIP "")
SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_GENERATOR "TGZ")
SET(CPACK_IGNORE_FILES "~$;/\\.svn/")
SET(CPACK_INSTALLED_DIRECTORIES "/home/sycv/workplace/pengyuzhou/cvblob;/")
SET(CPACK_INSTALL_CMAKE_PROJECTS "")
SET(CPACK_INSTALL_PREFIX "/usr/local")
SET(CPACK_MODULE_PATH "/home/sycv/workplace/pengyuzhou/cvblob/CMakeScripts")
SET(CPACK_NSIS_DISPLAY_NAME "cvBlob 0.10.4")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
SET(CPACK_NSIS_PACKAGE_NAME "cvBlob 0.10.4")
SET(CPACK_OUTPUT_CONFIG_FILE "/home/sycv/workplace/pengyuzhou/cvblob/CPackConfig.cmake")
SET(CPACK_PACKAGE_CONTACT "grendel.ccl@gmail.com")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "/home/sycv/workplace/pengyuzhou/cvblob/README")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Blob library for OpenCV")
SET(CPACK_PACKAGE_FILE_NAME "cvBlob-src-0.10.4")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "cvBlob 0.10.4")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "cvBlob 0.10.4")
SET(CPACK_PACKAGE_NAME "cvBlob")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "Cristóbal Carnero Liñán <grendel.ccl@gmail.com>")
SET(CPACK_PACKAGE_VERSION "0.10.4")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "10")
SET(CPACK_PACKAGE_VERSION_PATCH "4")
SET(CPACK_RESOURCE_FILE_LICENSE "/home/sycv/workplace/pengyuzhou/cvblob/COPYING.LESSER")
SET(CPACK_RESOURCE_FILE_README "/home/sycv/workplace/pengyuzhou/cvblob/README")
SET(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-3.5/Templates/CPack.GenericWelcome.txt")
SET(CPACK_SET_DESTDIR "OFF")
SET(CPACK_SOURCE_7Z "")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "TGZ")
SET(CPACK_SOURCE_IGNORE_FILES "~$;/\\.svn/")
SET(CPACK_SOURCE_INSTALLED_DIRECTORIES "/home/sycv/workplace/pengyuzhou/cvblob;/")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/sycv/workplace/pengyuzhou/cvblob/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "cvBlob-src-0.10.4")
SET(CPACK_SOURCE_TBZ2 "")
SET(CPACK_SOURCE_TGZ "")
SET(CPACK_SOURCE_TOPLEVEL_TAG "Linux-Source")
SET(CPACK_SOURCE_TXZ "")
SET(CPACK_SOURCE_TZ "")
SET(CPACK_SOURCE_ZIP "")
SET(CPACK_STRIP_FILES "")
SET(CPACK_SYSTEM_NAME "Linux")
SET(CPACK_TOPLEVEL_TAG "Linux-Source")
SET(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/sycv/workplace/pengyuzhou/cvblob/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
