# Hash
一个用于求文件MD5/SHA1值的小工具，基于wxWidgets开发  
# 版本    0.1
* 实现了求文件MD5值的功能
* 实现了将文件MD5值存档的功能
* 实现了对剪贴板的操作
* 修正了退出后依旧占用文件的bug 
* 进度条显示目前可用
* 依然存在的问题有：
    * UI线程未与计算线程分离
	
##编译环境：

* WxWidgets 3.0.2   
* GCC4.8.1(TDM64-2)

###WxWidgets
	https://github.com/wxWidgets/wxWidgets
