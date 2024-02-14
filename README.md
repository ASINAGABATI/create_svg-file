
### ビルド

#### Windows11 Visual Studio 2022
 - コマンドプロンプト
	- x64 Native Tools Command Prompt for VS2022
 - コンパイル
	- cl ConsoleApp11.cpp /std:c++17 /c /I C:\opencv\build\include
	- cl Punch.cpp /std:c++17 /c /I C:\opencv\build\include
 - リンク
	- cl ConsoleApp11.obj Punch.obj opencv_world480.lib /link /LIBPATH:"C:\opencv\build\x64\vc16\lib" /out:floorball_isc.exe


#### Ubuntu20 
 - g++ -std=c++17 ConsoleApp11.cpp Punch.cpp -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -o floorball_isc
