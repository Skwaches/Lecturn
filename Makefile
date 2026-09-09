BUILD=build
FILES=$(wildcard *.cpp)
OUTPUTS=$(FILES:%.cpp=$(BUILD)/%)

.PHONY: $(Q)
$(Q): $(BUILD)/$(Q)

all: $(OUTPUTS)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%: %.cpp $(BUILD)
	g++ -g -O3 -Wall -Werror $< -o $@

run: $(BUILD)/$(Q) 
	./$(BUILD)/$(Q)
	
clean: 
	rm -rf $(BUILD)/$(Q)
