string (TIMESTAMP MY_TIMESTAMP "%Y-%m-%d-%H-%M-%S")
execute_process (COMMAND C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe --build "C:/Users/hadar/OneDrive - Hadassah Academic College/Desktop/oop1_ex01-basefiles/oop1_ex01/out/build/x64-Debug" --target package_source)
execute_process (COMMAND C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe -E copy "C:/Users/hadar/OneDrive - Hadassah Academic College/Desktop/oop1_ex01-basefiles/oop1_ex01/out/build/x64-Debug/oop1_ex01-rutbo.zip" "C:/Users/hadar/OneDrive - Hadassah Academic College/Desktop/oop1_ex01-basefiles/oop1_ex01-rutbo-${MY_TIMESTAMP}.zip")
execute_process (COMMAND C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe -E echo "")
execute_process (COMMAND C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe -E echo "***" C:/Users/hadar/OneDrive - Hadassah Academic College/Desktop/oop1_ex01-basefiles/oop1_ex01-rutbo-${MY_TIMESTAMP}.zip "file created ***")
