# Copyright (C) 2012 The contributors of aire
#
# This program is free software: you can redistribute it and/or modify  
# it under the terms of the GNU General Public License as published by  
# the Free Software Foundation, either version 3 of the License.  
#
# This program is distributed in the hope that it will be useful,  
# but WITHOUT ANY WARRANTY; without even the implied warranty of  
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  
# GNU General Public License for more details.  
#
# You should have received a copy of the GNU General Public License  
# along with this program. If not, see <http://www.gnu.org/licenses/>.

# Include specific makefile 
ifndef arch
ifeq (,$(findstring clean, $(MAKECMDGOALS)))
ifeq (,$(findstring setup, $(MAKECMDGOALS)))
ifeq (,$(findstring dist, $(MAKECMDGOALS)))
ifeq (,$(findstring dox, $(MAKECMDGOALS)))
$(error Please use: make arch=<your_arch>)
else
DOX = doxygen
endif
endif
endif
endif
else
include Makefile.$(arch)
endif

# Target binary, object and source(include) directory 
BIN_DIR   = bin
OBJ_DIR   = obj
INC_DIR   = ./include/utility ./include/math

# Test cases
TEST_SRC  = $(notdir $(wildcard test/*.cpp))
TEST_OBJ  = $(addprefix $(OBJ_DIR)/,$(TEST_SRC:.cpp=.o))
TEST_EXE  = $(TEST_SRC:.cpp=)
TEST_BIN  = $(addprefix $(BIN_DIR)/,$(TEST_EXE))

# Example cases
EXAM_SRC  = $(notdir $(wildcard example/*.cpp))
EXAM_OBJ  = $(addprefix $(OBJ_DIR)/,$(EXAM_SRC:.cpp=.o))
EXAM_EXE  = $(EXAM_SRC:.cpp=)
EXAM_BIN  = $(addprefix $(BIN_DIR)/,$(EXAM_EXE))

# Compiler
CPP      += $(CPP_FLAGS)
CPP_INCS += $(addprefix -I,$(INC_DIR))

# Build rules
.PHONY: setup clean all

all: setup $(TEST_BIN) $(EXAM_BIN)

test: setup all $(TEST_EXE)

# Include dependencies
OBJS = $(TEST_OBJ)
-include $(OBJS:%.o=%.d)

$(OBJ_DIR)/%.o: test/%.cpp 
	$(CPP) -MMD -c -o $@ $< $(CPP_INCS)  

$(OBJ_DIR)/%.o: example/%.cpp 
	$(CPP) -MMD -c -o $@ $< $(CPP_INCS)  

define template
$(1): setup $$(addprefix $$(BIN_DIR)/,$(1))
	@mkdir -p $(BIN_DIR)/logs
	@cd $(BIN_DIR) && ./$(1) 2>&1 > logs/$(1).txt

$(BIN_DIR)/$(1): $$(addprefix $$(OBJ_DIR)/,$$(addsuffix .o,$(1))) 
	$(CPP) -o $$@ $$^ $(CPP_INCS) $(CPP_LIBS)
endef

$(foreach t,$(TEST_EXE),$(eval $(call template,$(t))))
$(foreach t,$(EXAM_EXE),$(eval $(call template,$(t))))

dox:
	$(DOX) Doxyfile.dox

setup:
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)

clean:
	@echo "Clean"
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

