CURR:=$(ROOT)/$(DATA)/
DEBUG_DIR:=$(CURR)$(TEMPOUTPUTDIR)/
CPP_SOURCE:=$(wildcard *.cpp)
OBJ_FILES:=$(patsubst %.cpp, $(DEBUG_DIR)%.o, $(CPP_SOURCE))
CPP_SOURCE_FULL:=$(patsubst %.cpp, $(CURR)%.cpp, $(CPP_SOURCE))
DEPS=$(patsubst %.o, %.d, $(OBJ_FILES))
LIB_NAME=$(BIN_DIR)$(DATA).dll

all:$(LIB_NAME)

$(LIB_NAME):$(OBJ_FILES)
	$(LD) -shared -o $@ $^ $(LDFLAGS) -lboost_system -lboost_filesystem -lboost_log -lboost_thread -lboost_python -lpython2.7 -lboost_date_time \
	-Wl,--out-implib=${LIB_NAME}.a

-include $(DEPS)

$(DEPS): $(DEBUG_DIR)%.d: $(CURR)%.cpp
	$(CC) -c -I$(COMMON_DIR) -I$(PYTHON_INCLUDE_DIR) $< -MM > $@.$$
	@sed -r 's,($*)\.o[:]*,$(DEBUG_DIR)\1.o $@:,g' < $@.$$ > $@
	@rm -rf $@.$$

$(OBJ_FILES): $(DEBUG_DIR)%.o: $(CURR)%.cpp
	$(CC) -c $(CPP_FLAGS) -I$(COMMON_DIR) -I$(PYTHON_INCLUDE_DIR) $< -D$(BUILDING_DLL) -DDATA_EXPORTS -D$(BOOST_LINK_OPT) -o $@

.PHONY: all show clean

show:
	@echo $(CPP_SOURCE)
	@echo $(OBJ_FILES)
	@echo $(DEPS)
	@echo $(CURR)
	@echo $(LIB_NAME)

clean:
	rm -rf $(DEBUG_DIR)/*