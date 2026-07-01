# Compiler Settings
CXX = g++
CXXFLAGS = -Iinclude -Wall -g -std=c++11

# Directories
SRCDIR = src
OBJDIR = obj

# Target Name (Το όνομα του εκτελέσιμου)
BASE_TARGET = snake_game

# Detect Operating System
ifeq ($(OS),Windows_NT)
    # --- Windows Settings ---
    TARGET = $(BASE_TARGET).exe
    
    # Flags για τη Raylib στα Windows (στατική ή δυναμική σύνδεση)
    # Ανάλογα με το setup σου, μπορεί να χρειαστεί να προσθέσεις -I και -L μονοπάτια
    RAYLIB_FLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm
    
    MKDIR_CMD = if not exist $(OBJDIR) mkdir $(OBJDIR)
    RM_OBJ_CMD = if exist $(OBJDIR) rmdir /S /Q $(OBJDIR)
    RM_TARGET_CMD = if exist $(TARGET) del /F /Q $(TARGET)
else
    # --- Linux / macOS Settings ---
    TARGET = $(BASE_TARGET)
    
    # Flags για τη Raylib σε Linux (X11, GL, Math, Threads κλπ)
    RAYLIB_FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    
    MKDIR_CMD = mkdir -p $(OBJDIR)
    RM_OBJ_CMD = rm -rf $(OBJDIR)
    RM_TARGET_CMD = rm -f $(TARGET)
endif

# Source and Object files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Phony Targets
.PHONY: all clean

# Default Rule
all: $(TARGET)

# Link Rule (Εδώ συνδέουμε τα αντικείμενα μαζί με τη Raylib)
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(RAYLIB_FLAGS)

# Compile Rule
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Rule
clean:
	@$(RM_OBJ_CMD)
	@$(RM_TARGET_CMD)