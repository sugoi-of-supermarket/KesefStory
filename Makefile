# ==============================================================================
# Kesef Story - Makefile
# ==============================================================================

# Compiler and tools
CC       = cc
RM       = rm -rf
MKDIR    = mkdir -p

# Directories
SRC_DIR  = src
BUILD_DIR = build

# Raylib paths (adjust if needed)
RAYLIB_INCLUDE = ./raylib/raylib-5.5_macos/include
RAYLIB_LIB     = ./raylib/raylib-5.5_macos/lib

# Compiler flags
CFLAGS   = -Wall -Wextra -Wswitch-enum -std=c11 -O2
CFLAGS  += -I$(SRC_DIR)
CFLAGS  += -I$(RAYLIB_INCLUDE)

# Linker flags
LDFLAGS  = -L$(RAYLIB_LIB)
LDFLAGS += -Wl,-rpath,@executable_path/../$(RAYLIB_LIB)
LDFLAGS += -lraylib
LDFLAGS += -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL

# Debug flags (use with 'make debug')
DEBUG_CFLAGS = -g -O0 -DDEBUG

# Files
SRCS    = $(wildcard $(SRC_DIR)/*.c)
OBJS    = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS    = $(OBJS:.o=.d)
TARGET  = $(BUILD_DIR)/kesef_story

# ==============================================================================
# Targets
# ==============================================================================

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Build complete: $@"

# Compile source files to object files
# -MMD: Generate dependency file (.d)
# -MP:  Add phony targets for headers (prevents errors if header deleted)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)

# Include dependency files (tells Make about header dependencies)
# The '-' prefix means "don't error if files don't exist yet"
-include $(DEPS)

# ==============================================================================
# Phony Targets
# ==============================================================================

# Run the game
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	$(RM) $(BUILD_DIR)

# Debug build (with debug symbols, no optimization)
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: clean all

# Release build (optimized)
release: CFLAGS := $(filter-out -O2,$(CFLAGS)) -O3 -DNDEBUG
release: clean all

# Print Makefile variables (for debugging the Makefile itself)
print-%:
	@echo '$*=$($*)'

# Show project information
info:
	@echo "Source files: $(SRCS)"
	@echo "Object files: $(OBJS)"
	@echo "Dependencies: $(DEPS)"
	@echo "Target:       $(TARGET)"

# Check for Raylib installation
check:
	@echo "Checking for Raylib..."
	@test -d $(RAYLIB_INCLUDE) && echo "✓ Raylib include found" || echo "✗ Raylib include missing"
	@test -d $(RAYLIB_LIB) && echo "✓ Raylib lib found" || echo "✗ Raylib lib missing"

# Help target
help:
	@echo "Kesef Story - Makefile targets:"
	@echo "  make          - Build the game (default)"
	@echo "  make run      - Build and run the game"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make debug    - Build with debug symbols"
	@echo "  make release  - Build optimized release"
	@echo "  make info     - Show build configuration"
	@echo "  make check    - Check for Raylib"
	@echo "  make help     - Show this help message"

# Mark phony targets (targets that don't create files)
.PHONY: all run clean debug release print-% info check help
