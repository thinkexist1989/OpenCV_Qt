!build_pass:message(OpenCV Directory is $$(OPENCV))
INCLUDEPATH += $$(OPENCV)/include

win32:{
    Debug:{
        LIBS += -l$$(OPENCV)/lib/Debug/opencv_world345d
    }
    Release:{
        LIBS += -l$$(OPENCV)/lib/Release/opencv_world345
    }
}

