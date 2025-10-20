# ============================================================
# Makefile for OpenRasterDriver
# ============================================================

CC      := gcc
CFLAGS  := -Wall -Wextra -O2
LDFLAGS := -lcups
TARGET  := openrasterdriver
OBJS    := main.o pcl6.o

# Default rule
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile each .c file to .o
%.o: %.c pcl6.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)

# Convenience run target (for manual testing)
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

