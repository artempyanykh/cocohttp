ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
$(eval $(ARGS):;@:)

.DEFAULT_GOAL := build

LAST_PRESET_FILE := last-preset.txt
LAST_PRESET := $(shell cat ${LAST_PRESET_FILE})
ifeq (${LAST_PRESET},)
PRESET := default-debug
else
PRESET := ${LAST_PRESET}
endif

$(info PRESET is ${PRESET})

BUILD_DIR := build/${PRESET}

.PHONY: bootstrap
bootstrap:
	git submodule update --init && vcpkg/bootstrap-vcpkg.sh

.PHONY: clean
clean:
	rm -rf ${BUILD_DIR}

.PHONY: cleanall
cleanall:
	rm -rf build

${LAST_PRESET_FILE}:
	@echo ${PRESET} > ${LAST_PRESET_FILE}

.PHONY: configure
configure: ${LAST_PRESET_FILE}
	cmake --preset ${PRESET}

.PHONY: build
build:
	@cmake --build ${BUILD_DIR}

.PHONY: runSample1
runSample1: build
	@${BUILD_DIR}/sample/sample1 $(ARGS)

.PHONY: reconfigure
reconfigure: clean configure