include("E:/School/DataBaseE/QuanQuan/build/Desktop_Qt_6_9_3_MinGW_64_bit-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/QuanQuan-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "E:/School/DataBaseE/QuanQuan/build/Desktop_Qt_6_9_3_MinGW_64_bit-Debug/QuanQuan.exe"
    GENERATE_QT_CONF
)
