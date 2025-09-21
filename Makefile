BUILD_DIR := build
SOURCE_DIR := src
ROM := syobon64
ROM_TITLE := "Syobon Action 64"

include $(N64_INST)/include/n64.mk

ifeq ($(DEBUG),1)
CFLAGS   += -g3 -DDEBUG
CXXFLAGS += -g3 -DDEBUG
ASFLAGS  += -g
RSPASFLAGS += -g
LDFLAGS  += -g
endif

CXXFLAGS += -Isrc -Wno-error=parentheses -Wno-error=narrowing -fcommon # NOT MY FAULT!!!!

EXCLUDE_SRCS :=

SRCS := $(shell find $(SOURCE_DIR) \( -name '*.c' -o -name '*.cpp' \))
SRCS := $(filter-out $(EXCLUDE_SRCS), $(SRCS))

OBJS := $(SRCS:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJS := $(OBJS:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/%.o)

TTF := $(wildcard res/*.ttf)
PNG := $(wildcard res/*.png)
SFX := $(wildcard SE/*.wav)
BGM := $(wildcard BGM/*.wav)

FONTS := $(patsubst res/%.ttf,filesystem/res/%.font64,$(TTF))
SPRITES := $(patsubst res/%.png,filesystem/res/%.sprite,$(PNG))
AUDIO_SFX := $(patsubst SE/%.wav,filesystem/SE/%.wav64,$(SFX))
AUDIO_BGM := $(patsubst BGM/%.wav,filesystem/BGM/%.wav64,$(BGM))

ASSETS := $(FONTS) $(SPRITES) $(AUDIO_SFX) $(AUDIO_BGM)

MKFONT_FLAGS ?=
MKSPRITE_FLAGS ?=
AUDIOCONV_FLAGS ?= --wav-resample 16000 --wav-mono

all: $(ROM).z64

filesystem/res/sazanami-gothic.font64: MKFONT_FLAGS += --compress 1 --range 20-7F --range 3000-9FFF --range FF00-FFEF --range 00D7-00D7 --size 20 --outline 1 --monochrome

$(AUDIO_BGM): AUDIOCONV_FLAGS += --wav-loop true

filesystem/res/%.sprite: res/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o $(dir $@) "$<"

filesystem/res/%.font64: res/%.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	$(N64_MKFONT) $(MKFONT_FLAGS) -o $(dir $@) "$<"

filesystem/SE/%.wav64: SE/%.wav
	@mkdir -p $(dir $@)
	@echo "    [AUDIO] $@"
	$(N64_AUDIOCONV) $(AUDIOCONV_FLAGS) -o $(dir $@) "$<"

filesystem/BGM/%.wav64: BGM/%.wav
	@mkdir -p $(dir $@)
	@echo "    [AUDIO] $@"
	$(N64_AUDIOCONV) $(AUDIOCONV_FLAGS) -o $(dir $@) "$<"

$(BUILD_DIR)/$(ROM).dfs: $(ASSETS)
	@mkdir -p $(BUILD_DIR)
	@echo "    [DFS] $@"
	$(N64_MKDFS) $@ filesystem

$(BUILD_DIR)/$(ROM).elf: $(OBJS)

$(ROM).z64: N64_ROM_TITLE := $(ROM_TITLE)
$(ROM).z64: $(BUILD_DIR)/$(ROM).elf $(BUILD_DIR)/$(ROM).dfs

clean:
	rm -rf $(BUILD_DIR) filesystem $(ROM).z64

DEPS := $(OBJS:.o=.d)
-include $(DEPS)

.PHONY: all clean