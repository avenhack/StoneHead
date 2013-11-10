EXECUTABLE = HelloCpp

INCLUDES = -I.. -I../Classes  
	   

SOURCES = main.cpp \
        ../Classes/AppDelegate.cpp \
        ../Classes/MainMenuScene.cpp \
	../Classes/GameScene.cpp \
	../Classes/GameOverScene.cpp \
	../Classes/ScoresScene.cpp

COCOS_ROOT = ../../../..
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

INCLUDES += -I$(COCOS_ROOT)/CocosDenshion/include \
	    -I$(COCOS_ROOT)/CocosDenshion/linux

SHAREDLIBS += -lcocos2d -lcocosdenshion 
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so
COCOS_LIBS = $(LIB_DIR)/libcocosdenshion.so

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
