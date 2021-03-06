# GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug_linux
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug_linux)
  SDL2Pacman_config = debug_linux
endif
ifeq ($(config),debug_windows)
  SDL2Pacman_config = debug_windows
endif
ifeq ($(config),release_linux)
  SDL2Pacman_config = release_linux
endif
ifeq ($(config),release_windows)
  SDL2Pacman_config = release_windows
endif

PROJECTS := SDL2Pacman

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

SDL2Pacman:
ifneq (,$(SDL2Pacman_config))
	@echo "==== Building SDL2Pacman ($(SDL2Pacman_config)) ===="
	@${MAKE} --no-print-directory -C . -f SDL2Pacman.make config=$(SDL2Pacman_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f SDL2Pacman.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug_linux"
	@echo "  debug_windows"
	@echo "  release_linux"
	@echo "  release_windows"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   SDL2Pacman"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"