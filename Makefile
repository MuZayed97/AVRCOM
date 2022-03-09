DEVICE:=atmega328p
F_CPU := 16000000UL
CC = avr-gcc
CC_ARGS = -O2 -Wall -ggdb  -mmcu=$(DEVICE) -DF_CPU=$(F_CPU)

OBJCOPY = avr-objcopy
OBJCOPY_ARGS = -Oihex 

AVRDUDE = avrdude
AVRDUDE_ARGS = -Cavrdude.conf -F -v -pm328p -carduino -PCOM10 -b115200 -D

INCLUD_PATH = include/

SRC = src
OBJ = debug
TEST = test
C-SRCS=$(wildcard $(SRC)/*.c)
ASM-SRCS=$(wildcard $(SRC)/*.S)
OBJS = $(patsubst $(SRC)/%.S, $(OBJ)/%.o, $(ASM-SRCS))
OBJS += $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(C-SRCS))
OBJS-TEST = $(wildcard $(OBJ)/$(TEST)/*.o)

all:
	# pleas write:( make test )for test device 

link: $(OBJS) 
	$(CC) $(CC_ARGS) -Wl,-Map,./debug/$(DEVICE).map -I$(INCLUD_PATH) $^ $(OBJS-TEST) -o ./$(OBJ)/$(DEVICE).elf
	$(OBJCOPY) $(OBJCOPY_ARGS) -j .text -j .data  ./debug/$(DEVICE).elf ./debug/$(DEVICE).hex
	avr-size -A ./debug/$(DEVICE).hex

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CC_ARGS) -c -I$(INCLUD_PATH) $^ -o $@
	

$(OBJ)/%.o: $(SRC)/%.S
	$(CC) $(CC_ARGS) -c -I$(INCLUD_PATH) $^ -o $@

testdev: $(OBJS) 
	$(CC) $(CC_ARGS) -c -I$(INCLUD_PATH) $(TEST)/$(DEVICE).c -o$(OBJ)/$(TEST)/$(DEVICE).o

test: testdev link

upload:

	$(AVRDUDE) $(AVRDUDE_ARGS) -Uflash:w:"./debug/atmega328p.hex":i

clean:
	rm -rf ./$(OBJ)/*.map
	rm -rf ./$(OBJ)/*.hex
	rm -rf ./$(OBJ)/*.o
	rm -rf ./$(OBJ)/$(TEST)/*.o
	rm -rf ./$(OBJ)/*.s
	rm -rf ./$(OBJ)/*.map
	rm -rf ./$(OBJ)/*.S
	rm -rf ./$(OBJ)/*.elf
	mkdir -p ./$(OBJ)/$(TEST)