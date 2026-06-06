include("E:/School/DataBaseE/QuanQuan/build/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/QuanQuan-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "E:/School/DataBaseE/QuanQuan/build/QuanQuan.exe"
    GENERATE_QT_CONF
)
